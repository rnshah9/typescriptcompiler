#ifndef MLIR_TYPESCRIPT_LOWERTOLLVMLOGIC_THROWLOGIC_H_
#define MLIR_TYPESCRIPT_LOWERTOLLVMLOGIC_THROWLOGIC_H_

#include "TypeScript/Config.h"
#include "TypeScript/Defines.h"
#include "TypeScript/Passes.h"
#include "TypeScript/TypeScriptDialect.h"
#include "TypeScript/TypeScriptOps.h"

#include "TypeScript/LowerToLLVM/CodeLogicHelper.h"
#include "TypeScript/LowerToLLVM/LLVMCodeHelper.h"
#include "TypeScript/LowerToLLVM/TypeConverterHelper.h"
#include "TypeScript/LowerToLLVM/TypeHelper.h"

#include "mlir/IR/PatternMatch.h"

using namespace mlir;
namespace mlir_ts = mlir::typescript;

namespace typescript
{

class ThrowLogic
{
    Operation *op;
    PatternRewriter &rewriter;
    TypeHelper th;
    LLVMCodeHelper ch;
    CodeLogicHelper clh;
    Location loc;
    mlir::TypeConverter &typeConverter;

  public:
    ThrowLogic(Operation *op, PatternRewriter &rewriter, TypeConverterHelper &tch, Location loc)
        : op(op), rewriter(rewriter), th(rewriter), ch(op, rewriter, &tch.typeConverter), clh(op, rewriter), loc(loc),
          typeConverter(tch.typeConverter)
    {
    }

    mlir::LogicalResult logic(mlir::Value exceptionValue, mlir::Type origType, mlir::Block *unwind)
    {
#ifdef WIN_EXCEPTION
        return logicWin32(exceptionValue, origType, unwind);
#else
        return logicUnix(exceptionValue, origType, unwind);
#endif
    }

#ifdef WIN_EXCEPTION
    mlir::LogicalResult logicWin32(mlir::Value exceptionValue, mlir::Type origType, mlir::Block *unwind)
    {
        mlir::Type exceptionType = origType;

        LLVMRTTIHelperVCWin32 rttih(op, rewriter, typeConverter);
        rttih.setType(exceptionType);

        auto throwInfoPtrTy = rttih.getThrowInfoPtrTy();

        auto i8PtrTy = th.getI8PtrType();

        // variable
        mlir::Value value;
        {
            OpBuilder::InsertionGuard guard(rewriter);

            auto found = ch.seekFirstNonConstantOp(op->getParentOfType<LLVM::LLVMFuncOp>());
            if (found)
            {
                rewriter.setInsertionPointAfter(found);
            }

            value =
                rewriter.create<mlir_ts::VariableOp>(loc, mlir_ts::RefType::get(exceptionType), mlir::Value(), rewriter.getBoolAttr(false));
        }

        rewriter.create<mlir_ts::StoreOp>(loc, exceptionValue, value);

        // throw
        auto throwInfoPtr = rttih.throwInfoPtrValue(loc);

        auto throwFuncName = "_CxxThrowException";
        auto cxxThrowException = ch.getOrInsertFunction(throwFuncName, th.getFunctionType(th.getVoidType(), {i8PtrTy, throwInfoPtrTy}));

        {
            OpBuilder::InsertionGuard guard(rewriter);

            if (unwind != nullptr)
            {
                OpBuilder::InsertionGuard guard(rewriter);

                auto unreachable = clh.FindUnreachableBlockOrCreate();

                auto endOfBlock = rewriter.getInsertionBlock()->getTerminator() == op;
                auto *continuationBlock = endOfBlock ? nullptr : clh.CutBlockAndSetInsertPointToEndOfBlock();

                rewriter.create<LLVM::InvokeOp>(
                    loc, TypeRange{th.getVoidType()}, mlir::FlatSymbolRefAttr::get(rewriter.getContext(), throwFuncName),
                    ValueRange{clh.castToI8Ptr(value), throwInfoPtr}, unreachable, ValueRange{}, unwind, ValueRange{});

                if (continuationBlock)
                {
                    rewriter.setInsertionPointToStart(continuationBlock);
                }
            }
            else
            {
                rewriter.create<LLVM::CallOp>(loc, cxxThrowException, ValueRange{clh.castToI8Ptr(value), throwInfoPtr});
                rewriter.create<mlir_ts::UnreachableOp>(loc);
            }
        }

        return success();
    }
#else
    mlir::LogicalResult logicUnix(mlir::Value exceptionValue, mlir::Type origType, mlir::Block *unwind)
    {
        mlir::Type exceptionType = origType;

        LLVMRTTIHelperVCLinux rttih(op, rewriter, typeConverter);
        rttih.setType(exceptionType);

        if (rttih.isRethrow())
        {
            return logicUnixRethrow(exceptionValue, unwind);
        }

        return logicUnixThrow(rttih, exceptionValue, origType, unwind);
    }

    mlir::LogicalResult logicUnixThrow(LLVMRTTIHelperVCLinux &rttih, mlir::Value exceptionValue, mlir::Type origType, mlir::Block *unwind)
    {
        mlir::Type exceptionType = origType;

        auto i8PtrTy = th.getI8PtrType();

        auto allocExceptFuncName = "__cxa_allocate_exception";

        auto cxxAllocException = ch.getOrInsertFunction(allocExceptFuncName, th.getFunctionType(i8PtrTy, {th.getI64Type()}));

        auto throwFuncName = "__cxa_throw";

        auto cxxThrowException = ch.getOrInsertFunction(throwFuncName, th.getFunctionType(th.getVoidType(), {i8PtrTy, i8PtrTy, i8PtrTy}));

        auto size = rewriter.create<mlir_ts::SizeOfOp>(loc, th.getI64Type(), exceptionType);

        auto callInfo = rewriter.create<LLVM::CallOp>(
            loc, TypeRange{i8PtrTy}, mlir::FlatSymbolRefAttr::get(rewriter.getContext(), allocExceptFuncName), ValueRange{size});

        auto value = callInfo.getResult(0);

        // save value
        auto refValue = rewriter.create<mlir_ts::CastOp>(loc, mlir_ts::RefType::get(exceptionType), value);
        rewriter.create<mlir_ts::StoreOp>(loc, exceptionValue, refValue);

        // throw exception
        if (unwind)
        {
            OpBuilder::InsertionGuard guard(rewriter);

            auto unreachable = clh.FindUnreachableBlockOrCreate();

            auto endOfBlock = rewriter.getInsertionBlock()->getTerminator() == op;

            auto *continuationBlock = endOfBlock ? nullptr : clh.CutBlockAndSetInsertPointToEndOfBlock();

            auto nullValue = rewriter.create<LLVM::NullOp>(loc, i8PtrTy);
            rewriter.create<LLVM::InvokeOp>(loc, TypeRange{th.getVoidType()},
                                            mlir::FlatSymbolRefAttr::get(rewriter.getContext(), throwFuncName),
                                            ValueRange{value, clh.castToI8Ptr(rttih.throwInfoPtrValue(loc)), nullValue}, unreachable,
                                            ValueRange{}, unwind, ValueRange{});

            if (continuationBlock)
            {
                rewriter.setInsertionPointToStart(continuationBlock);
            }
        }
        else
        {
            auto nullValue = rewriter.create<LLVM::NullOp>(loc, i8PtrTy);
            rewriter.create<LLVM::CallOp>(loc, cxxThrowException,
                                          ValueRange{value, clh.castToI8Ptr(rttih.throwInfoPtrValue(loc)), nullValue});
            rewriter.create<mlir_ts::UnreachableOp>(loc);
        }

        return success();
    }

    mlir::LogicalResult logicUnixRethrow(mlir::Value exceptionValue, mlir::Block *unwind)
    {
        auto i8PtrTy = th.getI8PtrType();

        auto rethrowFuncName = "__cxa_rethrow";

        auto cxxRethrowException = ch.getOrInsertFunction(rethrowFuncName, th.getFunctionType(ArrayRef<mlir::Type>{}));

        // save value
        if (unwind)
        {
            OpBuilder::InsertionGuard guard(rewriter);

            auto unreachable = clh.FindUnreachableBlockOrCreate();

            auto endOfBlock = rewriter.getInsertionBlock()->getTerminator() == op;

            auto *continuationBlock = endOfBlock ? nullptr : clh.CutBlockAndSetInsertPointToEndOfBlock();

            rewriter.create<LLVM::InvokeOp>(loc, TypeRange{th.getVoidType()},
                                            mlir::FlatSymbolRefAttr::get(rewriter.getContext(), rethrowFuncName), ValueRange{}, unreachable,
                                            ValueRange{}, unwind, ValueRange{});

            if (continuationBlock)
            {
                rewriter.setInsertionPointToStart(continuationBlock);
            }
        }
        else
        {
            rewriter.create<LLVM::CallOp>(loc, cxxRethrowException, ValueRange{});
            rewriter.create<mlir_ts::UnreachableOp>(loc);
        }

        return success();
    }
#endif
};
} // namespace typescript

#endif // MLIR_TYPESCRIPT_LOWERTOLLVMLOGIC_THROWLOGIC_H_
