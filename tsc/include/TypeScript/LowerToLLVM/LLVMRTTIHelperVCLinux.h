#ifndef MLIR_TYPESCRIPT_LOWERTOLLVMLOGIC_LLVMRTTIHELPERVCLINUX_H_
#define MLIR_TYPESCRIPT_LOWERTOLLVMLOGIC_LLVMRTTIHELPERVCLINUX_H_

#include "TypeScript/Config.h"
#include "TypeScript/Defines.h"
#include "TypeScript/Passes.h"
#include "TypeScript/TypeScriptDialect.h"
#include "TypeScript/TypeScriptOps.h"

#include "TypeScript/LowerToLLVM/TypeHelper.h"
#include "TypeScript/LowerToLLVM/LLVMCodeHelper.h"
#include "TypeScript/LowerToLLVM/LLVMRTTIHelperVCLinuxConst.h"

#include "mlir/Transforms/DialectConversion.h"
#include "llvm/ADT/TypeSwitch.h"

#include <sstream>

using namespace mlir;
namespace mlir_ts = mlir::typescript;

namespace typescript
{

struct TypeNames
{
    std::string typeName;
};

class LLVMRTTIHelperVCLinux
{
    Operation *op;
    PatternRewriter &rewriter;
    ModuleOp parentModule;
    TypeHelper th;
    LLVMCodeHelper ch;

    SmallVector<TypeNames> types;

  public:
    LLVMRTTIHelperVCLinux(Operation *op, PatternRewriter &rewriter, TypeConverter &typeConverter)
        : op(op), rewriter(rewriter), parentModule(op->getParentOfType<ModuleOp>()), th(rewriter), ch(op, rewriter, &typeConverter)
    {
    }

    void setF32AsCatchType()
    {
        types.push_back({F32Type::typeName});
    }

    void setI32AsCatchType()
    {
        types.push_back({I32Type::typeName});
    }

    void setStringTypeAsCatchType()
    {
        types.push_back({StringType::typeName});
    }

    void setI8PtrAsCatchType()
    {
        types.push_back({I8PtrType::typeName});
    }

    void setClassTypeAsCatchType(StringRef name)
    {
        std::stringstream ss;
        ss << "_ZTIP";
        ss << name.str().size();
        ss << name.str();

        types.push_back({ss.str()});
    }

    LogicalResult setPersonality(mlir::FuncOp newFuncOp)
    {
        auto name = "__gxx_personality_v0";
        auto cxxFrameHandler3 = ch.getOrInsertFunction(name, th.getFunctionType(th.getI32Type(), {}, true));

        newFuncOp->setAttr(rewriter.getIdentifier("personality"), FlatSymbolRefAttr::get(rewriter.getContext(), name));
        return success();
    }

    void setType(mlir::Type type)
    {
        TypeSwitch<Type>(type)
            .Case<mlir::IntegerType>([&](auto intType) {
                if (intType.getIntOrFloatBitWidth() == 32)
                {
                    setI32AsCatchType();
                }
                else
                {
                    llvm_unreachable("not implemented");
                }
            })
            .Case<mlir::FloatType>([&](auto floatType) {
                if (floatType.getIntOrFloatBitWidth() == 32)
                {
                    setF32AsCatchType();
                }
                else
                {
                    llvm_unreachable("not implemented");
                }
            })
            .Case<mlir_ts::NumberType>([&](auto numberType) { setF32AsCatchType(); })
            .Case<mlir_ts::StringType>([&](auto stringType) { setStringTypeAsCatchType(); })
            .Case<mlir_ts::ClassType>([&](auto classType) { setClassTypeAsCatchType(classType.getName().getValue()); })
            .Case<mlir_ts::AnyType>([&](auto anyType) { setI8PtrAsCatchType(); })
            .Default([&](auto type) { llvm_unreachable("not implemented"); });
    }

    bool hasType()
    {
        return types.size() > 0;
    }

    mlir::Value typeInfoPtrValue(mlir::Location loc)
    {
        // TODO:
        return throwInfoPtrValue(loc);
    }

    mlir::Value throwInfoPtrValue(mlir::Location loc)
    {
        auto typeName = types.front().typeName;

        assert(typeName.size() > 0);

        auto throwInfoPtr =
            rewriter.create<mlir::ConstantOp>(loc, th.getI8PtrType(), FlatSymbolRefAttr::get(rewriter.getContext(), typeName));
        return throwInfoPtr;
    }
};
} // namespace typescript

#endif // MLIR_TYPESCRIPT_LOWERTOLLVMLOGIC_LLVMRTTIHELPERVCLINUX_H_
