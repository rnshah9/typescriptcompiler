#ifndef MLIR_TYPESCRIPT_LOWERTOLLVMLOGIC_LLVMCODEHELPERWRAP_H_
#define MLIR_TYPESCRIPT_LOWERTOLLVMLOGIC_LLVMCODEHELPERWRAP_H_

#include "TypeScript/LowerToLLVM/TypeConverterHelper.h"
#include "TypeScript/LowerToLLVM/TypeHelper.h"

#include "mlir/Dialect/StandardOps/IR/Ops.h"

using namespace mlir;
namespace mlir_ts = mlir::typescript;

namespace typescript
{

enum class MemoryAllocSet
{
    None,
    Zero
};

template <typename T>
mlir::Value castLogic(mlir::Value size, mlir::Type sizeType, mlir::Operation *op, PatternRewriter &rewriter, TypeConverterHelper tch);

class LLVMCodeHelperBase
{
  protected:
    mlir::Operation *op;
    PatternRewriter &rewriter;
    TypeConverter *typeConverter;

  public:
    LLVMCodeHelperBase(mlir::Operation *op, PatternRewriter &rewriter, TypeConverter *typeConverter)
        : op(op), rewriter(rewriter), typeConverter(typeConverter)
    {
    }

    template <typename T> void seekLast(mlir::Block *block)
    {
        // find last string
        auto lastUse = [&](Operation *op) {
            if (auto globalOp = dyn_cast_or_null<LLVM::GlobalOp>(op))
            {
                if (globalOp.valueAttr() && globalOp.valueAttr().isa<T>())
                {
                    rewriter.setInsertionPointAfter(globalOp);
                }
            }
        };

        block->walk(lastUse);
    }

    void seekLast(mlir::Block *block)
    {
        // find last string
        auto lastUse = [&](mlir::Operation *op) {
            if (auto globalOp = dyn_cast_or_null<LLVM::GlobalOp>(op))
            {
                rewriter.setInsertionPointAfter(globalOp);
            }
        };

        block->walk(lastUse);
    }

    void seekLastWithBody(mlir::Block *block)
    {
        // find last string
        auto lastUse = [&](Operation *op) {
            if (auto globalOp = dyn_cast_or_null<LLVM::GlobalOp>(op))
            {
                if (globalOp.getInitializerBlock())
                {
                    rewriter.setInsertionPointAfter(globalOp);
                }
            }
        };

        block->walk(lastUse);
    }

    template <typename T> void seekLastOp(mlir::Block *block)
    {
        // find last string
        auto lastUse = [&](Operation *op) {
            if (auto opT = dyn_cast_or_null<T>(op))
            {
                rewriter.setInsertionPointAfter(opT);
            }
        };

        block->walk(lastUse);
    }

    template <typename T> Operation *seekFirstNonConstantOp(T funcOp)
    {
        auto found = false;
        Operation *foundOp;
        // find last string
        auto lastUse = [&](Operation *op) {
            if (found)
            {
                return;
            }

            auto constantOp = dyn_cast_or_null<mlir_ts::ConstantOp>(op);
            if (!constantOp)
            {
                auto constOp = dyn_cast_or_null<mlir::ConstantOp>(op);
                if (!constOp)
                {
                    found = true;
                    foundOp = op;
                }
            }
        };

        funcOp.walk(lastUse);

        return foundOp;
    }

    std::string getStorageStringName(std::string value)
    {
        auto opHash = std::hash<std::string>{}(value);

        std::stringstream strVarName;
        strVarName << "s_" << opHash;

        return strVarName.str();
    }

  private:
    /// Return a value representing an access into a global string with the given
    /// name, creating the string if necessary.
    mlir::Value getOrCreateGlobalString_(StringRef name, StringRef value)
    {
        auto loc = op->getLoc();
        auto parentModule = op->getParentOfType<ModuleOp>();

        TypeHelper th(rewriter);

        // Create the global at the entry of the module.
        LLVM::GlobalOp global;
        if (!(global = parentModule.lookupSymbol<LLVM::GlobalOp>(name)))
        {
            OpBuilder::InsertionGuard insertGuard(rewriter);
            rewriter.setInsertionPointToStart(parentModule.getBody());

            seekLast<StringAttr>(parentModule.getBody());

            auto type = th.getArrayType(th.getI8Type(), value.size());
            global = rewriter.create<LLVM::GlobalOp>(loc, type, true, LLVM::Linkage::Internal, name, rewriter.getStringAttr(value));
        }

        // Get the pointer to the first character in the global string.
        mlir::Value globalPtr = rewriter.create<LLVM::AddressOfOp>(loc, global);
        mlir::Value cst0 = rewriter.create<LLVM::ConstantOp>(loc, th.getIndexType(), th.getIndexAttrValue(0));
        return rewriter.create<LLVM::GEPOp>(loc, th.getI8PtrType(), globalPtr, ArrayRef<mlir::Value>({cst0, cst0}));
    }

  public:
    mlir::Value getOrCreateGlobalString(std::string value)
    {
        return getOrCreateGlobalString(getStorageStringName(value), value);
    }

    mlir::Value getOrCreateGlobalString(StringRef name, std::string value)
    {
        return getOrCreateGlobalString_(name, StringRef(value.data(), value.length() + 1));
    }

    LLVM::LLVMFuncOp getOrInsertFunction(const StringRef &name, const LLVM::LLVMFunctionType &llvmFnType)
    {
        auto parentModule = op->getParentOfType<ModuleOp>();

        if (auto funcOp = parentModule.lookupSymbol<LLVM::LLVMFuncOp>(name))
        {
            return funcOp;
        }

        auto loc = op->getLoc();

        // Insert the printf function into the body of the parent module.
        PatternRewriter::InsertionGuard insertGuard(rewriter);
        rewriter.setInsertionPointToStart(parentModule.getBody());
        return rewriter.create<LLVM::LLVMFuncOp>(loc, name, llvmFnType);
    }

    mlir::Value MemoryAlloc(mlir::Value sizeOfAlloc, MemoryAllocSet zero = MemoryAllocSet::None)
    {
        return _MemoryAlloc<int>(sizeOfAlloc, zero);
    }

    mlir::Value MemoryAlloc(mlir::Type storageType, MemoryAllocSet zero = MemoryAllocSet::None)
    {
        TypeHelper th(rewriter);

        auto loc = op->getLoc();

        auto sizeOfTypeValue = rewriter.create<mlir_ts::SizeOfOp>(loc, th.getIndexType(), storageType);
        return MemoryAlloc(sizeOfTypeValue, zero);
    }

    mlir::Value MemoryAllocBitcast(mlir::Type res, mlir::Type storageType, MemoryAllocSet zero = MemoryAllocSet::None)
    {
        auto loc = op->getLoc();

        auto alloc = MemoryAlloc(storageType, zero);
        auto val = rewriter.create<LLVM::BitcastOp>(loc, res, alloc);
        return val;
    }

    mlir::Value MemoryAllocBitcast(mlir::Type res, mlir::Value sizeOfAlloc, MemoryAllocSet zero = MemoryAllocSet::None)
    {
        auto loc = op->getLoc();

        auto alloc = MemoryAlloc(sizeOfAlloc, zero);
        auto val = rewriter.create<LLVM::BitcastOp>(loc, res, alloc);
        return val;
    }

    mlir::Value MemoryRealloc(mlir::Value ptrValue, mlir::Value sizeOfAlloc)
    {
        return _MemoryRealloc<int>(ptrValue, sizeOfAlloc);
    }

    mlir::Value MemoryReallocBitcast(mlir::Type res, mlir::Value ptrValue, mlir::Value sizeOfAlloc)
    {
        auto loc = op->getLoc();

        auto alloc = MemoryRealloc(ptrValue, sizeOfAlloc);
        auto val = rewriter.create<LLVM::BitcastOp>(loc, res, alloc);
        return val;
    }

    LogicalResult MemoryFree(mlir::Value ptrValue)
    {
        return _MemoryFree<int>(ptrValue);
    }

    template <typename T> mlir::Value _MemoryAlloc(mlir::Value sizeOfAlloc, MemoryAllocSet zero)
    {
        TypeHelper th(rewriter);
        TypeConverterHelper tch(typeConverter);
        CodeLogicHelper clh(op, rewriter);

        auto loc = op->getLoc();

        auto i8PtrTy = th.getI8PtrType();
        auto mallocFuncOp = getOrInsertFunction("malloc", th.getFunctionType(i8PtrTy, {th.getIndexType()}));

        auto effectiveSize = sizeOfAlloc;
        if (effectiveSize.getType() != th.getIndexType())
        {
            effectiveSize = castLogic<int>(effectiveSize, th.getIndexType(), op, rewriter, tch);
        }

        auto callResults = rewriter.create<LLVM::CallOp>(loc, mallocFuncOp, ValueRange{effectiveSize});
        auto ptr = callResults.getResult(0);

        if (zero == MemoryAllocSet::Zero)
        {
            auto memsetFuncOp = getOrInsertFunction("memset", th.getFunctionType(i8PtrTy, {i8PtrTy, th.getI32Type(), th.getIndexType()}));
            auto const0 = clh.createI32ConstantOf(0);
            rewriter.create<LLVM::CallOp>(loc, memsetFuncOp, ValueRange{ptr, const0, effectiveSize});
        }

        return ptr;
    }

    template <typename T> mlir::Value _MemoryRealloc(mlir::Value ptrValue, mlir::Value sizeOfAlloc)
    {
        TypeHelper th(rewriter);
        TypeConverterHelper tch(typeConverter);

        auto loc = op->getLoc();

        auto i8PtrTy = th.getI8PtrType();

        auto effectivePtrValue = ptrValue;
        if (ptrValue.getType() != i8PtrTy)
        {
            effectivePtrValue = rewriter.create<LLVM::BitcastOp>(loc, i8PtrTy, ptrValue);
        }

        auto mallocFuncOp = getOrInsertFunction("realloc", th.getFunctionType(i8PtrTy, {i8PtrTy, th.getIndexType()}));

        auto effectiveSize = sizeOfAlloc;
        if (effectiveSize.getType() != th.getIndexType())
        {
            effectiveSize = castLogic<int>(effectiveSize, th.getIndexType(), op, rewriter, tch);
        }

        auto callResults = rewriter.create<LLVM::CallOp>(loc, mallocFuncOp, ValueRange{effectivePtrValue, effectiveSize});
        return callResults.getResult(0);
    }

    template <typename T> mlir::LogicalResult _MemoryFree(mlir::Value ptrValue)
    {
        TypeHelper th(rewriter);
        TypeConverterHelper tch(typeConverter);

        auto loc = op->getLoc();

        auto i8PtrTy = th.getI8PtrType();

        auto freeFuncOp = getOrInsertFunction("free", th.getFunctionType(th.getVoidType(), {i8PtrTy}));

        auto casted = rewriter.create<LLVM::BitcastOp>(loc, i8PtrTy, ptrValue);

        rewriter.create<LLVM::CallOp>(loc, freeFuncOp, ValueRange{casted});

        return mlir::success();
    }
};

} // namespace typescript

#endif // MLIR_TYPESCRIPT_LOWERTOLLVMLOGIC_LLVMCODEHELPERWRAP_H_
