#ifndef TYPESCRIPT_AST_H_
#define TYPESCRIPT_AST_H_

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/Casting.h"
#include <vector>
#include <stack>

namespace typescript
{

    enum class SyntaxKind
    {
        Unknown = 0,
        EndOfFileToken = 1,
        SingleLineCommentTrivia = 2,
        MultiLineCommentTrivia = 3,
        NewLineTrivia = 4,
        WhitespaceTrivia = 5,
        ShebangTrivia = 6,
        ConflictMarkerTrivia = 7,
        NumericLiteral = 8,
        BigIntLiteral = 9,
        StringLiteral = 10,
        JsxText = 11,
        JsxTextAllWhiteSpaces = 12,
        RegularExpressionLiteral = 13,
        NoSubstitutionTemplateLiteral = 14,
        TemplateHead = 15,
        TemplateMiddle = 16,
        TemplateTail = 17,
        OpenBraceToken = 18,
        CloseBraceToken = 19,
        OpenParenToken = 20,
        CloseParenToken = 21,
        OpenBracketToken = 22,
        CloseBracketToken = 23,
        DotToken = 24,
        DotDotDotToken = 25,
        SemicolonToken = 26,
        CommaToken = 27,
        QuestionDotToken = 28,
        LessThanToken = 29,
        LessThanSlashToken = 30,
        GreaterThanToken = 31,
        LessThanEqualsToken = 32,
        GreaterThanEqualsToken = 33,
        EqualsEqualsToken = 34,
        ExclamationEqualsToken = 35,
        EqualsEqualsEqualsToken = 36,
        ExclamationEqualsEqualsToken = 37,
        EqualsGreaterThanToken = 38,
        PlusToken = 39,
        MinusToken = 40,
        AsteriskToken = 41,
        AsteriskAsteriskToken = 42,
        SlashToken = 43,
        PercentToken = 44,
        PlusPlusToken = 45,
        MinusMinusToken = 46,
        LessThanLessThanToken = 47,
        GreaterThanGreaterThanToken = 48,
        GreaterThanGreaterThanGreaterThanToken = 49,
        AmpersandToken = 50,
        BarToken = 51,
        CaretToken = 52,
        ExclamationToken = 53,
        TildeToken = 54,
        AmpersandAmpersandToken = 55,
        BarBarToken = 56,
        QuestionToken = 57,
        ColonToken = 58,
        AtToken = 59,
        QuestionQuestionToken = 60,
        /** Only the JSDoc scanner produces BacktickToken. The normal scanner produces NoSubstitutionTemplateLiteral and related kinds. */
        BacktickToken = 61,
        EqualsToken = 62,
        PlusEqualsToken = 63,
        MinusEqualsToken = 64,
        AsteriskEqualsToken = 65,
        AsteriskAsteriskEqualsToken = 66,
        SlashEqualsToken = 67,
        PercentEqualsToken = 68,
        LessThanLessThanEqualsToken = 69,
        GreaterThanGreaterThanEqualsToken = 70,
        GreaterThanGreaterThanGreaterThanEqualsToken = 71,
        AmpersandEqualsToken = 72,
        BarEqualsToken = 73,
        CaretEqualsToken = 74,
        Identifier = 75,
        PrivateIdentifier = 76,
        BreakKeyword = 77,
        CaseKeyword = 78,
        CatchKeyword = 79,
        ClassKeyword = 80,
        ConstKeyword = 81,
        ContinueKeyword = 82,
        DebuggerKeyword = 83,
        DefaultKeyword = 84,
        DeleteKeyword = 85,
        DoKeyword = 86,
        ElseKeyword = 87,
        EnumKeyword = 88,
        ExportKeyword = 89,
        ExtendsKeyword = 90,
        FalseKeyword = 91,
        FinallyKeyword = 92,
        ForKeyword = 93,
        FunctionKeyword = 94,
        IfKeyword = 95,
        ImportKeyword = 96,
        InKeyword = 97,
        InstanceOfKeyword = 98,
        NewKeyword = 99,
        NullKeyword = 100,
        ReturnKeyword = 101,
        SuperKeyword = 102,
        SwitchKeyword = 103,
        ThisKeyword = 104,
        ThrowKeyword = 105,
        TrueKeyword = 106,
        TryKeyword = 107,
        TypeOfKeyword = 108,
        VarKeyword = 109,
        VoidKeyword = 110,
        WhileKeyword = 111,
        WithKeyword = 112,
        ImplementsKeyword = 113,
        InterfaceKeyword = 114,
        LetKeyword = 115,
        PackageKeyword = 116,
        PrivateKeyword = 117,
        ProtectedKeyword = 118,
        PublicKeyword = 119,
        StaticKeyword = 120,
        YieldKeyword = 121,
        AbstractKeyword = 122,
        AsKeyword = 123,
        AssertsKeyword = 124,
        AnyKeyword = 125,
        AsyncKeyword = 126,
        AwaitKeyword = 127,
        BooleanKeyword = 128,
        ConstructorKeyword = 129,
        DeclareKeyword = 130,
        GetKeyword = 131,
        InferKeyword = 132,
        IsKeyword = 133,
        KeyOfKeyword = 134,
        ModuleKeyword = 135,
        NamespaceKeyword = 136,
        NeverKeyword = 137,
        ReadonlyKeyword = 138,
        RequireKeyword = 139,
        NumberKeyword = 140,
        ObjectKeyword = 141,
        SetKeyword = 142,
        StringKeyword = 143,
        SymbolKeyword = 144,
        TypeKeyword = 145,
        UndefinedKeyword = 146,
        UniqueKeyword = 147,
        UnknownKeyword = 148,
        FromKeyword = 149,
        GlobalKeyword = 150,
        BigIntKeyword = 151,
        OfKeyword = 152,
        QualifiedName = 153,
        ComputedPropertyName = 154,
        TypeParameter = 155,
        Parameter = 156,
        Decorator = 157,
        PropertySignature = 158,
        PropertyDeclaration = 159,
        MethodSignature = 160,
        MethodDeclaration = 161,
        Constructor = 162,
        GetAccessor = 163,
        SetAccessor = 164,
        CallSignature = 165,
        ConstructSignature = 166,
        IndexSignature = 167,
        TypePredicate = 168,
        TypeReference = 169,
        FunctionType = 170,
        ConstructorType = 171,
        TypeQuery = 172,
        TypeLiteral = 173,
        ArrayType = 174,
        TupleType = 175,
        OptionalType = 176,
        RestType = 177,
        UnionType = 178,
        IntersectionType = 179,
        ConditionalType = 180,
        InferType = 181,
        ParenthesizedType = 182,
        ThisType = 183,
        TypeOperator = 184,
        IndexedAccessType = 185,
        MappedType = 186,
        LiteralType = 187,
        ImportType = 188,
        ObjectBindingPattern = 189,
        ArrayBindingPattern = 190,
        BindingElement = 191,
        ArrayLiteralExpression = 192,
        ObjectLiteralExpression = 193,
        PropertyAccessExpression = 194,
        ElementAccessExpression = 195,
        CallExpression = 196,
        NewExpression = 197,
        TaggedTemplateExpression = 198,
        TypeAssertionExpression = 199,
        ParenthesizedExpression = 200,
        FunctionExpression = 201,
        ArrowFunction = 202,
        DeleteExpression = 203,
        TypeOfExpression = 204,
        VoidExpression = 205,
        AwaitExpression = 206,
        PrefixUnaryExpression = 207,
        PostfixUnaryExpression = 208,
        BinaryExpression = 209,
        ConditionalExpression = 210,
        TemplateExpression = 211,
        YieldExpression = 212,
        SpreadElement = 213,
        ClassExpression = 214,
        OmittedExpression = 215,
        ExpressionWithTypeArguments = 216,
        AsExpression = 217,
        NonNullExpression = 218,
        MetaProperty = 219,
        SyntheticExpression = 220,
        TemplateSpan = 221,
        SemicolonClassElement = 222,
        Block = 223,
        EmptyStatement = 224,
        VariableStatement = 225,
        ExpressionStatement = 226,
        IfStatement = 227,
        DoStatement = 228,
        WhileStatement = 229,
        ForStatement = 230,
        ForInStatement = 231,
        ForOfStatement = 232,
        ContinueStatement = 233,
        BreakStatement = 234,
        ReturnStatement = 235,
        WithStatement = 236,
        SwitchStatement = 237,
        LabeledStatement = 238,
        ThrowStatement = 239,
        TryStatement = 240,
        DebuggerStatement = 241,
        VariableDeclaration = 242,
        VariableDeclarationList = 243,
        FunctionDeclaration = 244,
        ClassDeclaration = 245,
        InterfaceDeclaration = 246,
        TypeAliasDeclaration = 247,
        EnumDeclaration = 248,
        ModuleDeclaration = 249,
        ModuleBlock = 250,
        CaseBlock = 251,
        NamespaceExportDeclaration = 252,
        ImportEqualsDeclaration = 253,
        ImportDeclaration = 254,
        ImportClause = 255,
        NamespaceImport = 256,
        NamedImports = 257,
        ImportSpecifier = 258,
        ExportAssignment = 259,
        ExportDeclaration = 260,
        NamedExports = 261,
        NamespaceExport = 262,
        ExportSpecifier = 263,
        MissingDeclaration = 264,
        ExternalModuleReference = 265,
        JsxElement = 266,
        JsxSelfClosingElement = 267,
        JsxOpeningElement = 268,
        JsxClosingElement = 269,
        JsxFragment = 270,
        JsxOpeningFragment = 271,
        JsxClosingFragment = 272,
        JsxAttribute = 273,
        JsxAttributes = 274,
        JsxSpreadAttribute = 275,
        JsxExpression = 276,
        CaseClause = 277,
        DefaultClause = 278,
        HeritageClause = 279,
        CatchClause = 280,
        PropertyAssignment = 281,
        ShorthandPropertyAssignment = 282,
        SpreadAssignment = 283,
        EnumMember = 284,
        UnparsedPrologue = 285,
        UnparsedPrepend = 286,
        UnparsedText = 287,
        UnparsedInternalText = 288,
        UnparsedSyntheticReference = 289,
        SourceFile = 290,
        Bundle = 291,
        UnparsedSource = 292,
        InputFiles = 293,
        JSDocTypeExpression = 294,
        JSDocAllType = 295,
        JSDocUnknownType = 296,
        JSDocNullableType = 297,
        JSDocNonNullableType = 298,
        JSDocOptionalType = 299,
        JSDocFunctionType = 300,
        JSDocVariadicType = 301,
        JSDocNamepathType = 302,
        JSDocComment = 303,
        JSDocTypeLiteral = 304,
        JSDocSignature = 305,
        JSDocTag = 306,
        JSDocAugmentsTag = 307,
        JSDocAuthorTag = 308,
        JSDocClassTag = 309,
        JSDocPublicTag = 310,
        JSDocPrivateTag = 311,
        JSDocProtectedTag = 312,
        JSDocReadonlyTag = 313,
        JSDocCallbackTag = 314,
        JSDocEnumTag = 315,
        JSDocParameterTag = 316,
        JSDocReturnTag = 317,
        JSDocThisTag = 318,
        JSDocTypeTag = 319,
        JSDocTemplateTag = 320,
        JSDocTypedefTag = 321,
        JSDocPropertyTag = 322,
        SyntaxList = 323,
        NotEmittedStatement = 324,
        PartiallyEmittedExpression = 325,
        CommaListExpression = 326,
        MergeDeclarationMarker = 327,
        EndOfDeclarationMarker = 328,
        SyntheticReferenceExpression = 329,
        Parameters = 330,
        Count = 331,
        FirstAssignment = 62,
        LastAssignment = 74,
        FirstCompoundAssignment = 63,
        LastCompoundAssignment = 74,
        FirstReservedWord = 77,
        LastReservedWord = 112,
        FirstKeyword = 77,
        LastKeyword = 152,
        FirstFutureReservedWord = 113,
        LastFutureReservedWord = 121,
        FirstTypeNode = 168,
        LastTypeNode = 188,
        FirstPunctuation = 18,
        LastPunctuation = 74,
        FirstToken = 0,
        LastToken = 152,
        FirstTriviaToken = 2,
        LastTriviaToken = 7,
        FirstLiteralToken = 8,
        LastLiteralToken = 14,
        FirstTemplateToken = 14,
        LastTemplateToken = 17,
        FirstBinaryOperator = 29,
        LastBinaryOperator = 74,
        FirstStatement = 225,
        LastStatement = 241,
        FirstNode = 153,
        FirstJSDocNode = 294,
        LastJSDocNode = 322,
        FirstJSDocTagNode = 306,
        LastJSDocTagNode = 322,
    };

    enum class NodeFlags
    {
        None = 0,
        Let = 1,
        Const = 2,
        NestedNamespace = 4,
        Synthesized = 8,
        Namespace = 16,
        OptionalChain = 32,
        ExportContext = 64,
        ContainsThis = 128,
        HasImplicitReturn = 256,
        HasExplicitReturn = 512,
        GlobalAugmentation = 1024,
        HasAsyncFunctions = 2048,
        DisallowInContext = 4096,
        YieldContext = 8192,
        DecoratorContext = 16384,
        AwaitContext = 32768,
        ThisNodeHasError = 65536,
        JavaScriptFile = 131072,
        ThisNodeOrAnySubNodesHasError = 262144,
        HasAggregatedChildData = 524288,
        JSDoc = 4194304,
        JsonFile = 33554432,
        BlockScoped = 3,
        ReachabilityCheckFlags = 768,
        ReachabilityAndEmitFlags = 2816,
        ContextFlags = 25358336,
        TypeExcludesFlags = 40960,
    };

    enum class ModifierFlags
    {
        None = 0,
        Export = 1,
        Ambient = 2,
        Public = 4,
        Private = 8,
        Protected = 16,
        Static = 32,
        Readonly = 64,
        Abstract = 128,
        Async = 256,
        Default = 512,
        Const = 2048,
        HasComputedFlags = 536870912,
        AccessibilityModifier = 28,
        ParameterPropertyModifier = 92,
        NonPublicAccessibilityModifier = 24,
        TypeScriptModifier = 2270,
        ExportDefault = 513,
        All = 3071
    };

    enum class JsxFlags
    {
        None = 0,
        /** An element from a named property of the JSX.IntrinsicElements interface */
        IntrinsicNamedElement = 1,
        /** An element inferred from the string index signature of the JSX.IntrinsicElements interface */
        IntrinsicIndexedElement = 2,
        IntrinsicElement = 3
    };

    struct TextRange
    {
        int pos;
        int end;
    };

    class NodeAST
    {
    public:
        using TypePtr = std::shared_ptr<NodeAST>;

        NodeAST(SyntaxKind kind, TextRange range)
            : kind(kind), range(range) {}
        virtual ~NodeAST() = default;

        SyntaxKind getKind() const { return kind; }

        const TextRange &getLoc() { return range; }

    protected:
        TextRange range;
        SyntaxKind kind;
        NodeFlags flags;
        NodeAST *parent;
    };

    class BlockAST : public NodeAST
    {
        std::vector<NodeAST::TypePtr> items;

    public:
        using TypePtr = std::shared_ptr<BlockAST>;

        // TODO: remove it when finish
        BlockAST(TextRange range, std::vector<NodeAST::TypePtr> items)
            : NodeAST(SyntaxKind::Block, range), items(items) {}

        /// LLVM style RTTI
        static bool classof(const NodeAST *N) 
        {
            return N->getKind() == SyntaxKind::Block;
        }               
    };   

    class IdentifierAST : public NodeAST
    {
        std::string name;
    public:
        using TypePtr = std::shared_ptr<IdentifierAST>;

        // TODO: remove it when finish
        IdentifierAST(TextRange range, std::string identifier)
            : NodeAST(SyntaxKind::Identifier, range), name(identifier) {}

        const std::string& getName() const { return name; }

        /// LLVM style RTTI
        static bool classof(const NodeAST *N) 
        {
            return N->getKind() == SyntaxKind::Identifier;
        }            
    };

    class TypeReferenceAST : public NodeAST
    {
        std::string typeName;
        SyntaxKind typeKind;
    public:
        using TypePtr = std::shared_ptr<TypeReferenceAST>;

        TypeReferenceAST(TextRange range, SyntaxKind typeKind)
            : NodeAST(SyntaxKind::Identifier, range), typeKind(typeKind) {}

        TypeReferenceAST(TextRange range, std::string typeName)
            : NodeAST(SyntaxKind::Identifier, range), typeKind(SyntaxKind::Unknown), typeName(typeName) {}

        SyntaxKind getTypeKind() const { return typeKind; }
        const std::string& getTypeName() const { return typeName; }

        /// LLVM style RTTI
        static bool classof(const NodeAST *N) 
        {
            return N->getKind() == SyntaxKind::TypeReference;
        }            
    };    

    class ParameterDeclarationAST : public NodeAST
    {
        IdentifierAST::TypePtr identifier;
        TypeReferenceAST::TypePtr type;
        NodeAST::TypePtr initializer;
        bool dotdotdot;

    public:
        using TypePtr = std::shared_ptr<ParameterDeclarationAST>;

        // TODO: remove it when finish
        ParameterDeclarationAST(TextRange range, IdentifierAST::TypePtr identifier, TypeReferenceAST::TypePtr type, NodeAST::TypePtr initialize)
            : NodeAST(SyntaxKind::FunctionDeclaration, range), identifier(identifier), type(type), initializer(initializer) {}

        const IdentifierAST::TypePtr& getIdentifier() const { return identifier; }
        const TypeReferenceAST::TypePtr& getType() const { return type; }
        const NodeAST::TypePtr& getInitializer() const { return initializer; }
        bool getDotDotDot() { return dotdotdot; }
        void setDotDotDot(bool val) { dotdotdot = val; }

        /// LLVM style RTTI
        static bool classof(const NodeAST *N) 
        {
            return N->getKind() == SyntaxKind::Parameter;
        }
    };

    class ParametersDeclarationAST : public NodeAST
    {
        std::vector<ParameterDeclarationAST::TypePtr> parameters;

    public:
        using TypePtr = std::shared_ptr<ParametersDeclarationAST>;

        // TODO: remove it when finish
        ParametersDeclarationAST(TextRange range, std::vector<ParameterDeclarationAST::TypePtr> parameters)
            : NodeAST(SyntaxKind::Parameters, range), parameters(parameters) {}

        /// LLVM style RTTI
        static bool classof(const NodeAST *N) 
        {
            return N->getKind() == SyntaxKind::Parameters;
        }          
    };

    class FunctionDeclarationAST : public NodeAST
    {
        IdentifierAST::TypePtr identifier;
        ParametersDeclarationAST::TypePtr parameters;
        TypeReferenceAST::TypePtr typeReference;

    public:
        using TypePtr = std::shared_ptr<FunctionDeclarationAST>;

        // TODO: remove it when finish
        FunctionDeclarationAST(TextRange range, IdentifierAST::TypePtr identifier, ParametersDeclarationAST::TypePtr parameters, TypeReferenceAST::TypePtr typeReference)
            : NodeAST(SyntaxKind::FunctionDeclaration, range), identifier(identifier), parameters(parameters), typeReference(typeReference) {}

        const IdentifierAST::TypePtr& getIdentifier() const { return identifier; }
        const ParametersDeclarationAST::TypePtr& getParameters() const { return parameters; }

        /// LLVM style RTTI
        static bool classof(const NodeAST *N) 
        {
            return N->getKind() == SyntaxKind::FunctionDeclaration;
        }
    };

    class ModuleBlockAST : public NodeAST
    {
        std::vector<NodeAST::TypePtr> items;

    public:
        using TypePtr = std::shared_ptr<ModuleBlockAST>;

        ModuleBlockAST(TextRange range, std::vector<NodeAST::TypePtr> items)
            : NodeAST(SyntaxKind::ModuleBlock, range), items(items) {}

        const std::vector<NodeAST::TypePtr>& getItems() const { return items; }

        /// LLVM style RTTI
        static bool classof(const NodeAST *N) 
        {
            return N->getKind() == SyntaxKind::ModuleBlock;
        }               
    };   

    class ModuleAST : public NodeAST
    {
        ModuleBlockAST::TypePtr block;

    public:
        using TypePtr = std::shared_ptr<ModuleAST>;

        ModuleAST() : NodeAST(SyntaxKind::ModuleDeclaration, TextRange()) {}        

        ModuleAST(TextRange range, ModuleBlockAST::TypePtr block)
            : NodeAST(SyntaxKind::ModuleDeclaration, range), block(block) {}

        auto begin() -> decltype(block.get()->getItems().begin()) { return block.get()->getItems().begin(); }
        auto end() -> decltype(block.get()->getItems().end()) { return block.get()->getItems().end(); }

        /// LLVM style RTTI
        static bool classof(const NodeAST *N) 
        {
            return N->getKind() == SyntaxKind::ModuleDeclaration;
        }         
    };

} // namespace typescript

#endif // TYPESCRIPT_AST_H_
