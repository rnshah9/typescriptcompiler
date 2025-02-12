#define DEBUG_TYPE "mlir"

#include "TypeScript/Config.h"
#include "TypeScript/TypeScriptDialect.h"
#include "TypeScript/TypeScriptOps.h"

#include "mlir/Dialect/StandardOps/IR/Ops.h"
#include "mlir/IR/DialectImplementation.h"
#include "mlir/IR/OpImplementation.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/Transforms/InliningUtils.h"

#include "llvm/ADT/TypeSwitch.h"
#include "llvm/ADT/SmallPtrSet.h"

#include "llvm/Support/Debug.h"

using namespace mlir;
namespace mlir_ts = mlir::typescript;

//===----------------------------------------------------------------------===//
// TypeScript dialect.
//===----------------------------------------------------------------------===//
#include "TypeScript/TypeScriptOpsDialect.cpp.inc"

LogicalResult verify(mlir_ts::FuncOp op);
LogicalResult verify(mlir_ts::InvokeOp op);
LogicalResult verify(mlir_ts::CastOp op);

#ifndef DISABLE_CUSTOM_CLASSSTORAGESTORAGE
namespace mlir
{
namespace typescript
{
namespace detail
{
struct ClassStorageTypeStorage : public ::mlir::TypeStorage
{
    ClassStorageTypeStorage(FlatSymbolRefAttr name) : name(name), fields({})
    {
    }

    /// The hash key is a tuple of the parameter types.
    using KeyTy = FlatSymbolRefAttr;
    bool operator==(const KeyTy &tblgenKey) const
    {
        if (!(name == tblgenKey))
            return false;
        return true;
    }
    static ::llvm::hash_code hashKey(const KeyTy &tblgenKey)
    {
        return ::llvm::hash_combine(tblgenKey);
    }

    /// Define a construction method for creating a new instance of this storage.
    static ClassStorageTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, const KeyTy &tblgenKey)
    {
        auto name = tblgenKey;

        return new (allocator.allocate<ClassStorageTypeStorage>()) ClassStorageTypeStorage(name);
    }

    LogicalResult mutate(TypeStorageAllocator &allocator, ::llvm::ArrayRef<::mlir::typescript::FieldInfo> newFields)
    {
        // Cannot set a different body than before.
        llvm::SmallVector<::mlir::typescript::FieldInfo, 4> tmpFields;

        for (size_t i = 0, e = newFields.size(); i < e; ++i)
            tmpFields.push_back(newFields[i].allocateInto(allocator));
        auto copiedFields = allocator.copyInto(ArrayRef<::mlir::typescript::FieldInfo>(tmpFields));

        fields = copiedFields;

        return success();
    }

    FlatSymbolRefAttr name;
    ::llvm::ArrayRef<::mlir::typescript::FieldInfo> fields;
};
} // namespace detail

FlatSymbolRefAttr ClassStorageType::getName() const
{
    return getImpl()->name;
}

::llvm::ArrayRef<::mlir::typescript::FieldInfo> ClassStorageType::getFields() const
{
    return getImpl()->fields;
}

LogicalResult ClassStorageType::setFields(::llvm::ArrayRef<::mlir::typescript::FieldInfo> newFields)
{
    return Base::mutate(newFields);
}

} // namespace typescript
} // namespace mlir
#endif

#define GET_TYPEDEF_CLASSES
#include "TypeScript/TypeScriptOpsTypes.cpp.inc"

#define GET_OP_CLASSES
#include "TypeScript/TypeScriptOps.cpp.inc"

//===----------------------------------------------------------------------===//
// TypeScriptInlinerInterface
//===----------------------------------------------------------------------===//

/// This class defines the interface for handling inlining with TypeScript
/// operations.

struct TypeScriptInlinerInterface : public mlir::DialectInlinerInterface
{
    TypeScriptInlinerInterface(Dialect *dialect) : DialectInlinerInterface(dialect)
    {
    }

    //===--------------------------------------------------------------------===//
    // Analysis Hooks
    //===--------------------------------------------------------------------===//

    /// All call operations within TypeScript(but recursive) can be inlined.
    // TODO: find out how to prevent recursive calls in better way
    // TODO: something happening when inlining class methods
    bool isLegalToInline(mlir::Operation *call, mlir::Operation *callable, bool wouldBeCloned) const final
    {
        LLVM_DEBUG(llvm::dbgs() << "!! Legal To Inline(call): TRUE = " << *call << "\n";);
        return true;
    }

    bool isLegalToInline(Region *dest, Region *src, bool wouldBeCloned, BlockAndValueMapping &valueMapping) const final
    {
        if (auto funcOp = dyn_cast<mlir_ts::FuncOp>(dest->getParentOp()))
        {
            auto condition = !(funcOp.personality().hasValue() && funcOp.personality().getValue());
            LLVM_DEBUG(llvm::dbgs() << "!! is Legal To Inline (region): " << (condition ? "TRUE" : "FALSE") << " " << funcOp << " = "
                                    << "\n";);
            return condition;
        }

        return false;
    }

    /// here if we return false for any of op, then whole funcOp will not be inlined
    /// needed to decided if to allow inlining or not
    bool isLegalToInline(mlir::Operation *op, mlir::Region *region, bool, mlir::BlockAndValueMapping &) const final
    {
        // auto condition = true;
        // ignore all functions until you find out how to resolve issue with recursive calls
        auto condition = !isa<mlir_ts::SymbolCallInternalOp>(op);

        // do not inline if func body has TryOp
        condition &= !isa<mlir_ts::TryOp>(op);
        condition &= !isa<mlir_ts::CatchOp>(op);
        condition &= !isa<mlir_ts::ThrowOp>(op);
        condition &= !isa<mlir_ts::LandingPadOp>(op);
        condition &= !isa<mlir_ts::BeginCatchOp>(op);
        condition &= !isa<mlir_ts::EndCatchOp>(op);

        LLVM_DEBUG(llvm::dbgs() << "!! is Legal To Inline (op): " << (condition ? "TRUE" : "FALSE") << " " << *op << " = "
                                << "\n";);

        return condition;
    }

    //===--------------------------------------------------------------------===//
    // Transformation Hooks
    //===--------------------------------------------------------------------===//

    void handleTerminator(mlir::Operation *op, mlir::ArrayRef<Value> valuesToRepl) const final
    {
        LLVM_DEBUG(llvm::dbgs() << "!! handleTerminator: " << *op << "\n";);

        // we need to handle it when inlining function
        // Only "ts.returnVal" needs to be handled here.
        if (auto returnOp = dyn_cast<mlir_ts::ReturnInternalOp>(op))
        {
            LLVM_DEBUG(llvm::dbgs() << "!! handleTerminator counts: Ret ops: " << returnOp.getNumOperands()
                                    << ", values to replace: " << valuesToRepl.size() << "\n";);
            // Replace the values directly with the return operands.
            if (returnOp.getNumOperands() == valuesToRepl.size())
            {
                for (const auto &it : llvm::enumerate(returnOp.getOperands()))
                {
                    valuesToRepl[it.index()].replaceAllUsesWith(it.value());
                }
            }
            else
            {
                OpBuilder builder(op);
                for (const auto &it : llvm::enumerate(valuesToRepl))
                {
                    auto undefVal = builder.create<mlir_ts::UndefOp>(op->getLoc(), it.value().getType());
                    valuesToRepl[it.index()].replaceAllUsesWith(undefVal);
                }
            }
        }
    }

    void handleTerminator(mlir::Operation *op, mlir::Block *newDest) const final
    {
        LLVM_DEBUG(llvm::dbgs() << "!! handleTerminator: " << *op << "\n"
                                << "!! Block: ";
                   newDest->dump(); llvm::dbgs() << "\n";);

        auto voidType = mlir_ts::VoidType::get(op->getContext());

        // remove all args with ts.Void
        for (unsigned int argIndex = 0; argIndex < newDest->getNumArguments(); argIndex++)
        {
            if (newDest->getArgument(argIndex).getType() == voidType)
            {
                newDest->eraseArgument(argIndex);
                argIndex--;
            }
        }

        // we need to handle it when inlining function
        // Only "ts.returnVal" needs to be handled here.
        if (auto returnOp = dyn_cast<mlir_ts::ReturnInternalOp>(op))
        {
            // Replace the values directly with the return operands.
            OpBuilder builder(op);
            builder.create<mlir::BranchOp>(op->getLoc(), newDest, returnOp.getOperands());
            op->erase();
        }
    }

    /// Attempts to materialize a conversion for a type mismatch between a call
    /// from this dialect, and a callable region. This method should generate an
    /// operation that takes 'input' as the only operand, and produces a single
    /// result of 'resultType'. If a conversion can not be generated, nullptr
    /// should be returned.
    mlir::Operation *materializeCallConversion(mlir::OpBuilder &builder, mlir::Value input, mlir::Type resultType,
                                               mlir::Location conversionLoc) const final
    {
        return builder.create<mlir_ts::CastOp>(conversionLoc, resultType, input);
    }
};

void mlir_ts::TypeScriptDialect::initialize()
{
    addOperations<
#define GET_OP_LIST
#include "TypeScript/TypeScriptOps.cpp.inc"
        >();
    addTypes<
#define GET_TYPEDEF_LIST
#include "TypeScript/TypeScriptOpsTypes.cpp.inc"
        >();
    addInterfaces<TypeScriptInlinerInterface>();
}

Type mlir_ts::TypeScriptDialect::parseType(DialectAsmParser &parser) const
{
    llvm::SMLoc typeLoc = parser.getCurrentLocation();

    mlir::Type booleanType;
    if (*generatedTypeParser(getContext(), parser, "boolean", booleanType))
    {
        return booleanType;
    }

    mlir::Type numberType;
    if (*generatedTypeParser(getContext(), parser, "number", numberType))
    {
        return numberType;
    }

    mlir::Type stringType;
    if (*generatedTypeParser(getContext(), parser, "string", stringType))
    {
        return stringType;
    }

    mlir::Type refType;
    if (*generatedTypeParser(getContext(), parser, "ref", refType))
    {
        return refType;
    }

    mlir::Type valueRefType;
    if (*generatedTypeParser(getContext(), parser, "value_ref", valueRefType))
    {
        return valueRefType;
    }

    mlir::Type optionalType;
    if (*generatedTypeParser(getContext(), parser, "optional", optionalType))
    {
        return optionalType;
    }

    mlir::Type enumType;
    if (*generatedTypeParser(getContext(), parser, "enum", enumType))
    {
        return enumType;
    }

    mlir::Type arrayType;
    if (*generatedTypeParser(getContext(), parser, "array", arrayType))
    {
        return arrayType;
    }

    mlir::Type tupleType;
    if (*generatedTypeParser(getContext(), parser, "tuple", tupleType))
    {
        return tupleType;
    }

    parser.emitError(typeLoc, "unknown type in TypeScript dialect");
    return Type();
}

void mlir_ts::TypeScriptDialect::printType(Type type, DialectAsmPrinter &os) const
{
    if (failed(generatedTypePrinter(type, os)))
    {
        llvm_unreachable("unknown 'TypeScript' type");
    }
}

// The functions don't need to be in the header file, but need to be in the mlir
// namespace. Declare them here, then define them immediately below. Separating
// the declaration and definition adheres to the LLVM coding standards.
namespace mlir
{
namespace typescript
{
// FieldInfo is used as part of a parameter, so equality comparison is compulsory.
static bool operator==(const FieldInfo &a, const FieldInfo &b);
// FieldInfo is used as part of a parameter, so a hash will be computed.
static llvm::hash_code hash_value(const FieldInfo &fi);
} // namespace typescript
} // namespace mlir

// FieldInfo is used as part of a parameter, so equality comparison is
// compulsory.
static bool mlir_ts::operator==(const FieldInfo &a, const FieldInfo &b)
{
    return a.id == b.id && a.type == b.type;
}

// FieldInfo is used as part of a parameter, so a hash will be computed.
static llvm::hash_code mlir_ts::hash_value(const FieldInfo &fi)
{
    return llvm::hash_combine(fi.id, fi.type);
}
