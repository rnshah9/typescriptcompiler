#ifndef MLIR_TYPESCRIPT_MLIRGENCONTEXT_H_
#define MLIR_TYPESCRIPT_MLIRGENCONTEXT_H_

#include "TypeScript/TypeScriptDialect.h"
#include "TypeScript/TypeScriptOps.h"

#include "mlir/IR/Attributes.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Types.h"

#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/LLVMIR/LLVMTypes.h"
#include "mlir/Dialect/SCF/SCF.h"
#include "mlir/Dialect/StandardOps/IR/Ops.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/TypeSwitch.h"
#include "llvm/Support/Debug.h"

#include "TypeScript/DOM.h"
#include "TypeScript/MLIRLogic/MLIRTypeHelper.h"

#include "parser_types.h"

#include <numeric>

using namespace ::typescript;
using namespace ts;
namespace mlir_ts = mlir::typescript;

using llvm::ArrayRef;
using llvm::cast;
using llvm::dyn_cast;
using llvm::dyn_cast_or_null;
using llvm::isa;
using llvm::makeArrayRef;
using llvm::SmallVector;
using llvm::StringRef;
using llvm::Twine;

namespace
{

struct PassResult
{
    PassResult() : functionReturnTypeShouldBeProvided(false)
    {
    }

    mlir::Type functionReturnType;
    bool functionReturnTypeShouldBeProvided;
    llvm::StringMap<ts::VariableDeclarationDOM::TypePtr> outerVariables;
    SmallVector<mlir_ts::FieldInfo> extraFieldsInThisContext;
};

struct GenContext
{
    GenContext() = default;

    void clearScopeVars()
    {
        passResult = nullptr;
        capturedVars = nullptr;

        currentOperation = nullptr;
    }

    // TODO: you are using "theModule.getBody()->clear();", do you need this hack anymore?
    void clean()
    {
        if (cleanUps)
        {
            for (auto op : *cleanUps)
            {
                op->dropAllDefinedValueUses();
                op->dropAllUses();
                op->dropAllReferences();
                op->erase();
            }

            delete cleanUps;
            cleanUps = nullptr;
        }

        if (passResult)
        {
            delete passResult;
            passResult = nullptr;
        }

        cleanState();

        cleanFuncOp();
    }

    void cleanState()
    {
        if (state)
        {
            delete state;
            state = nullptr;
        }
    }

    void cleanFuncOp()
    {
        if (funcOp)
        {
            funcOp->dropAllDefinedValueUses();
            funcOp->dropAllUses();
            funcOp->dropAllReferences();
            funcOp->erase();
        }
    }

    bool allowPartialResolve;
    bool dummyRun;
    bool allowConstEval;
    bool allocateVarsInContextThis;
    bool allocateVarsOutsideOfOperation;
    bool skipProcessed;
    bool rediscover;
    bool discoverParamsOnly;
    bool insertIntoParentScope;
    mlir::Operation *currentOperation;
    mlir_ts::FuncOp funcOp;
    llvm::StringMap<ts::VariableDeclarationDOM::TypePtr> *capturedVars;
    mlir::Type thisType;
    mlir::Type destFuncType;
    mlir::Type argTypeDestFuncType;
    PassResult *passResult;
    mlir::SmallVector<mlir::Block *> *cleanUps;
    NodeArray<Statement> generatedStatements;
    llvm::StringMap<mlir::Type> typeAliasMap;
    llvm::StringMap<std::pair<TypeParameterDOM::TypePtr, mlir::Type>> typeParamsWithArgs;
    ArrayRef<mlir::Value> callOperands;
    int *state;
};

struct NamespaceInfo;
using NamespaceInfo_TypePtr = std::shared_ptr<NamespaceInfo>;

struct GenericFunctionInfo
{
  public:
    using TypePtr = std::shared_ptr<GenericFunctionInfo>;

    mlir::StringRef name;

    llvm::SmallVector<TypeParameterDOM::TypePtr> typeParams;

    FunctionLikeDeclarationBase functionDeclaration;

    FunctionPrototypeDOM::TypePtr funcOp;

    mlir_ts::FunctionType funcType;

    NamespaceInfo_TypePtr elementNamespace;

    bool processing;
    bool processed;

    GenericFunctionInfo() = default;
};

enum class VariableClass
{
    Const,
    Let,
    Var,
    ConstRef,
    External
};

struct StaticFieldInfo
{
    mlir::Attribute id;
    mlir::Type type;
    mlir::StringRef globalVariableName;
    int virtualIndex;
};

struct MethodInfo
{
    std::string name;
    mlir_ts::FunctionType funcType;
    // TODO: remove using it, we do not need it, we need actual name of function not function itself
    mlir_ts::FuncOp funcOp;
    bool isStatic;
    bool isVirtual;
    bool isAbstract;
    int virtualIndex;
};

struct VirtualMethodOrInterfaceVTableInfo
{
    VirtualMethodOrInterfaceVTableInfo(MethodInfo methodInfo_, bool isInterfaceVTable_) : methodInfo(methodInfo_), isStaticField(false), isInterfaceVTable(isInterfaceVTable_)
    {
    }

    VirtualMethodOrInterfaceVTableInfo(StaticFieldInfo staticFieldInfo_, bool isInterfaceVTable_) : staticFieldInfo(staticFieldInfo_), isStaticField(true), isInterfaceVTable(isInterfaceVTable_)
    {
    }

    MethodInfo methodInfo;
    StaticFieldInfo staticFieldInfo;
    bool isStaticField;
    bool isInterfaceVTable;
};

struct AccessorInfo
{
    std::string name;
    mlir_ts::FuncOp get;
    mlir_ts::FuncOp set;
    bool isStatic;
    bool isVirtual;
    bool isAbstract;
};

struct InterfaceFieldInfo
{
    mlir::Attribute id;
    mlir::Type type;
    bool isConditional;
    int interfacePosIndex;
};

struct InterfaceMethodInfo
{
    std::string name;
    mlir_ts::FunctionType funcType;
    bool isConditional;
    int interfacePosIndex;
};

struct VirtualMethodOrFieldInfo
{
    VirtualMethodOrFieldInfo(MethodInfo methodInfo) : methodInfo(methodInfo), isField(false), isMissing(false)
    {
    }

    VirtualMethodOrFieldInfo(mlir_ts::FieldInfo fieldInfo) : fieldInfo(fieldInfo), isField(true), isMissing(false)
    {
    }

    VirtualMethodOrFieldInfo(MethodInfo methodInfo, bool isMissing)
        : methodInfo(methodInfo), isField(false), isMissing(isMissing)
    {
    }

    VirtualMethodOrFieldInfo(mlir_ts::FieldInfo fieldInfo, bool isMissing)
        : fieldInfo(fieldInfo), isField(true), isMissing(isMissing)
    {
    }

    MethodInfo methodInfo;
    mlir_ts::FieldInfo fieldInfo;
    bool isField;
    bool isMissing;
};

struct InterfaceInfo
{
  public:
    using TypePtr = std::shared_ptr<InterfaceInfo>;
    using InterfaceInfoWithOffset = std::pair<int, InterfaceInfo::TypePtr>;

    mlir::StringRef name;

    mlir::StringRef fullName;

    mlir_ts::InterfaceType interfaceType;

    llvm::SmallVector<InterfaceInfoWithOffset> extends;

    llvm::SmallVector<InterfaceFieldInfo> fields;

    llvm::SmallVector<InterfaceMethodInfo> methods;

    llvm::StringMap<std::pair<TypeParameterDOM::TypePtr, mlir::Type>> typeParamsWithArgs;

    InterfaceInfo()
    {
    }

    mlir::LogicalResult getTupleTypeFields(llvm::SmallVector<mlir_ts::FieldInfo> &tupleFields, MLIRTypeHelper &mth)
    {
        for (auto &extent : extends)
        {
            if (mlir::failed(std::get<1>(extent)->getTupleTypeFields(tupleFields, mth)))
            {
                return mlir::failure();
            }
        }

        for (auto &method : methods)
        {
            tupleFields.push_back({mth.TupleFieldName(method.name), method.funcType});
        }

        for (auto &field : fields)
        {
            tupleFields.push_back({field.id, field.type});
        }

        return mlir::success();
    }

    mlir::LogicalResult getVirtualTable(
        llvm::SmallVector<VirtualMethodOrFieldInfo> &vtable,
        std::function<mlir_ts::FieldInfo(mlir::Attribute, mlir::Type, bool)> resolveField,
        std::function<MethodInfo &(std::string, mlir_ts::FunctionType, bool)> resolveMethod)
    {
        for (auto &extent : extends)
        {
            if (mlir::failed(std::get<1>(extent)->getVirtualTable(vtable, resolveField, resolveMethod)))
            {
                return mlir::failure();
            }
        }

        // do vtable for current
        for (auto &method : methods)
        {
            auto &classMethodInfo = resolveMethod(method.name, method.funcType, method.isConditional);
            if (classMethodInfo.name.empty())
            {
                if (method.isConditional)
                {
                    MethodInfo missingMethod;
                    missingMethod.name = method.name;
                    missingMethod.funcType = method.funcType;
                    vtable.push_back({missingMethod, true});
                }
                else
                {
                    return mlir::failure();
                }
            }
            else
            {
                vtable.push_back({classMethodInfo});
            }
        }

        for (auto &field : fields)
        {
            auto fieldInfo = resolveField(field.id, field.type, field.isConditional);
            if (!fieldInfo.id)
            {
                if (field.isConditional)
                {
                    mlir_ts::FieldInfo missingField;
                    missingField.id = field.id;
                    missingField.type = field.type;
                    vtable.push_back({missingField, true});
                }
                else
                {
                    return mlir::failure();
                }
            }
            else
            {
                vtable.push_back({fieldInfo});
            }
        }

        return mlir::success();
    }

    int getMethodIndex(mlir::StringRef name)
    {
        auto dist = std::distance(
            methods.begin(), std::find_if(methods.begin(), methods.end(),
                                          [&](InterfaceMethodInfo methodInfo) { return name == methodInfo.name; }));
        return (signed)dist >= (signed)methods.size() ? -1 : dist;
    }

    int getFieldIndex(mlir::Attribute id)
    {
        auto dist = std::distance(fields.begin(),
                                  std::find_if(fields.begin(), fields.end(),
                                               [&](InterfaceFieldInfo fieldInfo) { return id == fieldInfo.id; }));
        return (signed)dist >= (signed)fields.size() ? -1 : dist;
    }

    InterfaceFieldInfo *findField(mlir::Attribute id, int &totalOffset)
    {
        auto index = getFieldIndex(id);
        if (index >= 0)
        {
            return &this->fields[index];
        }

        for (auto &extent : extends)
        {
            auto totalOffsetLocal = 0;
            auto field = std::get<1>(extent)->findField(id, totalOffsetLocal);
            if (field)
            {
                totalOffset = std::get<0>(extent) + totalOffsetLocal;
                return field;
            }
        }

        LLVM_DEBUG(llvm::dbgs() << "\n!! can't resolve field: " << id << " in interface type: " << interfaceType
                                << "\n";);

        return nullptr;
    }

    InterfaceMethodInfo *findMethod(mlir::StringRef name, int &totalOffset)
    {
        auto index = getMethodIndex(name);
        if (index >= 0)
        {
            return &methods[index];
        }

        for (auto &extent : extends)
        {
            auto totalOffsetLocal = 0;
            auto *method = std::get<1>(extent)->findMethod(name, totalOffsetLocal);
            if (method)
            {
                totalOffset = std::get<0>(extent) + totalOffsetLocal;
                return method;
            }
        }

        return nullptr;
    }

    int getNextVTableMemberIndex()
    {
        return getVTableSize();
    }

    int getVTableSize()
    {
        auto offset = 0;
        for (auto &extent : extends)
        {
            offset += std::get<1>(extent)->getVTableSize();
        }

        return offset + fields.size() + methods.size();
    }

    void recalcOffsets()
    {
        auto offset = 0;
        for (auto &extent : extends)
        {
            std::get<0>(extent) = offset;
            offset += std::get<1>(extent)->getVTableSize();
        }
    }
};

struct GenericInterfaceInfo
{
  public:
    using TypePtr = std::shared_ptr<GenericInterfaceInfo>;

    mlir::StringRef name;

    mlir::StringRef fullName;

    llvm::SmallVector<TypeParameterDOM::TypePtr> typeParams;

    mlir_ts::InterfaceType interfaceType;

    InterfaceDeclaration interfaceDeclaration;

    NamespaceInfo_TypePtr elementNamespace;

    GenericInterfaceInfo()
    {
    }
};

struct ImplementInfo
{
    InterfaceInfo::TypePtr interface;
    int virtualIndex;
    bool processed;
};

struct ClassInfo
{
  public:
    using TypePtr = std::shared_ptr<ClassInfo>;

    mlir::StringRef name;

    mlir::StringRef fullName;

    mlir_ts::ClassType classType;

    llvm::SmallVector<ClassInfo::TypePtr> baseClasses;

    llvm::SmallVector<ImplementInfo> implements;

    llvm::SmallVector<StaticFieldInfo> staticFields;

    llvm::SmallVector<MethodInfo> methods;

    llvm::SmallVector<AccessorInfo> accessors;

    NodeArray<ClassElement> extraMembers;
    NodeArray<ClassElement> extraMembersPost;

    llvm::StringMap<std::pair<TypeParameterDOM::TypePtr, mlir::Type>> typeParamsWithArgs;

    bool isDeclaration;
    bool hasNew;
    bool hasConstructor;
    bool hasInitializers;
    bool hasStaticConstructor;
    bool hasStaticInitializers;
    bool hasVirtualTable;
    bool isAbstract;
    bool hasRTTI;
    bool fullyProcessedAtEvaluation;
    bool fullyProcessed;
    bool processingStorageClass;
    bool processedStorageClass;
    bool enteredProcessingStorageClass;

    ClassInfo()
        : isDeclaration(false), hasNew(false), hasConstructor(false), hasInitializers(false), hasStaticConstructor(false),
          hasStaticInitializers(false), hasVirtualTable(false), isAbstract(false), hasRTTI(false),
          fullyProcessedAtEvaluation(false), fullyProcessed(false), processingStorageClass(false),
          processedStorageClass(false), enteredProcessingStorageClass(false)
    {
    }

    auto getHasConstructor() -> bool
    {
        if (hasConstructor)
        {
            return true;
        }

        for (auto &base : baseClasses)
        {
            if (base->hasConstructor)
            {
                return true;
            }
        }

        return false;
    }

    auto getHasVirtualTable() -> bool
    {
        if (hasVirtualTable)
        {
            return true;
        }

        for (auto &base : baseClasses)
        {
            if (base->hasVirtualTable)
            {
                return true;
            }
        }

        return false;
    }

    auto getHasVirtualTableVariable() -> bool
    {
        for (auto &base : baseClasses)
        {
            if (base->hasVirtualTable)
            {
                return false;
            }
        }

        if (hasVirtualTable)
        {
            return true;
        }

        return false;
    }

    void getVirtualTable(llvm::SmallVector<VirtualMethodOrInterfaceVTableInfo> &vtable)
    {
        for (auto &base : baseClasses)
        {
            base->getVirtualTable(vtable);
        }

        // do vtable for current class
        for (auto &implement : implements)
        {
            auto index =
                std::distance(vtable.begin(), std::find_if(vtable.begin(), vtable.end(), [&](auto vTableRecord) {
                                  return implement.interface->fullName == vTableRecord.methodInfo.name;
                              }));
            if ((size_t)index < vtable.size())
            {
                // found interface
                continue;
            }

            MethodInfo methodInfo;
            methodInfo.name = implement.interface->fullName.str();
            implement.virtualIndex = vtable.size();
            vtable.push_back({methodInfo, true});
        }

        // methods
        for (auto &method : methods)
        {
#ifndef ADD_STATIC_MEMBERS_TO_VTABLE            
            if (method.isStatic)
            {
                continue;
            }
#endif            

            auto index =
                std::distance(vtable.begin(), std::find_if(vtable.begin(), vtable.end(), [&](auto vTableMethod) {
                                  return method.name == vTableMethod.methodInfo.name;
                              }));
            if ((size_t)index < vtable.size())
            {
                // found method
                vtable[index].methodInfo.funcOp = method.funcOp;
                method.virtualIndex = index;
                method.isVirtual = true;
                continue;
            }

            if (method.isVirtual)
            {
                method.virtualIndex = vtable.size();
                vtable.push_back({method, false});
            }
        }

#ifdef ADD_STATIC_MEMBERS_TO_VTABLE
        // static fields
        for (auto &staticField : staticFields)
        {
            staticField.virtualIndex = vtable.size();
            vtable.push_back({staticField, false});
        }        
#endif        
    }

    auto getBasesWithRoot(SmallVector<StringRef> &classNames) -> bool
    {
        classNames.push_back(fullName);

        for (auto &base : baseClasses)
        {
            base->getBasesWithRoot(classNames);
        }

        return true;
    }

    /// Iterate over the held elements.
    using iterator = ArrayRef<::mlir::typescript::FieldInfo>::iterator;

    int getStaticFieldIndex(mlir::Attribute id)
    {
        auto dist =
            std::distance(staticFields.begin(), std::find_if(staticFields.begin(), staticFields.end(),
                                                             [&](StaticFieldInfo fldInf) { return id == fldInf.id; }));
        return (signed)dist >= (signed)staticFields.size() ? -1 : dist;
    }

    int getMethodIndex(mlir::StringRef name)
    {
        auto dist = std::distance(
            methods.begin(), std::find_if(methods.begin(), methods.end(), [&](MethodInfo methodInfo) {
                LLVM_DEBUG(dbgs() << "\nmatching method: " << name << " to " << methodInfo.name << "\n\n";);
                return name == methodInfo.name;
            }));
        return (signed)dist >= (signed)methods.size() ? -1 : dist;
    }

    unsigned fieldsCount()
    {
        auto storageClass = classType.getStorageType().cast<mlir_ts::ClassStorageType>();
        return storageClass.size();
    }

    mlir_ts::FieldInfo fieldInfoByIndex(int index)
    {
        if (index >= 0)
        {
            auto storageClass = classType.getStorageType().cast<mlir_ts::ClassStorageType>();
            return storageClass.getFieldInfo(index);
        }

        return mlir_ts::FieldInfo();
    }

    mlir_ts::FieldInfo findField(mlir::Attribute id, bool &foundField)
    {
        foundField = false;
        auto storageClass = classType.getStorageType().cast<mlir_ts::ClassStorageType>();
        auto index = storageClass.getIndex(id);
        if (index >= 0)
        {
            foundField = true;
            return storageClass.getFieldInfo(index);
        }

        for (auto &baseClass : baseClasses)
        {
            auto field = baseClass->findField(id, foundField);
            if (foundField)
            {
                return field;
            }
        }

        LLVM_DEBUG(llvm::dbgs() << "\n!! can't resolve field: " << id << " in class type: " << storageClass << "\n";);

        return mlir_ts::FieldInfo();
    }

    MethodInfo *findMethod(mlir::StringRef name)
    {
        auto index = getMethodIndex(name);
        if (index >= 0)
        {
            return &methods[index];
        }

        for (auto &baseClass : baseClasses)
        {
            auto *method = baseClass->findMethod(name);
            if (method)
            {
                return method;
            }
        }

        return nullptr;
    }

    int getAccessorIndex(mlir::StringRef name)
    {
        auto dist = std::distance(accessors.begin(),
                                  std::find_if(accessors.begin(), accessors.end(),
                                               [&](AccessorInfo accessorInfo) { return name == accessorInfo.name; }));
        return (signed)dist >= (signed)accessors.size() ? -1 : dist;
    }

    int getImplementIndex(mlir::StringRef name)
    {
        auto dist = std::distance(implements.begin(),
                                  std::find_if(implements.begin(), implements.end(), [&](ImplementInfo implementInfo) {
                                      return name == implementInfo.interface->fullName;
                                  }));
        return (signed)dist >= (signed)implements.size() ? -1 : dist;
    }
};

struct GenericClassInfo
{
  public:
    using TypePtr = std::shared_ptr<GenericClassInfo>;

    mlir::StringRef name;

    mlir::StringRef fullName;

    llvm::SmallVector<TypeParameterDOM::TypePtr> typeParams;

    mlir_ts::ClassType classType;

    ClassLikeDeclaration classDeclaration;

    NamespaceInfo_TypePtr elementNamespace;

    GenericClassInfo()
    {
    }
};

struct NamespaceInfo
{
  public:
    using TypePtr = std::shared_ptr<NamespaceInfo>;

    mlir::StringRef name;

    mlir::StringRef fullName;

    mlir_ts::NamespaceType namespaceType;

    llvm::StringMap<mlir_ts::FunctionType> functionTypeMap;

    llvm::StringMap<mlir_ts::FuncOp> functionMap;

    llvm::StringMap<GenericFunctionInfo::TypePtr> genericFunctionMap;

    llvm::StringMap<VariableDeclarationDOM::TypePtr> globalsMap;

    llvm::StringMap<llvm::StringMap<ts::VariableDeclarationDOM::TypePtr>> captureVarsMap;

    llvm::StringMap<llvm::SmallVector<mlir::typescript::FieldInfo>> localVarsInThisContextMap;

    llvm::StringMap<mlir::Type> typeAliasMap;

    llvm::StringMap<std::pair<llvm::SmallVector<TypeParameterDOM::TypePtr>, TypeNode>> genericTypeAliasMap;

    llvm::StringMap<mlir::StringRef> importEqualsMap;

    llvm::StringMap<std::pair<mlir::Type, mlir::DictionaryAttr>> enumsMap;

    llvm::StringMap<ClassInfo::TypePtr> classesMap;

    llvm::StringMap<GenericClassInfo::TypePtr> genericClassesMap;

    llvm::StringMap<InterfaceInfo::TypePtr> interfacesMap;

    llvm::StringMap<GenericInterfaceInfo::TypePtr> genericInterfacesMap;

    llvm::StringMap<NamespaceInfo::TypePtr> namespacesMap;

    bool isFunctionNamespace;

    NamespaceInfo::TypePtr parentNamespace;
};

struct ValueOrLogicalResult 
{
    ValueOrLogicalResult() = default;
    ValueOrLogicalResult(mlir::LogicalResult result) : result(result) {};
    ValueOrLogicalResult(mlir::Value value) : result(mlir::success()), value(value) {};

    mlir::LogicalResult result;
    mlir::Value value;

    operator bool()
    {
        return mlir::succeeded(result);
    }

    bool failed()
    {
        return mlir::failed(result);
    }

    bool failed_or_no_value()
    {
        return failed() || !value;
    }

    operator mlir::LogicalResult()
    {
        return failed_or_no_value() ? mlir::failure() : mlir::success();
    } 

    operator mlir::Value()
    {
        return value;
    }    
};

#define V(x) static_cast<mlir::Value>(x)

} // namespace

#endif // MLIR_TYPESCRIPT_MLIRGENCONTEXT_H_
