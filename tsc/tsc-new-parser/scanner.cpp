#include "scanner.h"
#include "core.h"
#include "utilities.h"

namespace ts
{
    class ScannerImpl
    {
    public:
        ScannerImpl() = default;

    private:
        /* @internal */
        auto tokenIsIdentifierOrKeyword(SyntaxKind token) -> boolean
        {
            return token >= SyntaxKind::Identifier;
        }

        /* @internal */
        auto tokenIsIdentifierOrKeywordOrGreaterThan(SyntaxKind token) -> boolean
        {
            return token == SyntaxKind::GreaterThanToken || tokenIsIdentifierOrKeyword(token);
        }

        std::map<string, SyntaxKind> textToKeyword = {
            {S("abstract"), SyntaxKind::AbstractKeyword},
            {S("any"), SyntaxKind::AnyKeyword},
            {S("as"), SyntaxKind::AsKeyword},
            {S("asserts"), SyntaxKind::AssertsKeyword},
            {S("bigint"), SyntaxKind::BigIntKeyword},
            {S("boolean"), SyntaxKind::BooleanKeyword},
            {S("break"), SyntaxKind::BreakKeyword},
            {S("case"), SyntaxKind::CaseKeyword},
            {S("catch"), SyntaxKind::CatchKeyword},
            {S("class"), SyntaxKind::ClassKeyword},
            {S("continue"), SyntaxKind::ContinueKeyword},
            {S("const"), SyntaxKind::ConstKeyword},
            {S("constructor"), SyntaxKind::ConstructorKeyword},
            {S("debugger"), SyntaxKind::DebuggerKeyword},
            {S("declare"), SyntaxKind::DeclareKeyword},
            {S("default"), SyntaxKind::DefaultKeyword},
            {S("delete"), SyntaxKind::DeleteKeyword},
            {S("do"), SyntaxKind::DoKeyword},
            {S("else"), SyntaxKind::ElseKeyword},
            {S("enum"), SyntaxKind::EnumKeyword},
            {S("export"), SyntaxKind::ExportKeyword},
            {S("extends"), SyntaxKind::ExtendsKeyword},
            {S("false"), SyntaxKind::FalseKeyword},
            {S("finally"), SyntaxKind::FinallyKeyword},
            {S("for"), SyntaxKind::ForKeyword},
            {S("from"), SyntaxKind::FromKeyword},
            {S("function"), SyntaxKind::FunctionKeyword},
            {S("get"), SyntaxKind::GetKeyword},
            {S("if"), SyntaxKind::IfKeyword},
            {S("implements"), SyntaxKind::ImplementsKeyword},
            {S("import"), SyntaxKind::ImportKeyword},
            {S("in"), SyntaxKind::InKeyword},
            {S("infer"), SyntaxKind::InferKeyword},
            {S("instanceof"), SyntaxKind::InstanceOfKeyword},
            {S("interface"), SyntaxKind::InterfaceKeyword},
            {S("intrinsic"), SyntaxKind::IntrinsicKeyword},
            {S("is"), SyntaxKind::IsKeyword},
            {S("keyof"), SyntaxKind::KeyOfKeyword},
            {S("let"), SyntaxKind::LetKeyword},
            {S("module"), SyntaxKind::ModuleKeyword},
            {S("namespace"), SyntaxKind::NamespaceKeyword},
            {S("never"), SyntaxKind::NeverKeyword},
            {S("new"), SyntaxKind::NewKeyword},
            {S("null"), SyntaxKind::NullKeyword},
            {S("number"), SyntaxKind::NumberKeyword},
            {S("object"), SyntaxKind::ObjectKeyword},
            {S("package"), SyntaxKind::PackageKeyword},
            {S("private"), SyntaxKind::PrivateKeyword},
            {S("protected"), SyntaxKind::ProtectedKeyword},
            {S("public"), SyntaxKind::PublicKeyword},
            {S("readonly"), SyntaxKind::ReadonlyKeyword},
            {S("require"), SyntaxKind::RequireKeyword},
            {S("global"), SyntaxKind::GlobalKeyword},
            {S("return"), SyntaxKind::ReturnKeyword},
            {S("set"), SyntaxKind::SetKeyword},
            {S("static"), SyntaxKind::StaticKeyword},
            {S("string"), SyntaxKind::StringKeyword},
            {S("super"), SyntaxKind::SuperKeyword},
            {S("switch"), SyntaxKind::SwitchKeyword},
            {S("symbol"), SyntaxKind::SymbolKeyword},
            {S("this"), SyntaxKind::ThisKeyword},
            {S("throw"), SyntaxKind::ThrowKeyword},
            {S("true"), SyntaxKind::TrueKeyword},
            {S("try"), SyntaxKind::TryKeyword},
            {S("type"), SyntaxKind::TypeKeyword},
            {S("typeof"), SyntaxKind::TypeOfKeyword},
            {S("undefined"), SyntaxKind::UndefinedKeyword},
            {S("unique"), SyntaxKind::UniqueKeyword},
            {S("unknown"), SyntaxKind::UnknownKeyword},
            {S("var"), SyntaxKind::VarKeyword},
            {S("void"), SyntaxKind::VoidKeyword},
            {S("while"), SyntaxKind::WhileKeyword},
            {S("with"), SyntaxKind::WithKeyword},
            {S("yield"), SyntaxKind::YieldKeyword},
            {S("async"), SyntaxKind::AsyncKeyword},
            {S("await"), SyntaxKind::AwaitKeyword},
            {S("of"), SyntaxKind::OfKeyword}};

        std::map<string, SyntaxKind> textToToken = {
            {S("abstract"), SyntaxKind::AbstractKeyword},
            {S("any"), SyntaxKind::AnyKeyword},
            {S("as"), SyntaxKind::AsKeyword},
            {S("asserts"), SyntaxKind::AssertsKeyword},
            {S("bigint"), SyntaxKind::BigIntKeyword},
            {S("boolean"), SyntaxKind::BooleanKeyword},
            {S("break"), SyntaxKind::BreakKeyword},
            {S("case"), SyntaxKind::CaseKeyword},
            {S("catch"), SyntaxKind::CatchKeyword},
            {S("class"), SyntaxKind::ClassKeyword},
            {S("continue"), SyntaxKind::ContinueKeyword},
            {S("const"), SyntaxKind::ConstKeyword},
            {S("constructor"), SyntaxKind::ConstructorKeyword},
            {S("debugger"), SyntaxKind::DebuggerKeyword},
            {S("declare"), SyntaxKind::DeclareKeyword},
            {S("default"), SyntaxKind::DefaultKeyword},
            {S("delete"), SyntaxKind::DeleteKeyword},
            {S("do"), SyntaxKind::DoKeyword},
            {S("else"), SyntaxKind::ElseKeyword},
            {S("enum"), SyntaxKind::EnumKeyword},
            {S("export"), SyntaxKind::ExportKeyword},
            {S("extends"), SyntaxKind::ExtendsKeyword},
            {S("false"), SyntaxKind::FalseKeyword},
            {S("finally"), SyntaxKind::FinallyKeyword},
            {S("for"), SyntaxKind::ForKeyword},
            {S("from"), SyntaxKind::FromKeyword},
            {S("function"), SyntaxKind::FunctionKeyword},
            {S("get"), SyntaxKind::GetKeyword},
            {S("if"), SyntaxKind::IfKeyword},
            {S("implements"), SyntaxKind::ImplementsKeyword},
            {S("import"), SyntaxKind::ImportKeyword},
            {S("in"), SyntaxKind::InKeyword},
            {S("infer"), SyntaxKind::InferKeyword},
            {S("instanceof"), SyntaxKind::InstanceOfKeyword},
            {S("interface"), SyntaxKind::InterfaceKeyword},
            {S("intrinsic"), SyntaxKind::IntrinsicKeyword},
            {S("is"), SyntaxKind::IsKeyword},
            {S("keyof"), SyntaxKind::KeyOfKeyword},
            {S("let"), SyntaxKind::LetKeyword},
            {S("module"), SyntaxKind::ModuleKeyword},
            {S("namespace"), SyntaxKind::NamespaceKeyword},
            {S("never"), SyntaxKind::NeverKeyword},
            {S("new"), SyntaxKind::NewKeyword},
            {S("null"), SyntaxKind::NullKeyword},
            {S("number"), SyntaxKind::NumberKeyword},
            {S("object"), SyntaxKind::ObjectKeyword},
            {S("package"), SyntaxKind::PackageKeyword},
            {S("private"), SyntaxKind::PrivateKeyword},
            {S("protected"), SyntaxKind::ProtectedKeyword},
            {S("public"), SyntaxKind::PublicKeyword},
            {S("readonly"), SyntaxKind::ReadonlyKeyword},
            {S("require"), SyntaxKind::RequireKeyword},
            {S("global"), SyntaxKind::GlobalKeyword},
            {S("return"), SyntaxKind::ReturnKeyword},
            {S("set"), SyntaxKind::SetKeyword},
            {S("static"), SyntaxKind::StaticKeyword},
            {S("string"), SyntaxKind::StringKeyword},
            {S("super"), SyntaxKind::SuperKeyword},
            {S("switch"), SyntaxKind::SwitchKeyword},
            {S("symbol"), SyntaxKind::SymbolKeyword},
            {S("this"), SyntaxKind::ThisKeyword},
            {S("throw"), SyntaxKind::ThrowKeyword},
            {S("true"), SyntaxKind::TrueKeyword},
            {S("try"), SyntaxKind::TryKeyword},
            {S("type"), SyntaxKind::TypeKeyword},
            {S("typeof"), SyntaxKind::TypeOfKeyword},
            {S("undefined"), SyntaxKind::UndefinedKeyword},
            {S("unique"), SyntaxKind::UniqueKeyword},
            {S("unknown"), SyntaxKind::UnknownKeyword},
            {S("var"), SyntaxKind::VarKeyword},
            {S("void"), SyntaxKind::VoidKeyword},
            {S("while"), SyntaxKind::WhileKeyword},
            {S("with"), SyntaxKind::WithKeyword},
            {S("yield"), SyntaxKind::YieldKeyword},
            {S("async"), SyntaxKind::AsyncKeyword},
            {S("await"), SyntaxKind::AwaitKeyword},
            {S("of"), SyntaxKind::OfKeyword},

            {S("{"), SyntaxKind::OpenBraceToken},
            {S("}"), SyntaxKind::CloseBraceToken},
            {S("("), SyntaxKind::OpenParenToken},
            {S(")"), SyntaxKind::CloseParenToken},
            {S("["), SyntaxKind::OpenBracketToken},
            {S("]"), SyntaxKind::CloseBracketToken},
            {S("."), SyntaxKind::DotToken},
            {S("..."), SyntaxKind::DotDotDotToken},
            {S(";"), SyntaxKind::SemicolonToken},
            {S("),"), SyntaxKind::CommaToken},
            {S("<"), SyntaxKind::LessThanToken},
            {S(">"), SyntaxKind::GreaterThanToken},
            {S("<="), SyntaxKind::LessThanEqualsToken},
            {S(">="), SyntaxKind::GreaterThanEqualsToken},
            {S("=="), SyntaxKind::EqualsEqualsToken},
            {S("!="), SyntaxKind::ExclamationEqualsToken},
            {S("==="), SyntaxKind::EqualsEqualsEqualsToken},
            {S("!="), SyntaxKind::ExclamationEqualsEqualsToken},
            {S("=>"), SyntaxKind::EqualsGreaterThanToken},
            {S("+"), SyntaxKind::PlusToken},
            {S("-"), SyntaxKind::MinusToken},
            {S("**"), SyntaxKind::AsteriskAsteriskToken},
            {S("*"), SyntaxKind::AsteriskToken},
            {S("/"), SyntaxKind::SlashToken},
            {S("%"), SyntaxKind::PercentToken},
            {S("++"), SyntaxKind::PlusPlusToken},
            {S("--"), SyntaxKind::MinusMinusToken},
            {S("<<"), SyntaxKind::LessThanLessThanToken},
            {S("</"), SyntaxKind::LessThanSlashToken},
            {S(">>"), SyntaxKind::GreaterThanGreaterThanToken},
            {S(">>>"), SyntaxKind::GreaterThanGreaterThanGreaterThanToken},
            {S("&"), SyntaxKind::AmpersandToken},
            {S("|"), SyntaxKind::BarToken},
            {S("^"), SyntaxKind::CaretToken},
            {S("!"), SyntaxKind::ExclamationToken},
            {S("~"), SyntaxKind::TildeToken},
            {S("&&"), SyntaxKind::AmpersandAmpersandToken},
            {S("||"), SyntaxKind::BarBarToken},
            {S("?"), SyntaxKind::QuestionToken},
            {S("??"), SyntaxKind::QuestionQuestionToken},
            {S("?."), SyntaxKind::QuestionDotToken},
            {S("),"), SyntaxKind::ColonToken},
            {S("="), SyntaxKind::EqualsToken},
            {S("+="), SyntaxKind::PlusEqualsToken},
            {S("-="), SyntaxKind::MinusEqualsToken},
            {S("*="), SyntaxKind::AsteriskEqualsToken},
            {S("**="), SyntaxKind::AsteriskAsteriskEqualsToken},
            {S("/="), SyntaxKind::SlashEqualsToken},
            {S("%="), SyntaxKind::PercentEqualsToken},
            {S("<<="), SyntaxKind::LessThanLessThanEqualsToken},
            {S(">>="), SyntaxKind::GreaterThanGreaterThanEqualsToken},
            {S(">>>="), SyntaxKind::GreaterThanGreaterThanGreaterThanEqualsToken},
            {S("&="), SyntaxKind::AmpersandEqualsToken},
            {S("|="), SyntaxKind::BarEqualsToken},
            {S("^="), SyntaxKind::CaretEqualsToken},
            {S("||="), SyntaxKind::BarBarEqualsToken},
            {S("&&="), SyntaxKind::AmpersandAmpersandEqualsToken},
            {S("??="), SyntaxKind::QuestionQuestionEqualsToken},
            {S("@"), SyntaxKind::AtToken},
            {S("`"), SyntaxKind::BacktickToken}};

        std::map<SyntaxKind, string> tokenToText = {
            {SyntaxKind::Unknown, S("Unknown")},
            {SyntaxKind::EndOfFileToken, S("EndOfFileToken")},
            {SyntaxKind::SingleLineCommentTrivia, S("SingleLineCommentTrivia")},
            {SyntaxKind::MultiLineCommentTrivia, S("MultiLineCommentTrivia")},
            {SyntaxKind::NewLineTrivia, S("NewLineTrivia")},
            {SyntaxKind::WhitespaceTrivia, S("WhitespaceTrivia")},
            {SyntaxKind::ShebangTrivia, S("ShebangTrivia")},
            {SyntaxKind::ConflictMarkerTrivia, S("ConflictMarkerTrivia")},
            {SyntaxKind::NumericLiteral, S("NumericLiteral")},
            {SyntaxKind::BigIntLiteral, S("BigIntLiteral")},
            {SyntaxKind::StringLiteral, S("StringLiteral")},
            {SyntaxKind::JsxText, S("JsxText")},
            {SyntaxKind::JsxTextAllWhiteSpaces, S("JsxTextAllWhiteSpaces")},
            {SyntaxKind::RegularExpressionLiteral, S("RegularExpressionLiteral")},
            {SyntaxKind::NoSubstitutionTemplateLiteral, S("NoSubstitutionTemplateLiteral")},
            {SyntaxKind::TemplateHead, S("TemplateHead")},
            {SyntaxKind::TemplateMiddle, S("TemplateMiddle")},
            {SyntaxKind::TemplateTail, S("TemplateTail")},
            {SyntaxKind::OpenBraceToken, S("OpenBraceToken")},
            {SyntaxKind::CloseBraceToken, S("CloseBraceToken")},
            {SyntaxKind::OpenParenToken, S("OpenParenToken")},
            {SyntaxKind::CloseParenToken, S("CloseParenToken")},
            {SyntaxKind::OpenBracketToken, S("OpenBracketToken")},
            {SyntaxKind::CloseBracketToken, S("CloseBracketToken")},
            {SyntaxKind::DotToken, S("DotToken")},
            {SyntaxKind::DotDotDotToken, S("DotDotDotToken")},
            {SyntaxKind::SemicolonToken, S("SemicolonToken")},
            {SyntaxKind::CommaToken, S("CommaToken")},
            {SyntaxKind::QuestionDotToken, S("QuestionDotToken")},
            {SyntaxKind::LessThanToken, S("LessThanToken")},
            {SyntaxKind::LessThanSlashToken, S("LessThanSlashToken")},
            {SyntaxKind::GreaterThanToken, S("GreaterThanToken")},
            {SyntaxKind::LessThanEqualsToken, S("LessThanEqualsToken")},
            {SyntaxKind::GreaterThanEqualsToken, S("GreaterThanEqualsToken")},
            {SyntaxKind::EqualsEqualsToken, S("EqualsEqualsToken")},
            {SyntaxKind::ExclamationEqualsToken, S("ExclamationEqualsToken")},
            {SyntaxKind::EqualsEqualsEqualsToken, S("EqualsEqualsEqualsToken")},
            {SyntaxKind::ExclamationEqualsEqualsToken, S("ExclamationEqualsEqualsToken")},
            {SyntaxKind::EqualsGreaterThanToken, S("EqualsGreaterThanToken")},
            {SyntaxKind::PlusToken, S("PlusToken")},
            {SyntaxKind::MinusToken, S("MinusToken")},
            {SyntaxKind::AsteriskToken, S("AsteriskToken")},
            {SyntaxKind::AsteriskAsteriskToken, S("AsteriskAsteriskToken")},
            {SyntaxKind::SlashToken, S("SlashToken")},
            {SyntaxKind::PercentToken, S("PercentToken")},
            {SyntaxKind::PlusPlusToken, S("PlusPlusToken")},
            {SyntaxKind::MinusMinusToken, S("MinusMinusToken")},
            {SyntaxKind::LessThanLessThanToken, S("LessThanLessThanToken")},
            {SyntaxKind::GreaterThanGreaterThanToken, S("GreaterThanGreaterThanToken")},
            {SyntaxKind::GreaterThanGreaterThanGreaterThanToken, S("GreaterThanGreaterThanGreaterThanToken")},
            {SyntaxKind::AmpersandToken, S("AmpersandToken")},
            {SyntaxKind::BarToken, S("BarToken")},
            {SyntaxKind::CaretToken, S("CaretToken")},
            {SyntaxKind::ExclamationToken, S("ExclamationToken")},
            {SyntaxKind::TildeToken, S("TildeToken")},
            {SyntaxKind::AmpersandAmpersandToken, S("AmpersandAmpersandToken")},
            {SyntaxKind::BarBarToken, S("BarBarToken")},
            {SyntaxKind::QuestionToken, S("QuestionToken")},
            {SyntaxKind::ColonToken, S("ColonToken")},
            {SyntaxKind::AtToken, S("AtToken")},
            {SyntaxKind::QuestionQuestionToken, S("QuestionQuestionToken")},
            {SyntaxKind::BacktickToken, S("BacktickToken")},
            {SyntaxKind::EqualsToken, S("EqualsToken")},
            {SyntaxKind::PlusEqualsToken, S("PlusEqualsToken")},
            {SyntaxKind::MinusEqualsToken, S("MinusEqualsToken")},
            {SyntaxKind::AsteriskEqualsToken, S("AsteriskEqualsToken")},
            {SyntaxKind::AsteriskAsteriskEqualsToken, S("AsteriskAsteriskEqualsToken")},
            {SyntaxKind::SlashEqualsToken, S("SlashEqualsToken")},
            {SyntaxKind::PercentEqualsToken, S("PercentEqualsToken")},
            {SyntaxKind::LessThanLessThanEqualsToken, S("LessThanLessThanEqualsToken")},
            {SyntaxKind::GreaterThanGreaterThanEqualsToken, S("GreaterThanGreaterThanEqualsToken")},
            {SyntaxKind::GreaterThanGreaterThanGreaterThanEqualsToken, S("GreaterThanGreaterThanGreaterThanEqualsToken")},
            {SyntaxKind::AmpersandEqualsToken, S("AmpersandEqualsToken")},
            {SyntaxKind::BarEqualsToken, S("BarEqualsToken")},
            {SyntaxKind::BarBarEqualsToken, S("BarBarEqualsToken")},
            {SyntaxKind::AmpersandAmpersandEqualsToken, S("AmpersandAmpersandEqualsToken")},
            {SyntaxKind::QuestionQuestionEqualsToken, S("QuestionQuestionEqualsToken")},
            {SyntaxKind::CaretEqualsToken, S("CaretEqualsToken")},
            {SyntaxKind::Identifier, S("Identifier")},
            {SyntaxKind::PrivateIdentifier, S("PrivateIdentifier")},
            {SyntaxKind::BreakKeyword, S("BreakKeyword")},
            {SyntaxKind::CaseKeyword, S("CaseKeyword")},
            {SyntaxKind::CatchKeyword, S("CatchKeyword")},
            {SyntaxKind::ClassKeyword, S("ClassKeyword")},
            {SyntaxKind::ConstKeyword, S("ConstKeyword")},
            {SyntaxKind::ContinueKeyword, S("ContinueKeyword")},
            {SyntaxKind::DebuggerKeyword, S("DebuggerKeyword")},
            {SyntaxKind::DefaultKeyword, S("DefaultKeyword")},
            {SyntaxKind::DeleteKeyword, S("DeleteKeyword")},
            {SyntaxKind::DoKeyword, S("DoKeyword")},
            {SyntaxKind::ElseKeyword, S("ElseKeyword")},
            {SyntaxKind::EnumKeyword, S("EnumKeyword")},
            {SyntaxKind::ExportKeyword, S("ExportKeyword")},
            {SyntaxKind::ExtendsKeyword, S("ExtendsKeyword")},
            {SyntaxKind::FalseKeyword, S("FalseKeyword")},
            {SyntaxKind::FinallyKeyword, S("FinallyKeyword")},
            {SyntaxKind::ForKeyword, S("ForKeyword")},
            {SyntaxKind::FunctionKeyword, S("FunctionKeyword")},
            {SyntaxKind::IfKeyword, S("IfKeyword")},
            {SyntaxKind::ImportKeyword, S("ImportKeyword")},
            {SyntaxKind::InKeyword, S("InKeyword")},
            {SyntaxKind::InstanceOfKeyword, S("InstanceOfKeyword")},
            {SyntaxKind::NewKeyword, S("NewKeyword")},
            {SyntaxKind::NullKeyword, S("NullKeyword")},
            {SyntaxKind::ReturnKeyword, S("ReturnKeyword")},
            {SyntaxKind::SuperKeyword, S("SuperKeyword")},
            {SyntaxKind::SwitchKeyword, S("SwitchKeyword")},
            {SyntaxKind::ThisKeyword, S("ThisKeyword")},
            {SyntaxKind::ThrowKeyword, S("ThrowKeyword")},
            {SyntaxKind::TrueKeyword, S("TrueKeyword")},
            {SyntaxKind::TryKeyword, S("TryKeyword")},
            {SyntaxKind::TypeOfKeyword, S("TypeOfKeyword")},
            {SyntaxKind::VarKeyword, S("VarKeyword")},
            {SyntaxKind::VoidKeyword, S("VoidKeyword")},
            {SyntaxKind::WhileKeyword, S("WhileKeyword")},
            {SyntaxKind::WithKeyword, S("WithKeyword")},
            {SyntaxKind::ImplementsKeyword, S("ImplementsKeyword")},
            {SyntaxKind::InterfaceKeyword, S("InterfaceKeyword")},
            {SyntaxKind::LetKeyword, S("LetKeyword")},
            {SyntaxKind::PackageKeyword, S("PackageKeyword")},
            {SyntaxKind::PrivateKeyword, S("PrivateKeyword")},
            {SyntaxKind::ProtectedKeyword, S("ProtectedKeyword")},
            {SyntaxKind::PublicKeyword, S("PublicKeyword")},
            {SyntaxKind::StaticKeyword, S("StaticKeyword")},
            {SyntaxKind::YieldKeyword, S("YieldKeyword")},
            {SyntaxKind::AbstractKeyword, S("AbstractKeyword")},
            {SyntaxKind::AsKeyword, S("AsKeyword")},
            {SyntaxKind::AssertsKeyword, S("AssertsKeyword")},
            {SyntaxKind::AnyKeyword, S("AnyKeyword")},
            {SyntaxKind::AsyncKeyword, S("AsyncKeyword")},
            {SyntaxKind::AwaitKeyword, S("AwaitKeyword")},
            {SyntaxKind::BooleanKeyword, S("BooleanKeyword")},
            {SyntaxKind::ConstructorKeyword, S("ConstructorKeyword")},
            {SyntaxKind::DeclareKeyword, S("DeclareKeyword")},
            {SyntaxKind::GetKeyword, S("GetKeyword")},
            {SyntaxKind::InferKeyword, S("InferKeyword")},
            {SyntaxKind::IntrinsicKeyword, S("IntrinsicKeyword")},
            {SyntaxKind::IsKeyword, S("IsKeyword")},
            {SyntaxKind::KeyOfKeyword, S("KeyOfKeyword")},
            {SyntaxKind::ModuleKeyword, S("ModuleKeyword")},
            {SyntaxKind::NamespaceKeyword, S("NamespaceKeyword")},
            {SyntaxKind::NeverKeyword, S("NeverKeyword")},
            {SyntaxKind::ReadonlyKeyword, S("ReadonlyKeyword")},
            {SyntaxKind::RequireKeyword, S("RequireKeyword")},
            {SyntaxKind::NumberKeyword, S("NumberKeyword")},
            {SyntaxKind::ObjectKeyword, S("ObjectKeyword")},
            {SyntaxKind::SetKeyword, S("SetKeyword")},
            {SyntaxKind::StringKeyword, S("StringKeyword")},
            {SyntaxKind::SymbolKeyword, S("SymbolKeyword")},
            {SyntaxKind::TypeKeyword, S("TypeKeyword")},
            {SyntaxKind::UndefinedKeyword, S("UndefinedKeyword")},
            {SyntaxKind::UniqueKeyword, S("UniqueKeyword")},
            {SyntaxKind::UnknownKeyword, S("UnknownKeyword")},
            {SyntaxKind::FromKeyword, S("FromKeyword")},
            {SyntaxKind::GlobalKeyword, S("GlobalKeyword")},
            {SyntaxKind::BigIntKeyword, S("BigIntKeyword")},
            {SyntaxKind::OfKeyword, S("OfKeyword")}, 
            {SyntaxKind::QualifiedName, S("QualifiedName")},
            {SyntaxKind::ComputedPropertyName, S("ComputedPropertyName")},
            {SyntaxKind::TypeParameter, S("TypeParameter")},
            {SyntaxKind::Parameter, S("Parameter")},
            {SyntaxKind::Decorator, S("Decorator")},
            {SyntaxKind::PropertySignature, S("PropertySignature")},
            {SyntaxKind::PropertyDeclaration, S("PropertyDeclaration")},
            {SyntaxKind::MethodSignature, S("MethodSignature")},
            {SyntaxKind::MethodDeclaration, S("MethodDeclaration")},
            {SyntaxKind::Constructor, S("Constructor")},
            {SyntaxKind::GetAccessor, S("GetAccessor")},
            {SyntaxKind::SetAccessor, S("SetAccessor")},
            {SyntaxKind::CallSignature, S("CallSignature")},
            {SyntaxKind::ConstructSignature, S("ConstructSignature")},
            {SyntaxKind::IndexSignature, S("IndexSignature")},
            {SyntaxKind::TypePredicate, S("TypePredicate")},
            {SyntaxKind::TypeReference, S("TypeReference")},
            {SyntaxKind::FunctionType, S("FunctionType")},
            {SyntaxKind::ConstructorType, S("ConstructorType")},
            {SyntaxKind::TypeQuery, S("TypeQuery")},
            {SyntaxKind::TypeLiteral, S("TypeLiteral")},
            {SyntaxKind::ArrayType, S("ArrayType")},
            {SyntaxKind::TupleType, S("TupleType")},
            {SyntaxKind::OptionalType, S("OptionalType")},
            {SyntaxKind::RestType, S("RestType")},
            {SyntaxKind::UnionType, S("UnionType")},
            {SyntaxKind::IntersectionType, S("IntersectionType")},
            {SyntaxKind::ConditionalType, S("ConditionalType")},
            {SyntaxKind::InferType, S("InferType")},
            {SyntaxKind::ParenthesizedType, S("ParenthesizedType")},
            {SyntaxKind::ThisType, S("ThisType")},
            {SyntaxKind::TypeOperator, S("TypeOperator")},
            {SyntaxKind::IndexedAccessType, S("IndexedAccessType")},
            {SyntaxKind::MappedType, S("MappedType")},
            {SyntaxKind::LiteralType, S("LiteralType")},
            {SyntaxKind::NamedTupleMember, S("NamedTupleMember")},
            {SyntaxKind::TemplateLiteralType, S("TemplateLiteralType")},
            {SyntaxKind::TemplateLiteralTypeSpan, S("TemplateLiteralTypeSpan")},
            {SyntaxKind::ImportType, S("ImportType")},
            {SyntaxKind::ObjectBindingPattern, S("ObjectBindingPattern")},
            {SyntaxKind::ArrayBindingPattern, S("ArrayBindingPattern")},
            {SyntaxKind::BindingElement, S("BindingElement")},
            {SyntaxKind::ArrayLiteralExpression, S("ArrayLiteralExpression")},
            {SyntaxKind::ObjectLiteralExpression, S("ObjectLiteralExpression")},
            {SyntaxKind::PropertyAccessExpression, S("PropertyAccessExpression")},
            {SyntaxKind::ElementAccessExpression, S("ElementAccessExpression")},
            {SyntaxKind::CallExpression, S("CallExpression")},
            {SyntaxKind::NewExpression, S("NewExpression")},
            {SyntaxKind::TaggedTemplateExpression, S("TaggedTemplateExpression")},
            {SyntaxKind::TypeAssertionExpression, S("TypeAssertionExpression")},
            {SyntaxKind::ParenthesizedExpression, S("ParenthesizedExpression")},
            {SyntaxKind::FunctionExpression, S("FunctionExpression")},
            {SyntaxKind::ArrowFunction, S("ArrowFunction")},
            {SyntaxKind::DeleteExpression, S("DeleteExpression")},
            {SyntaxKind::TypeOfExpression, S("TypeOfExpression")},
            {SyntaxKind::VoidExpression, S("VoidExpression")},
            {SyntaxKind::AwaitExpression, S("AwaitExpression")},
            {SyntaxKind::PrefixUnaryExpression, S("PrefixUnaryExpression")},
            {SyntaxKind::PostfixUnaryExpression, S("PostfixUnaryExpression")},
            {SyntaxKind::BinaryExpression, S("BinaryExpression")},
            {SyntaxKind::ConditionalExpression, S("ConditionalExpression")},
            {SyntaxKind::TemplateExpression, S("TemplateExpression")},
            {SyntaxKind::YieldExpression, S("YieldExpression")},
            {SyntaxKind::SpreadElement, S("SpreadElement")},
            {SyntaxKind::ClassExpression, S("ClassExpression")},
            {SyntaxKind::OmittedExpression, S("OmittedExpression")},
            {SyntaxKind::ExpressionWithTypeArguments, S("ExpressionWithTypeArguments")},
            {SyntaxKind::AsExpression, S("AsExpression")},
            {SyntaxKind::NonNullExpression, S("NonNullExpression")},
            {SyntaxKind::MetaProperty, S("MetaProperty")},
            {SyntaxKind::SyntheticExpression, S("SyntheticExpression")},
            {SyntaxKind::TemplateSpan, S("TemplateSpan")},
            {SyntaxKind::SemicolonClassElement, S("SemicolonClassElement")},
            {SyntaxKind::Block, S("Block")},
            {SyntaxKind::EmptyStatement, S("EmptyStatement")},
            {SyntaxKind::VariableStatement, S("VariableStatement")},
            {SyntaxKind::ExpressionStatement, S("ExpressionStatement")},
            {SyntaxKind::IfStatement, S("IfStatement")},
            {SyntaxKind::DoStatement, S("DoStatement")},
            {SyntaxKind::WhileStatement, S("WhileStatement")},
            {SyntaxKind::ForStatement, S("ForStatement")},
            {SyntaxKind::ForInStatement, S("ForInStatement")},
            {SyntaxKind::ForOfStatement, S("ForOfStatement")},
            {SyntaxKind::ContinueStatement, S("ContinueStatement")},
            {SyntaxKind::BreakStatement, S("BreakStatement")},
            {SyntaxKind::ReturnStatement, S("ReturnStatement")},
            {SyntaxKind::WithStatement, S("WithStatement")},
            {SyntaxKind::SwitchStatement, S("SwitchStatement")},
            {SyntaxKind::LabeledStatement, S("LabeledStatement")},
            {SyntaxKind::ThrowStatement, S("ThrowStatement")},
            {SyntaxKind::TryStatement, S("TryStatement")},
            {SyntaxKind::DebuggerStatement, S("DebuggerStatement")},
            {SyntaxKind::VariableDeclaration, S("VariableDeclaration")},
            {SyntaxKind::VariableDeclarationList, S("VariableDeclarationList")},
            {SyntaxKind::FunctionDeclaration, S("FunctionDeclaration")},
            {SyntaxKind::ClassDeclaration, S("ClassDeclaration")},
            {SyntaxKind::InterfaceDeclaration, S("InterfaceDeclaration")},
            {SyntaxKind::TypeAliasDeclaration, S("TypeAliasDeclaration")},
            {SyntaxKind::EnumDeclaration, S("EnumDeclaration")},
            {SyntaxKind::ModuleDeclaration, S("ModuleDeclaration")},
            {SyntaxKind::ModuleBlock, S("ModuleBlock")},
            {SyntaxKind::CaseBlock, S("CaseBlock")},
            {SyntaxKind::NamespaceExportDeclaration, S("NamespaceExportDeclaration")},
            {SyntaxKind::ImportEqualsDeclaration, S("ImportEqualsDeclaration")},
            {SyntaxKind::ImportDeclaration, S("ImportDeclaration")},
            {SyntaxKind::ImportClause, S("ImportClause")},
            {SyntaxKind::NamespaceImport, S("NamespaceImport")},
            {SyntaxKind::NamedImports, S("NamedImports")},
            {SyntaxKind::ImportSpecifier, S("ImportSpecifier")},
            {SyntaxKind::ExportAssignment, S("ExportAssignment")},
            {SyntaxKind::ExportDeclaration, S("ExportDeclaration")},
            {SyntaxKind::NamedExports, S("NamedExports")},
            {SyntaxKind::NamespaceExport, S("NamespaceExport")},
            {SyntaxKind::ExportSpecifier, S("ExportSpecifier")},
            {SyntaxKind::MissingDeclaration, S("MissingDeclaration")},
            {SyntaxKind::ExternalModuleReference, S("ExternalModuleReference")},
            {SyntaxKind::JsxElement, S("JsxElement")},
            {SyntaxKind::JsxSelfClosingElement, S("JsxSelfClosingElement")},
            {SyntaxKind::JsxOpeningElement, S("JsxOpeningElement")},
            {SyntaxKind::JsxClosingElement, S("JsxClosingElement")},
            {SyntaxKind::JsxFragment, S("JsxFragment")},
            {SyntaxKind::JsxOpeningFragment, S("JsxOpeningFragment")},
            {SyntaxKind::JsxClosingFragment, S("JsxClosingFragment")},
            {SyntaxKind::JsxAttribute, S("JsxAttribute")},
            {SyntaxKind::JsxAttributes, S("JsxAttributes")},
            {SyntaxKind::JsxSpreadAttribute, S("JsxSpreadAttribute")},
            {SyntaxKind::JsxExpression, S("JsxExpression")},
            {SyntaxKind::CaseClause, S("CaseClause")},
            {SyntaxKind::DefaultClause, S("DefaultClause")},
            {SyntaxKind::HeritageClause, S("HeritageClause")},
            {SyntaxKind::CatchClause, S("CatchClause")},
            {SyntaxKind::PropertyAssignment, S("PropertyAssignment")},
            {SyntaxKind::ShorthandPropertyAssignment, S("ShorthandPropertyAssignment")},
            {SyntaxKind::SpreadAssignment, S("SpreadAssignment")},
            {SyntaxKind::EnumMember, S("EnumMember")},
            {SyntaxKind::UnparsedPrologue, S("UnparsedPrologue")},
            {SyntaxKind::UnparsedPrepend, S("UnparsedPrepend")},
            {SyntaxKind::UnparsedText, S("UnparsedText")},
            {SyntaxKind::UnparsedInternalText, S("UnparsedInternalText")},
            {SyntaxKind::UnparsedSyntheticReference, S("UnparsedSyntheticReference")},
            {SyntaxKind::SourceFile, S("SourceFile")},
            {SyntaxKind::Bundle, S("Bundle")},
            {SyntaxKind::UnparsedSource, S("UnparsedSource")},
            {SyntaxKind::InputFiles, S("InputFiles")},
            {SyntaxKind::JSDocTypeExpression, S("JSDocTypeExpression")},
            {SyntaxKind::JSDocNameReference, S("JSDocNameReference")},
            {SyntaxKind::JSDocAllType, S("JSDocAllType")}, 
            {SyntaxKind::JSDocUnknownType, S("JSDocUnknownType")}, 
            {SyntaxKind::JSDocNullableType, S("JSDocNullableType")},
            {SyntaxKind::JSDocNonNullableType, S("JSDocNonNullableType")},
            {SyntaxKind::JSDocOptionalType, S("JSDocOptionalType")},
            {SyntaxKind::JSDocFunctionType, S("JSDocFunctionType")},
            {SyntaxKind::JSDocVariadicType, S("JSDocVariadicType")},
            {SyntaxKind::JSDocNamepathType, S("JSDocNamepathType")}, 
            {SyntaxKind::JSDocComment, S("JSDocComment")},
            {SyntaxKind::JSDocTypeLiteral, S("JSDocTypeLiteral")},
            {SyntaxKind::JSDocSignature, S("JSDocSignature")},
            {SyntaxKind::JSDocTag, S("JSDocTag")},
            {SyntaxKind::JSDocAugmentsTag, S("JSDocAugmentsTag")},
            {SyntaxKind::JSDocImplementsTag, S("JSDocImplementsTag")},
            {SyntaxKind::JSDocAuthorTag, S("JSDocAuthorTag")},
            {SyntaxKind::JSDocDeprecatedTag, S("JSDocDeprecatedTag")},
            {SyntaxKind::JSDocClassTag, S("JSDocClassTag")},
            {SyntaxKind::JSDocPublicTag, S("JSDocPublicTag")},
            {SyntaxKind::JSDocPrivateTag, S("JSDocPrivateTag")},
            {SyntaxKind::JSDocProtectedTag, S("JSDocProtectedTag")},
            {SyntaxKind::JSDocReadonlyTag, S("JSDocReadonlyTag")},
            {SyntaxKind::JSDocCallbackTag, S("JSDocCallbackTag")},
            {SyntaxKind::JSDocEnumTag, S("JSDocEnumTag")},
            {SyntaxKind::JSDocParameterTag, S("JSDocParameterTag")},
            {SyntaxKind::JSDocReturnTag, S("JSDocReturnTag")},
            {SyntaxKind::JSDocThisTag, S("JSDocThisTag")},
            {SyntaxKind::JSDocTypeTag, S("JSDocTypeTag")},
            {SyntaxKind::JSDocTemplateTag, S("JSDocTemplateTag")},
            {SyntaxKind::JSDocTypedefTag, S("JSDocTypedefTag")},
            {SyntaxKind::JSDocSeeTag, S("JSDocSeeTag")},
            {SyntaxKind::JSDocPropertyTag, S("JSDocPropertyTag")},
            {SyntaxKind::SyntaxList, S("SyntaxList")},
            {SyntaxKind::NotEmittedStatement, S("NotEmittedStatement")},
            {SyntaxKind::PartiallyEmittedExpression, S("PartiallyEmittedExpression")},
            {SyntaxKind::CommaListExpression, S("CommaListExpression")},
            {SyntaxKind::MergeDeclarationMarker, S("MergeDeclarationMarker")},
            {SyntaxKind::EndOfDeclarationMarker, S("EndOfDeclarationMarker")},
            {SyntaxKind::SyntheticReferenceExpression, S("SyntheticReferenceExpression")}
        };

        /*
            As per ECMAScript Language Specification 3th Edition, Section 7.6: Identifiers
            IdentifierStart ::
                Can contain Unicode 3.0.0 categories:
                Uppercase letter (Lu),
                Lowercase letter (Ll),
                Titlecase letter (Lt),
                Modifier letter (Lm),
                Other letter (Lo), or
                Letter number (Nl).
            IdentifierPart :: =
                Can contain IdentifierStart + Unicode 3.0.0 categories:
                Non-spacing mark (Mn),
                Combining spacing mark (Mc),
                Decimal number (Nd), or
                Connector punctuation (Pc).

            Codepoint ranges for ES3 Identifiers are extracted from the Unicode 3.0.0 specification at:
            http://www.unicode.org/Public/3.0-Update/UnicodeData-3.0.0.txt
        */
        std::vector<number> unicodeES3IdentifierStart = {170, 170, 181, 181, 186, 186, 192, 214, 216, 246, 248, 543, 546, 563, 592, 685, 688, 696, 699, 705, 720, 721, 736, 740, 750, 750, 890, 890, 902, 902, 904, 906, 908, 908, 910, 929, 931, 974, 976, 983, 986, 1011, 1024, 1153, 1164, 1220, 1223, 1224, 1227, 1228, 1232, 1269, 1272, 1273, 1329, 1366, 1369, 1369, 1377, 1415, 1488, 1514, 1520, 1522, 1569, 1594, 1600, 1610, 1649, 1747, 1749, 1749, 1765, 1766, 1786, 1788, 1808, 1808, 1810, 1836, 1920, 1957, 2309, 2361, 2365, 2365, 2384, 2384, 2392, 2401, 2437, 2444, 2447, 2448, 2451, 2472, 2474, 2480, 2482, 2482, 2486, 2489, 2524, 2525, 2527, 2529, 2544, 2545, 2565, 2570, 2575, 2576, 2579, 2600, 2602, 2608, 2610, 2611, 2613, 2614, 2616, 2617, 2649, 2652, 2654, 2654, 2674, 2676, 2693, 2699, 2701, 2701, 2703, 2705, 2707, 2728, 2730, 2736, 2738, 2739, 2741, 2745, 2749, 2749, 2768, 2768, 2784, 2784, 2821, 2828, 2831, 2832, 2835, 2856, 2858, 2864, 2866, 2867, 2870, 2873, 2877, 2877, 2908, 2909, 2911, 2913, 2949, 2954, 2958, 2960, 2962, 2965, 2969, 2970, 2972, 2972, 2974, 2975, 2979, 2980, 2984, 2986, 2990, 2997, 2999, 3001, 3077, 3084, 3086, 3088, 3090, 3112, 3114, 3123, 3125, 3129, 3168, 3169, 3205, 3212, 3214, 3216, 3218, 3240, 3242, 3251, 3253, 3257, 3294, 3294, 3296, 3297, 3333, 3340, 3342, 3344, 3346, 3368, 3370, 3385, 3424, 3425, 3461, 3478, 3482, 3505, 3507, 3515, 3517, 3517, 3520, 3526, 3585, 3632, 3634, 3635, 3648, 3654, 3713, 3714, 3716, 3716, 3719, 3720, 3722, 3722, 3725, 3725, 3732, 3735, 3737, 3743, 3745, 3747, 3749, 3749, 3751, 3751, 3754, 3755, 3757, 3760, 3762, 3763, 3773, 3773, 3776, 3780, 3782, 3782, 3804, 3805, 3840, 3840, 3904, 3911, 3913, 3946, 3976, 3979, 4096, 4129, 4131, 4135, 4137, 4138, 4176, 4181, 4256, 4293, 4304, 4342, 4352, 4441, 4447, 4514, 4520, 4601, 4608, 4614, 4616, 4678, 4680, 4680, 4682, 4685, 4688, 4694, 4696, 4696, 4698, 4701, 4704, 4742, 4744, 4744, 4746, 4749, 4752, 4782, 4784, 4784, 4786, 4789, 4792, 4798, 4800, 4800, 4802, 4805, 4808, 4814, 4816, 4822, 4824, 4846, 4848, 4878, 4880, 4880, 4882, 4885, 4888, 4894, 4896, 4934, 4936, 4954, 5024, 5108, 5121, 5740, 5743, 5750, 5761, 5786, 5792, 5866, 6016, 6067, 6176, 6263, 6272, 6312, 7680, 7835, 7840, 7929, 7936, 7957, 7960, 7965, 7968, 8005, 8008, 8013, 8016, 8023, 8025, 8025, 8027, 8027, 8029, 8029, 8031, 8061, 8064, 8116, 8118, 8124, 8126, 8126, 8130, 8132, 8134, 8140, 8144, 8147, 8150, 8155, 8160, 8172, 8178, 8180, 8182, 8188, 8319, 8319, 8450, 8450, 8455, 8455, 8458, 8467, 8469, 8469, 8473, 8477, 8484, 8484, 8486, 8486, 8488, 8488, 8490, 8493, 8495, 8497, 8499, 8505, 8544, 8579, 12293, 12295, 12321, 12329, 12337, 12341, 12344, 12346, 12353, 12436, 12445, 12446, 12449, 12538, 12540, 12542, 12549, 12588, 12593, 12686, 12704, 12727, 13312, 19893, 19968, 40869, 40960, 42124, 44032, 55203, 63744, 64045, 64256, 64262, 64275, 64279, 64285, 64285, 64287, 64296, 64298, 64310, 64312, 64316, 64318, 64318, 64320, 64321, 64323, 64324, 64326, 64433, 64467, 64829, 64848, 64911, 64914, 64967, 65008, 65019, 65136, 65138, 65140, 65140, 65142, 65276, 65313, 65338, 65345, 65370, 65382, 65470, 65474, 65479, 65482, 65487, 65490, 65495, 65498, 65500};
        std::vector<number> unicodeES3IdentifierPart = {170, 170, 181, 181, 186, 186, 192, 214, 216, 246, 248, 543, 546, 563, 592, 685, 688, 696, 699, 705, 720, 721, 736, 740, 750, 750, 768, 846, 864, 866, 890, 890, 902, 902, 904, 906, 908, 908, 910, 929, 931, 974, 976, 983, 986, 1011, 1024, 1153, 1155, 1158, 1164, 1220, 1223, 1224, 1227, 1228, 1232, 1269, 1272, 1273, 1329, 1366, 1369, 1369, 1377, 1415, 1425, 1441, 1443, 1465, 1467, 1469, 1471, 1471, 1473, 1474, 1476, 1476, 1488, 1514, 1520, 1522, 1569, 1594, 1600, 1621, 1632, 1641, 1648, 1747, 1749, 1756, 1759, 1768, 1770, 1773, 1776, 1788, 1808, 1836, 1840, 1866, 1920, 1968, 2305, 2307, 2309, 2361, 2364, 2381, 2384, 2388, 2392, 2403, 2406, 2415, 2433, 2435, 2437, 2444, 2447, 2448, 2451, 2472, 2474, 2480, 2482, 2482, 2486, 2489, 2492, 2492, 2494, 2500, 2503, 2504, 2507, 2509, 2519, 2519, 2524, 2525, 2527, 2531, 2534, 2545, 2562, 2562, 2565, 2570, 2575, 2576, 2579, 2600, 2602, 2608, 2610, 2611, 2613, 2614, 2616, 2617, 2620, 2620, 2622, 2626, 2631, 2632, 2635, 2637, 2649, 2652, 2654, 2654, 2662, 2676, 2689, 2691, 2693, 2699, 2701, 2701, 2703, 2705, 2707, 2728, 2730, 2736, 2738, 2739, 2741, 2745, 2748, 2757, 2759, 2761, 2763, 2765, 2768, 2768, 2784, 2784, 2790, 2799, 2817, 2819, 2821, 2828, 2831, 2832, 2835, 2856, 2858, 2864, 2866, 2867, 2870, 2873, 2876, 2883, 2887, 2888, 2891, 2893, 2902, 2903, 2908, 2909, 2911, 2913, 2918, 2927, 2946, 2947, 2949, 2954, 2958, 2960, 2962, 2965, 2969, 2970, 2972, 2972, 2974, 2975, 2979, 2980, 2984, 2986, 2990, 2997, 2999, 3001, 3006, 3010, 3014, 3016, 3018, 3021, 3031, 3031, 3047, 3055, 3073, 3075, 3077, 3084, 3086, 3088, 3090, 3112, 3114, 3123, 3125, 3129, 3134, 3140, 3142, 3144, 3146, 3149, 3157, 3158, 3168, 3169, 3174, 3183, 3202, 3203, 3205, 3212, 3214, 3216, 3218, 3240, 3242, 3251, 3253, 3257, 3262, 3268, 3270, 3272, 3274, 3277, 3285, 3286, 3294, 3294, 3296, 3297, 3302, 3311, 3330, 3331, 3333, 3340, 3342, 3344, 3346, 3368, 3370, 3385, 3390, 3395, 3398, 3400, 3402, 3405, 3415, 3415, 3424, 3425, 3430, 3439, 3458, 3459, 3461, 3478, 3482, 3505, 3507, 3515, 3517, 3517, 3520, 3526, 3530, 3530, 3535, 3540, 3542, 3542, 3544, 3551, 3570, 3571, 3585, 3642, 3648, 3662, 3664, 3673, 3713, 3714, 3716, 3716, 3719, 3720, 3722, 3722, 3725, 3725, 3732, 3735, 3737, 3743, 3745, 3747, 3749, 3749, 3751, 3751, 3754, 3755, 3757, 3769, 3771, 3773, 3776, 3780, 3782, 3782, 3784, 3789, 3792, 3801, 3804, 3805, 3840, 3840, 3864, 3865, 3872, 3881, 3893, 3893, 3895, 3895, 3897, 3897, 3902, 3911, 3913, 3946, 3953, 3972, 3974, 3979, 3984, 3991, 3993, 4028, 4038, 4038, 4096, 4129, 4131, 4135, 4137, 4138, 4140, 4146, 4150, 4153, 4160, 4169, 4176, 4185, 4256, 4293, 4304, 4342, 4352, 4441, 4447, 4514, 4520, 4601, 4608, 4614, 4616, 4678, 4680, 4680, 4682, 4685, 4688, 4694, 4696, 4696, 4698, 4701, 4704, 4742, 4744, 4744, 4746, 4749, 4752, 4782, 4784, 4784, 4786, 4789, 4792, 4798, 4800, 4800, 4802, 4805, 4808, 4814, 4816, 4822, 4824, 4846, 4848, 4878, 4880, 4880, 4882, 4885, 4888, 4894, 4896, 4934, 4936, 4954, 4969, 4977, 5024, 5108, 5121, 5740, 5743, 5750, 5761, 5786, 5792, 5866, 6016, 6099, 6112, 6121, 6160, 6169, 6176, 6263, 6272, 6313, 7680, 7835, 7840, 7929, 7936, 7957, 7960, 7965, 7968, 8005, 8008, 8013, 8016, 8023, 8025, 8025, 8027, 8027, 8029, 8029, 8031, 8061, 8064, 8116, 8118, 8124, 8126, 8126, 8130, 8132, 8134, 8140, 8144, 8147, 8150, 8155, 8160, 8172, 8178, 8180, 8182, 8188, 8255, 8256, 8319, 8319, 8400, 8412, 8417, 8417, 8450, 8450, 8455, 8455, 8458, 8467, 8469, 8469, 8473, 8477, 8484, 8484, 8486, 8486, 8488, 8488, 8490, 8493, 8495, 8497, 8499, 8505, 8544, 8579, 12293, 12295, 12321, 12335, 12337, 12341, 12344, 12346, 12353, 12436, 12441, 12442, 12445, 12446, 12449, 12542, 12549, 12588, 12593, 12686, 12704, 12727, 13312, 19893, 19968, 40869, 40960, 42124, 44032, 55203, 63744, 64045, 64256, 64262, 64275, 64279, 64285, 64296, 64298, 64310, 64312, 64316, 64318, 64318, 64320, 64321, 64323, 64324, 64326, 64433, 64467, 64829, 64848, 64911, 64914, 64967, 65008, 65019, 65056, 65059, 65075, 65076, 65101, 65103, 65136, 65138, 65140, 65140, 65142, 65276, 65296, 65305, 65313, 65338, 65343, 65343, 65345, 65370, 65381, 65470, 65474, 65479, 65482, 65487, 65490, 65495, 65498, 65500};

        /*
            As per ECMAScript Language Specification 5th Edition, Section 7.6: ISyntaxToken Names and Identifiers
            IdentifierStart ::
                Can contain Unicode 6.2 categories:
                Uppercase letter (Lu),
                Lowercase letter (Ll),
                Titlecase letter (Lt),
                Modifier letter (Lm),
                Other letter (Lo), or
                Letter number (Nl).
            IdentifierPart ::
                Can contain IdentifierStart + Unicode 6.2 categories:
                Non-spacing mark (Mn),
                Combining spacing mark (Mc),
                Decimal number (Nd),
                Connector punctuation (Pc),
                <ZWNJ>, or
                <ZWJ>.

            Codepoint ranges for ES5 Identifiers are extracted from the Unicode 6.2 specification at:
            http://www.unicode.org/Public/6.2.0/ucd/UnicodeData.txt
        */
        std::vector<number> unicodeES5IdentifierStart = {170, 170, 181, 181, 186, 186, 192, 214, 216, 246, 248, 705, 710, 721, 736, 740, 748, 748, 750, 750, 880, 884, 886, 887, 890, 893, 902, 902, 904, 906, 908, 908, 910, 929, 931, 1013, 1015, 1153, 1162, 1319, 1329, 1366, 1369, 1369, 1377, 1415, 1488, 1514, 1520, 1522, 1568, 1610, 1646, 1647, 1649, 1747, 1749, 1749, 1765, 1766, 1774, 1775, 1786, 1788, 1791, 1791, 1808, 1808, 1810, 1839, 1869, 1957, 1969, 1969, 1994, 2026, 2036, 2037, 2042, 2042, 2048, 2069, 2074, 2074, 2084, 2084, 2088, 2088, 2112, 2136, 2208, 2208, 2210, 2220, 2308, 2361, 2365, 2365, 2384, 2384, 2392, 2401, 2417, 2423, 2425, 2431, 2437, 2444, 2447, 2448, 2451, 2472, 2474, 2480, 2482, 2482, 2486, 2489, 2493, 2493, 2510, 2510, 2524, 2525, 2527, 2529, 2544, 2545, 2565, 2570, 2575, 2576, 2579, 2600, 2602, 2608, 2610, 2611, 2613, 2614, 2616, 2617, 2649, 2652, 2654, 2654, 2674, 2676, 2693, 2701, 2703, 2705, 2707, 2728, 2730, 2736, 2738, 2739, 2741, 2745, 2749, 2749, 2768, 2768, 2784, 2785, 2821, 2828, 2831, 2832, 2835, 2856, 2858, 2864, 2866, 2867, 2869, 2873, 2877, 2877, 2908, 2909, 2911, 2913, 2929, 2929, 2947, 2947, 2949, 2954, 2958, 2960, 2962, 2965, 2969, 2970, 2972, 2972, 2974, 2975, 2979, 2980, 2984, 2986, 2990, 3001, 3024, 3024, 3077, 3084, 3086, 3088, 3090, 3112, 3114, 3123, 3125, 3129, 3133, 3133, 3160, 3161, 3168, 3169, 3205, 3212, 3214, 3216, 3218, 3240, 3242, 3251, 3253, 3257, 3261, 3261, 3294, 3294, 3296, 3297, 3313, 3314, 3333, 3340, 3342, 3344, 3346, 3386, 3389, 3389, 3406, 3406, 3424, 3425, 3450, 3455, 3461, 3478, 3482, 3505, 3507, 3515, 3517, 3517, 3520, 3526, 3585, 3632, 3634, 3635, 3648, 3654, 3713, 3714, 3716, 3716, 3719, 3720, 3722, 3722, 3725, 3725, 3732, 3735, 3737, 3743, 3745, 3747, 3749, 3749, 3751, 3751, 3754, 3755, 3757, 3760, 3762, 3763, 3773, 3773, 3776, 3780, 3782, 3782, 3804, 3807, 3840, 3840, 3904, 3911, 3913, 3948, 3976, 3980, 4096, 4138, 4159, 4159, 4176, 4181, 4186, 4189, 4193, 4193, 4197, 4198, 4206, 4208, 4213, 4225, 4238, 4238, 4256, 4293, 4295, 4295, 4301, 4301, 4304, 4346, 4348, 4680, 4682, 4685, 4688, 4694, 4696, 4696, 4698, 4701, 4704, 4744, 4746, 4749, 4752, 4784, 4786, 4789, 4792, 4798, 4800, 4800, 4802, 4805, 4808, 4822, 4824, 4880, 4882, 4885, 4888, 4954, 4992, 5007, 5024, 5108, 5121, 5740, 5743, 5759, 5761, 5786, 5792, 5866, 5870, 5872, 5888, 5900, 5902, 5905, 5920, 5937, 5952, 5969, 5984, 5996, 5998, 6000, 6016, 6067, 6103, 6103, 6108, 6108, 6176, 6263, 6272, 6312, 6314, 6314, 6320, 6389, 6400, 6428, 6480, 6509, 6512, 6516, 6528, 6571, 6593, 6599, 6656, 6678, 6688, 6740, 6823, 6823, 6917, 6963, 6981, 6987, 7043, 7072, 7086, 7087, 7098, 7141, 7168, 7203, 7245, 7247, 7258, 7293, 7401, 7404, 7406, 7409, 7413, 7414, 7424, 7615, 7680, 7957, 7960, 7965, 7968, 8005, 8008, 8013, 8016, 8023, 8025, 8025, 8027, 8027, 8029, 8029, 8031, 8061, 8064, 8116, 8118, 8124, 8126, 8126, 8130, 8132, 8134, 8140, 8144, 8147, 8150, 8155, 8160, 8172, 8178, 8180, 8182, 8188, 8305, 8305, 8319, 8319, 8336, 8348, 8450, 8450, 8455, 8455, 8458, 8467, 8469, 8469, 8473, 8477, 8484, 8484, 8486, 8486, 8488, 8488, 8490, 8493, 8495, 8505, 8508, 8511, 8517, 8521, 8526, 8526, 8544, 8584, 11264, 11310, 11312, 11358, 11360, 11492, 11499, 11502, 11506, 11507, 11520, 11557, 11559, 11559, 11565, 11565, 11568, 11623, 11631, 11631, 11648, 11670, 11680, 11686, 11688, 11694, 11696, 11702, 11704, 11710, 11712, 11718, 11720, 11726, 11728, 11734, 11736, 11742, 11823, 11823, 12293, 12295, 12321, 12329, 12337, 12341, 12344, 12348, 12353, 12438, 12445, 12447, 12449, 12538, 12540, 12543, 12549, 12589, 12593, 12686, 12704, 12730, 12784, 12799, 13312, 19893, 19968, 40908, 40960, 42124, 42192, 42237, 42240, 42508, 42512, 42527, 42538, 42539, 42560, 42606, 42623, 42647, 42656, 42735, 42775, 42783, 42786, 42888, 42891, 42894, 42896, 42899, 42912, 42922, 43000, 43009, 43011, 43013, 43015, 43018, 43020, 43042, 43072, 43123, 43138, 43187, 43250, 43255, 43259, 43259, 43274, 43301, 43312, 43334, 43360, 43388, 43396, 43442, 43471, 43471, 43520, 43560, 43584, 43586, 43588, 43595, 43616, 43638, 43642, 43642, 43648, 43695, 43697, 43697, 43701, 43702, 43705, 43709, 43712, 43712, 43714, 43714, 43739, 43741, 43744, 43754, 43762, 43764, 43777, 43782, 43785, 43790, 43793, 43798, 43808, 43814, 43816, 43822, 43968, 44002, 44032, 55203, 55216, 55238, 55243, 55291, 63744, 64109, 64112, 64217, 64256, 64262, 64275, 64279, 64285, 64285, 64287, 64296, 64298, 64310, 64312, 64316, 64318, 64318, 64320, 64321, 64323, 64324, 64326, 64433, 64467, 64829, 64848, 64911, 64914, 64967, 65008, 65019, 65136, 65140, 65142, 65276, 65313, 65338, 65345, 65370, 65382, 65470, 65474, 65479, 65482, 65487, 65490, 65495, 65498, 65500};
        std::vector<number> unicodeES5IdentifierPart = {170, 170, 181, 181, 186, 186, 192, 214, 216, 246, 248, 705, 710, 721, 736, 740, 748, 748, 750, 750, 768, 884, 886, 887, 890, 893, 902, 902, 904, 906, 908, 908, 910, 929, 931, 1013, 1015, 1153, 1155, 1159, 1162, 1319, 1329, 1366, 1369, 1369, 1377, 1415, 1425, 1469, 1471, 1471, 1473, 1474, 1476, 1477, 1479, 1479, 1488, 1514, 1520, 1522, 1552, 1562, 1568, 1641, 1646, 1747, 1749, 1756, 1759, 1768, 1770, 1788, 1791, 1791, 1808, 1866, 1869, 1969, 1984, 2037, 2042, 2042, 2048, 2093, 2112, 2139, 2208, 2208, 2210, 2220, 2276, 2302, 2304, 2403, 2406, 2415, 2417, 2423, 2425, 2431, 2433, 2435, 2437, 2444, 2447, 2448, 2451, 2472, 2474, 2480, 2482, 2482, 2486, 2489, 2492, 2500, 2503, 2504, 2507, 2510, 2519, 2519, 2524, 2525, 2527, 2531, 2534, 2545, 2561, 2563, 2565, 2570, 2575, 2576, 2579, 2600, 2602, 2608, 2610, 2611, 2613, 2614, 2616, 2617, 2620, 2620, 2622, 2626, 2631, 2632, 2635, 2637, 2641, 2641, 2649, 2652, 2654, 2654, 2662, 2677, 2689, 2691, 2693, 2701, 2703, 2705, 2707, 2728, 2730, 2736, 2738, 2739, 2741, 2745, 2748, 2757, 2759, 2761, 2763, 2765, 2768, 2768, 2784, 2787, 2790, 2799, 2817, 2819, 2821, 2828, 2831, 2832, 2835, 2856, 2858, 2864, 2866, 2867, 2869, 2873, 2876, 2884, 2887, 2888, 2891, 2893, 2902, 2903, 2908, 2909, 2911, 2915, 2918, 2927, 2929, 2929, 2946, 2947, 2949, 2954, 2958, 2960, 2962, 2965, 2969, 2970, 2972, 2972, 2974, 2975, 2979, 2980, 2984, 2986, 2990, 3001, 3006, 3010, 3014, 3016, 3018, 3021, 3024, 3024, 3031, 3031, 3046, 3055, 3073, 3075, 3077, 3084, 3086, 3088, 3090, 3112, 3114, 3123, 3125, 3129, 3133, 3140, 3142, 3144, 3146, 3149, 3157, 3158, 3160, 3161, 3168, 3171, 3174, 3183, 3202, 3203, 3205, 3212, 3214, 3216, 3218, 3240, 3242, 3251, 3253, 3257, 3260, 3268, 3270, 3272, 3274, 3277, 3285, 3286, 3294, 3294, 3296, 3299, 3302, 3311, 3313, 3314, 3330, 3331, 3333, 3340, 3342, 3344, 3346, 3386, 3389, 3396, 3398, 3400, 3402, 3406, 3415, 3415, 3424, 3427, 3430, 3439, 3450, 3455, 3458, 3459, 3461, 3478, 3482, 3505, 3507, 3515, 3517, 3517, 3520, 3526, 3530, 3530, 3535, 3540, 3542, 3542, 3544, 3551, 3570, 3571, 3585, 3642, 3648, 3662, 3664, 3673, 3713, 3714, 3716, 3716, 3719, 3720, 3722, 3722, 3725, 3725, 3732, 3735, 3737, 3743, 3745, 3747, 3749, 3749, 3751, 3751, 3754, 3755, 3757, 3769, 3771, 3773, 3776, 3780, 3782, 3782, 3784, 3789, 3792, 3801, 3804, 3807, 3840, 3840, 3864, 3865, 3872, 3881, 3893, 3893, 3895, 3895, 3897, 3897, 3902, 3911, 3913, 3948, 3953, 3972, 3974, 3991, 3993, 4028, 4038, 4038, 4096, 4169, 4176, 4253, 4256, 4293, 4295, 4295, 4301, 4301, 4304, 4346, 4348, 4680, 4682, 4685, 4688, 4694, 4696, 4696, 4698, 4701, 4704, 4744, 4746, 4749, 4752, 4784, 4786, 4789, 4792, 4798, 4800, 4800, 4802, 4805, 4808, 4822, 4824, 4880, 4882, 4885, 4888, 4954, 4957, 4959, 4992, 5007, 5024, 5108, 5121, 5740, 5743, 5759, 5761, 5786, 5792, 5866, 5870, 5872, 5888, 5900, 5902, 5908, 5920, 5940, 5952, 5971, 5984, 5996, 5998, 6000, 6002, 6003, 6016, 6099, 6103, 6103, 6108, 6109, 6112, 6121, 6155, 6157, 6160, 6169, 6176, 6263, 6272, 6314, 6320, 6389, 6400, 6428, 6432, 6443, 6448, 6459, 6470, 6509, 6512, 6516, 6528, 6571, 6576, 6601, 6608, 6617, 6656, 6683, 6688, 6750, 6752, 6780, 6783, 6793, 6800, 6809, 6823, 6823, 6912, 6987, 6992, 7001, 7019, 7027, 7040, 7155, 7168, 7223, 7232, 7241, 7245, 7293, 7376, 7378, 7380, 7414, 7424, 7654, 7676, 7957, 7960, 7965, 7968, 8005, 8008, 8013, 8016, 8023, 8025, 8025, 8027, 8027, 8029, 8029, 8031, 8061, 8064, 8116, 8118, 8124, 8126, 8126, 8130, 8132, 8134, 8140, 8144, 8147, 8150, 8155, 8160, 8172, 8178, 8180, 8182, 8188, 8204, 8205, 8255, 8256, 8276, 8276, 8305, 8305, 8319, 8319, 8336, 8348, 8400, 8412, 8417, 8417, 8421, 8432, 8450, 8450, 8455, 8455, 8458, 8467, 8469, 8469, 8473, 8477, 8484, 8484, 8486, 8486, 8488, 8488, 8490, 8493, 8495, 8505, 8508, 8511, 8517, 8521, 8526, 8526, 8544, 8584, 11264, 11310, 11312, 11358, 11360, 11492, 11499, 11507, 11520, 11557, 11559, 11559, 11565, 11565, 11568, 11623, 11631, 11631, 11647, 11670, 11680, 11686, 11688, 11694, 11696, 11702, 11704, 11710, 11712, 11718, 11720, 11726, 11728, 11734, 11736, 11742, 11744, 11775, 11823, 11823, 12293, 12295, 12321, 12335, 12337, 12341, 12344, 12348, 12353, 12438, 12441, 12442, 12445, 12447, 12449, 12538, 12540, 12543, 12549, 12589, 12593, 12686, 12704, 12730, 12784, 12799, 13312, 19893, 19968, 40908, 40960, 42124, 42192, 42237, 42240, 42508, 42512, 42539, 42560, 42607, 42612, 42621, 42623, 42647, 42655, 42737, 42775, 42783, 42786, 42888, 42891, 42894, 42896, 42899, 42912, 42922, 43000, 43047, 43072, 43123, 43136, 43204, 43216, 43225, 43232, 43255, 43259, 43259, 43264, 43309, 43312, 43347, 43360, 43388, 43392, 43456, 43471, 43481, 43520, 43574, 43584, 43597, 43600, 43609, 43616, 43638, 43642, 43643, 43648, 43714, 43739, 43741, 43744, 43759, 43762, 43766, 43777, 43782, 43785, 43790, 43793, 43798, 43808, 43814, 43816, 43822, 43968, 44010, 44012, 44013, 44016, 44025, 44032, 55203, 55216, 55238, 55243, 55291, 63744, 64109, 64112, 64217, 64256, 64262, 64275, 64279, 64285, 64296, 64298, 64310, 64312, 64316, 64318, 64318, 64320, 64321, 64323, 64324, 64326, 64433, 64467, 64829, 64848, 64911, 64914, 64967, 65008, 65019, 65024, 65039, 65056, 65062, 65075, 65076, 65101, 65103, 65136, 65140, 65142, 65276, 65296, 65305, 65313, 65338, 65343, 65343, 65345, 65370, 65382, 65470, 65474, 65479, 65482, 65487, 65490, 65495, 65498, 65500};

        /**
         * Generated by scripts/regenerate-unicode-identifier-parts.js on node v12.4.0 with unicode 12.1
         * based on http://www.unicode.org/reports/tr31/ and https://www.ecma-international.org/ecma-262/6.0/#sec-names-and-keywords
         * unicodeESNextIdentifierStart corresponds to the ID_Start and Other_ID_Start property, and
         * unicodeESNextIdentifierPart corresponds to ID_Continue, Other_ID_Continue, plus ID_Start and Other_ID_Start
         */
        std::vector<number> unicodeESNextIdentifierStart = {65, 90, 97, 122, 170, 170, 181, 181, 186, 186, 192, 214, 216, 246, 248, 705, 710, 721, 736, 740, 748, 748, 750, 750, 880, 884, 886, 887, 890, 893, 895, 895, 902, 902, 904, 906, 908, 908, 910, 929, 931, 1013, 1015, 1153, 1162, 1327, 1329, 1366, 1369, 1369, 1376, 1416, 1488, 1514, 1519, 1522, 1568, 1610, 1646, 1647, 1649, 1747, 1749, 1749, 1765, 1766, 1774, 1775, 1786, 1788, 1791, 1791, 1808, 1808, 1810, 1839, 1869, 1957, 1969, 1969, 1994, 2026, 2036, 2037, 2042, 2042, 2048, 2069, 2074, 2074, 2084, 2084, 2088, 2088, 2112, 2136, 2144, 2154, 2208, 2228, 2230, 2237, 2308, 2361, 2365, 2365, 2384, 2384, 2392, 2401, 2417, 2432, 2437, 2444, 2447, 2448, 2451, 2472, 2474, 2480, 2482, 2482, 2486, 2489, 2493, 2493, 2510, 2510, 2524, 2525, 2527, 2529, 2544, 2545, 2556, 2556, 2565, 2570, 2575, 2576, 2579, 2600, 2602, 2608, 2610, 2611, 2613, 2614, 2616, 2617, 2649, 2652, 2654, 2654, 2674, 2676, 2693, 2701, 2703, 2705, 2707, 2728, 2730, 2736, 2738, 2739, 2741, 2745, 2749, 2749, 2768, 2768, 2784, 2785, 2809, 2809, 2821, 2828, 2831, 2832, 2835, 2856, 2858, 2864, 2866, 2867, 2869, 2873, 2877, 2877, 2908, 2909, 2911, 2913, 2929, 2929, 2947, 2947, 2949, 2954, 2958, 2960, 2962, 2965, 2969, 2970, 2972, 2972, 2974, 2975, 2979, 2980, 2984, 2986, 2990, 3001, 3024, 3024, 3077, 3084, 3086, 3088, 3090, 3112, 3114, 3129, 3133, 3133, 3160, 3162, 3168, 3169, 3200, 3200, 3205, 3212, 3214, 3216, 3218, 3240, 3242, 3251, 3253, 3257, 3261, 3261, 3294, 3294, 3296, 3297, 3313, 3314, 3333, 3340, 3342, 3344, 3346, 3386, 3389, 3389, 3406, 3406, 3412, 3414, 3423, 3425, 3450, 3455, 3461, 3478, 3482, 3505, 3507, 3515, 3517, 3517, 3520, 3526, 3585, 3632, 3634, 3635, 3648, 3654, 3713, 3714, 3716, 3716, 3718, 3722, 3724, 3747, 3749, 3749, 3751, 3760, 3762, 3763, 3773, 3773, 3776, 3780, 3782, 3782, 3804, 3807, 3840, 3840, 3904, 3911, 3913, 3948, 3976, 3980, 4096, 4138, 4159, 4159, 4176, 4181, 4186, 4189, 4193, 4193, 4197, 4198, 4206, 4208, 4213, 4225, 4238, 4238, 4256, 4293, 4295, 4295, 4301, 4301, 4304, 4346, 4348, 4680, 4682, 4685, 4688, 4694, 4696, 4696, 4698, 4701, 4704, 4744, 4746, 4749, 4752, 4784, 4786, 4789, 4792, 4798, 4800, 4800, 4802, 4805, 4808, 4822, 4824, 4880, 4882, 4885, 4888, 4954, 4992, 5007, 5024, 5109, 5112, 5117, 5121, 5740, 5743, 5759, 5761, 5786, 5792, 5866, 5870, 5880, 5888, 5900, 5902, 5905, 5920, 5937, 5952, 5969, 5984, 5996, 5998, 6000, 6016, 6067, 6103, 6103, 6108, 6108, 6176, 6264, 6272, 6312, 6314, 6314, 6320, 6389, 6400, 6430, 6480, 6509, 6512, 6516, 6528, 6571, 6576, 6601, 6656, 6678, 6688, 6740, 6823, 6823, 6917, 6963, 6981, 6987, 7043, 7072, 7086, 7087, 7098, 7141, 7168, 7203, 7245, 7247, 7258, 7293, 7296, 7304, 7312, 7354, 7357, 7359, 7401, 7404, 7406, 7411, 7413, 7414, 7418, 7418, 7424, 7615, 7680, 7957, 7960, 7965, 7968, 8005, 8008, 8013, 8016, 8023, 8025, 8025, 8027, 8027, 8029, 8029, 8031, 8061, 8064, 8116, 8118, 8124, 8126, 8126, 8130, 8132, 8134, 8140, 8144, 8147, 8150, 8155, 8160, 8172, 8178, 8180, 8182, 8188, 8305, 8305, 8319, 8319, 8336, 8348, 8450, 8450, 8455, 8455, 8458, 8467, 8469, 8469, 8472, 8477, 8484, 8484, 8486, 8486, 8488, 8488, 8490, 8505, 8508, 8511, 8517, 8521, 8526, 8526, 8544, 8584, 11264, 11310, 11312, 11358, 11360, 11492, 11499, 11502, 11506, 11507, 11520, 11557, 11559, 11559, 11565, 11565, 11568, 11623, 11631, 11631, 11648, 11670, 11680, 11686, 11688, 11694, 11696, 11702, 11704, 11710, 11712, 11718, 11720, 11726, 11728, 11734, 11736, 11742, 12293, 12295, 12321, 12329, 12337, 12341, 12344, 12348, 12353, 12438, 12443, 12447, 12449, 12538, 12540, 12543, 12549, 12591, 12593, 12686, 12704, 12730, 12784, 12799, 13312, 19893, 19968, 40943, 40960, 42124, 42192, 42237, 42240, 42508, 42512, 42527, 42538, 42539, 42560, 42606, 42623, 42653, 42656, 42735, 42775, 42783, 42786, 42888, 42891, 42943, 42946, 42950, 42999, 43009, 43011, 43013, 43015, 43018, 43020, 43042, 43072, 43123, 43138, 43187, 43250, 43255, 43259, 43259, 43261, 43262, 43274, 43301, 43312, 43334, 43360, 43388, 43396, 43442, 43471, 43471, 43488, 43492, 43494, 43503, 43514, 43518, 43520, 43560, 43584, 43586, 43588, 43595, 43616, 43638, 43642, 43642, 43646, 43695, 43697, 43697, 43701, 43702, 43705, 43709, 43712, 43712, 43714, 43714, 43739, 43741, 43744, 43754, 43762, 43764, 43777, 43782, 43785, 43790, 43793, 43798, 43808, 43814, 43816, 43822, 43824, 43866, 43868, 43879, 43888, 44002, 44032, 55203, 55216, 55238, 55243, 55291, 63744, 64109, 64112, 64217, 64256, 64262, 64275, 64279, 64285, 64285, 64287, 64296, 64298, 64310, 64312, 64316, 64318, 64318, 64320, 64321, 64323, 64324, 64326, 64433, 64467, 64829, 64848, 64911, 64914, 64967, 65008, 65019, 65136, 65140, 65142, 65276, 65313, 65338, 65345, 65370, 65382, 65470, 65474, 65479, 65482, 65487, 65490, 65495, 65498, 65500, 65536, 65547, 65549, 65574, 65576, 65594, 65596, 65597, 65599, 65613, 65616, 65629, 65664, 65786, 65856, 65908, 66176, 66204, 66208, 66256, 66304, 66335, 66349, 66378, 66384, 66421, 66432, 66461, 66464, 66499, 66504, 66511, 66513, 66517, 66560, 66717, 66736, 66771, 66776, 66811, 66816, 66855, 66864, 66915, 67072, 67382, 67392, 67413, 67424, 67431, 67584, 67589, 67592, 67592, 67594, 67637, 67639, 67640, 67644, 67644, 67647, 67669, 67680, 67702, 67712, 67742, 67808, 67826, 67828, 67829, 67840, 67861, 67872, 67897, 67968, 68023, 68030, 68031, 68096, 68096, 68112, 68115, 68117, 68119, 68121, 68149, 68192, 68220, 68224, 68252, 68288, 68295, 68297, 68324, 68352, 68405, 68416, 68437, 68448, 68466, 68480, 68497, 68608, 68680, 68736, 68786, 68800, 68850, 68864, 68899, 69376, 69404, 69415, 69415, 69424, 69445, 69600, 69622, 69635, 69687, 69763, 69807, 69840, 69864, 69891, 69926, 69956, 69956, 69968, 70002, 70006, 70006, 70019, 70066, 70081, 70084, 70106, 70106, 70108, 70108, 70144, 70161, 70163, 70187, 70272, 70278, 70280, 70280, 70282, 70285, 70287, 70301, 70303, 70312, 70320, 70366, 70405, 70412, 70415, 70416, 70419, 70440, 70442, 70448, 70450, 70451, 70453, 70457, 70461, 70461, 70480, 70480, 70493, 70497, 70656, 70708, 70727, 70730, 70751, 70751, 70784, 70831, 70852, 70853, 70855, 70855, 71040, 71086, 71128, 71131, 71168, 71215, 71236, 71236, 71296, 71338, 71352, 71352, 71424, 71450, 71680, 71723, 71840, 71903, 71935, 71935, 72096, 72103, 72106, 72144, 72161, 72161, 72163, 72163, 72192, 72192, 72203, 72242, 72250, 72250, 72272, 72272, 72284, 72329, 72349, 72349, 72384, 72440, 72704, 72712, 72714, 72750, 72768, 72768, 72818, 72847, 72960, 72966, 72968, 72969, 72971, 73008, 73030, 73030, 73056, 73061, 73063, 73064, 73066, 73097, 73112, 73112, 73440, 73458, 73728, 74649, 74752, 74862, 74880, 75075, 77824, 78894, 82944, 83526, 92160, 92728, 92736, 92766, 92880, 92909, 92928, 92975, 92992, 92995, 93027, 93047, 93053, 93071, 93760, 93823, 93952, 94026, 94032, 94032, 94099, 94111, 94176, 94177, 94179, 94179, 94208, 100343, 100352, 101106, 110592, 110878, 110928, 110930, 110948, 110951, 110960, 111355, 113664, 113770, 113776, 113788, 113792, 113800, 113808, 113817, 119808, 119892, 119894, 119964, 119966, 119967, 119970, 119970, 119973, 119974, 119977, 119980, 119982, 119993, 119995, 119995, 119997, 120003, 120005, 120069, 120071, 120074, 120077, 120084, 120086, 120092, 120094, 120121, 120123, 120126, 120128, 120132, 120134, 120134, 120138, 120144, 120146, 120485, 120488, 120512, 120514, 120538, 120540, 120570, 120572, 120596, 120598, 120628, 120630, 120654, 120656, 120686, 120688, 120712, 120714, 120744, 120746, 120770, 120772, 120779, 123136, 123180, 123191, 123197, 123214, 123214, 123584, 123627, 124928, 125124, 125184, 125251, 125259, 125259, 126464, 126467, 126469, 126495, 126497, 126498, 126500, 126500, 126503, 126503, 126505, 126514, 126516, 126519, 126521, 126521, 126523, 126523, 126530, 126530, 126535, 126535, 126537, 126537, 126539, 126539, 126541, 126543, 126545, 126546, 126548, 126548, 126551, 126551, 126553, 126553, 126555, 126555, 126557, 126557, 126559, 126559, 126561, 126562, 126564, 126564, 126567, 126570, 126572, 126578, 126580, 126583, 126585, 126588, 126590, 126590, 126592, 126601, 126603, 126619, 126625, 126627, 126629, 126633, 126635, 126651, 131072, 173782, 173824, 177972, 177984, 178205, 178208, 183969, 183984, 191456, 194560, 195101};
        std::vector<number> unicodeESNextIdentifierPart = {48, 57, 65, 90, 95, 95, 97, 122, 170, 170, 181, 181, 183, 183, 186, 186, 192, 214, 216, 246, 248, 705, 710, 721, 736, 740, 748, 748, 750, 750, 768, 884, 886, 887, 890, 893, 895, 895, 902, 906, 908, 908, 910, 929, 931, 1013, 1015, 1153, 1155, 1159, 1162, 1327, 1329, 1366, 1369, 1369, 1376, 1416, 1425, 1469, 1471, 1471, 1473, 1474, 1476, 1477, 1479, 1479, 1488, 1514, 1519, 1522, 1552, 1562, 1568, 1641, 1646, 1747, 1749, 1756, 1759, 1768, 1770, 1788, 1791, 1791, 1808, 1866, 1869, 1969, 1984, 2037, 2042, 2042, 2045, 2045, 2048, 2093, 2112, 2139, 2144, 2154, 2208, 2228, 2230, 2237, 2259, 2273, 2275, 2403, 2406, 2415, 2417, 2435, 2437, 2444, 2447, 2448, 2451, 2472, 2474, 2480, 2482, 2482, 2486, 2489, 2492, 2500, 2503, 2504, 2507, 2510, 2519, 2519, 2524, 2525, 2527, 2531, 2534, 2545, 2556, 2556, 2558, 2558, 2561, 2563, 2565, 2570, 2575, 2576, 2579, 2600, 2602, 2608, 2610, 2611, 2613, 2614, 2616, 2617, 2620, 2620, 2622, 2626, 2631, 2632, 2635, 2637, 2641, 2641, 2649, 2652, 2654, 2654, 2662, 2677, 2689, 2691, 2693, 2701, 2703, 2705, 2707, 2728, 2730, 2736, 2738, 2739, 2741, 2745, 2748, 2757, 2759, 2761, 2763, 2765, 2768, 2768, 2784, 2787, 2790, 2799, 2809, 2815, 2817, 2819, 2821, 2828, 2831, 2832, 2835, 2856, 2858, 2864, 2866, 2867, 2869, 2873, 2876, 2884, 2887, 2888, 2891, 2893, 2902, 2903, 2908, 2909, 2911, 2915, 2918, 2927, 2929, 2929, 2946, 2947, 2949, 2954, 2958, 2960, 2962, 2965, 2969, 2970, 2972, 2972, 2974, 2975, 2979, 2980, 2984, 2986, 2990, 3001, 3006, 3010, 3014, 3016, 3018, 3021, 3024, 3024, 3031, 3031, 3046, 3055, 3072, 3084, 3086, 3088, 3090, 3112, 3114, 3129, 3133, 3140, 3142, 3144, 3146, 3149, 3157, 3158, 3160, 3162, 3168, 3171, 3174, 3183, 3200, 3203, 3205, 3212, 3214, 3216, 3218, 3240, 3242, 3251, 3253, 3257, 3260, 3268, 3270, 3272, 3274, 3277, 3285, 3286, 3294, 3294, 3296, 3299, 3302, 3311, 3313, 3314, 3328, 3331, 3333, 3340, 3342, 3344, 3346, 3396, 3398, 3400, 3402, 3406, 3412, 3415, 3423, 3427, 3430, 3439, 3450, 3455, 3458, 3459, 3461, 3478, 3482, 3505, 3507, 3515, 3517, 3517, 3520, 3526, 3530, 3530, 3535, 3540, 3542, 3542, 3544, 3551, 3558, 3567, 3570, 3571, 3585, 3642, 3648, 3662, 3664, 3673, 3713, 3714, 3716, 3716, 3718, 3722, 3724, 3747, 3749, 3749, 3751, 3773, 3776, 3780, 3782, 3782, 3784, 3789, 3792, 3801, 3804, 3807, 3840, 3840, 3864, 3865, 3872, 3881, 3893, 3893, 3895, 3895, 3897, 3897, 3902, 3911, 3913, 3948, 3953, 3972, 3974, 3991, 3993, 4028, 4038, 4038, 4096, 4169, 4176, 4253, 4256, 4293, 4295, 4295, 4301, 4301, 4304, 4346, 4348, 4680, 4682, 4685, 4688, 4694, 4696, 4696, 4698, 4701, 4704, 4744, 4746, 4749, 4752, 4784, 4786, 4789, 4792, 4798, 4800, 4800, 4802, 4805, 4808, 4822, 4824, 4880, 4882, 4885, 4888, 4954, 4957, 4959, 4969, 4977, 4992, 5007, 5024, 5109, 5112, 5117, 5121, 5740, 5743, 5759, 5761, 5786, 5792, 5866, 5870, 5880, 5888, 5900, 5902, 5908, 5920, 5940, 5952, 5971, 5984, 5996, 5998, 6000, 6002, 6003, 6016, 6099, 6103, 6103, 6108, 6109, 6112, 6121, 6155, 6157, 6160, 6169, 6176, 6264, 6272, 6314, 6320, 6389, 6400, 6430, 6432, 6443, 6448, 6459, 6470, 6509, 6512, 6516, 6528, 6571, 6576, 6601, 6608, 6618, 6656, 6683, 6688, 6750, 6752, 6780, 6783, 6793, 6800, 6809, 6823, 6823, 6832, 6845, 6912, 6987, 6992, 7001, 7019, 7027, 7040, 7155, 7168, 7223, 7232, 7241, 7245, 7293, 7296, 7304, 7312, 7354, 7357, 7359, 7376, 7378, 7380, 7418, 7424, 7673, 7675, 7957, 7960, 7965, 7968, 8005, 8008, 8013, 8016, 8023, 8025, 8025, 8027, 8027, 8029, 8029, 8031, 8061, 8064, 8116, 8118, 8124, 8126, 8126, 8130, 8132, 8134, 8140, 8144, 8147, 8150, 8155, 8160, 8172, 8178, 8180, 8182, 8188, 8255, 8256, 8276, 8276, 8305, 8305, 8319, 8319, 8336, 8348, 8400, 8412, 8417, 8417, 8421, 8432, 8450, 8450, 8455, 8455, 8458, 8467, 8469, 8469, 8472, 8477, 8484, 8484, 8486, 8486, 8488, 8488, 8490, 8505, 8508, 8511, 8517, 8521, 8526, 8526, 8544, 8584, 11264, 11310, 11312, 11358, 11360, 11492, 11499, 11507, 11520, 11557, 11559, 11559, 11565, 11565, 11568, 11623, 11631, 11631, 11647, 11670, 11680, 11686, 11688, 11694, 11696, 11702, 11704, 11710, 11712, 11718, 11720, 11726, 11728, 11734, 11736, 11742, 11744, 11775, 12293, 12295, 12321, 12335, 12337, 12341, 12344, 12348, 12353, 12438, 12441, 12447, 12449, 12538, 12540, 12543, 12549, 12591, 12593, 12686, 12704, 12730, 12784, 12799, 13312, 19893, 19968, 40943, 40960, 42124, 42192, 42237, 42240, 42508, 42512, 42539, 42560, 42607, 42612, 42621, 42623, 42737, 42775, 42783, 42786, 42888, 42891, 42943, 42946, 42950, 42999, 43047, 43072, 43123, 43136, 43205, 43216, 43225, 43232, 43255, 43259, 43259, 43261, 43309, 43312, 43347, 43360, 43388, 43392, 43456, 43471, 43481, 43488, 43518, 43520, 43574, 43584, 43597, 43600, 43609, 43616, 43638, 43642, 43714, 43739, 43741, 43744, 43759, 43762, 43766, 43777, 43782, 43785, 43790, 43793, 43798, 43808, 43814, 43816, 43822, 43824, 43866, 43868, 43879, 43888, 44010, 44012, 44013, 44016, 44025, 44032, 55203, 55216, 55238, 55243, 55291, 63744, 64109, 64112, 64217, 64256, 64262, 64275, 64279, 64285, 64296, 64298, 64310, 64312, 64316, 64318, 64318, 64320, 64321, 64323, 64324, 64326, 64433, 64467, 64829, 64848, 64911, 64914, 64967, 65008, 65019, 65024, 65039, 65056, 65071, 65075, 65076, 65101, 65103, 65136, 65140, 65142, 65276, 65296, 65305, 65313, 65338, 65343, 65343, 65345, 65370, 65382, 65470, 65474, 65479, 65482, 65487, 65490, 65495, 65498, 65500, 65536, 65547, 65549, 65574, 65576, 65594, 65596, 65597, 65599, 65613, 65616, 65629, 65664, 65786, 65856, 65908, 66045, 66045, 66176, 66204, 66208, 66256, 66272, 66272, 66304, 66335, 66349, 66378, 66384, 66426, 66432, 66461, 66464, 66499, 66504, 66511, 66513, 66517, 66560, 66717, 66720, 66729, 66736, 66771, 66776, 66811, 66816, 66855, 66864, 66915, 67072, 67382, 67392, 67413, 67424, 67431, 67584, 67589, 67592, 67592, 67594, 67637, 67639, 67640, 67644, 67644, 67647, 67669, 67680, 67702, 67712, 67742, 67808, 67826, 67828, 67829, 67840, 67861, 67872, 67897, 67968, 68023, 68030, 68031, 68096, 68099, 68101, 68102, 68108, 68115, 68117, 68119, 68121, 68149, 68152, 68154, 68159, 68159, 68192, 68220, 68224, 68252, 68288, 68295, 68297, 68326, 68352, 68405, 68416, 68437, 68448, 68466, 68480, 68497, 68608, 68680, 68736, 68786, 68800, 68850, 68864, 68903, 68912, 68921, 69376, 69404, 69415, 69415, 69424, 69456, 69600, 69622, 69632, 69702, 69734, 69743, 69759, 69818, 69840, 69864, 69872, 69881, 69888, 69940, 69942, 69951, 69956, 69958, 69968, 70003, 70006, 70006, 70016, 70084, 70089, 70092, 70096, 70106, 70108, 70108, 70144, 70161, 70163, 70199, 70206, 70206, 70272, 70278, 70280, 70280, 70282, 70285, 70287, 70301, 70303, 70312, 70320, 70378, 70384, 70393, 70400, 70403, 70405, 70412, 70415, 70416, 70419, 70440, 70442, 70448, 70450, 70451, 70453, 70457, 70459, 70468, 70471, 70472, 70475, 70477, 70480, 70480, 70487, 70487, 70493, 70499, 70502, 70508, 70512, 70516, 70656, 70730, 70736, 70745, 70750, 70751, 70784, 70853, 70855, 70855, 70864, 70873, 71040, 71093, 71096, 71104, 71128, 71133, 71168, 71232, 71236, 71236, 71248, 71257, 71296, 71352, 71360, 71369, 71424, 71450, 71453, 71467, 71472, 71481, 71680, 71738, 71840, 71913, 71935, 71935, 72096, 72103, 72106, 72151, 72154, 72161, 72163, 72164, 72192, 72254, 72263, 72263, 72272, 72345, 72349, 72349, 72384, 72440, 72704, 72712, 72714, 72758, 72760, 72768, 72784, 72793, 72818, 72847, 72850, 72871, 72873, 72886, 72960, 72966, 72968, 72969, 72971, 73014, 73018, 73018, 73020, 73021, 73023, 73031, 73040, 73049, 73056, 73061, 73063, 73064, 73066, 73102, 73104, 73105, 73107, 73112, 73120, 73129, 73440, 73462, 73728, 74649, 74752, 74862, 74880, 75075, 77824, 78894, 82944, 83526, 92160, 92728, 92736, 92766, 92768, 92777, 92880, 92909, 92912, 92916, 92928, 92982, 92992, 92995, 93008, 93017, 93027, 93047, 93053, 93071, 93760, 93823, 93952, 94026, 94031, 94087, 94095, 94111, 94176, 94177, 94179, 94179, 94208, 100343, 100352, 101106, 110592, 110878, 110928, 110930, 110948, 110951, 110960, 111355, 113664, 113770, 113776, 113788, 113792, 113800, 113808, 113817, 113821, 113822, 119141, 119145, 119149, 119154, 119163, 119170, 119173, 119179, 119210, 119213, 119362, 119364, 119808, 119892, 119894, 119964, 119966, 119967, 119970, 119970, 119973, 119974, 119977, 119980, 119982, 119993, 119995, 119995, 119997, 120003, 120005, 120069, 120071, 120074, 120077, 120084, 120086, 120092, 120094, 120121, 120123, 120126, 120128, 120132, 120134, 120134, 120138, 120144, 120146, 120485, 120488, 120512, 120514, 120538, 120540, 120570, 120572, 120596, 120598, 120628, 120630, 120654, 120656, 120686, 120688, 120712, 120714, 120744, 120746, 120770, 120772, 120779, 120782, 120831, 121344, 121398, 121403, 121452, 121461, 121461, 121476, 121476, 121499, 121503, 121505, 121519, 122880, 122886, 122888, 122904, 122907, 122913, 122915, 122916, 122918, 122922, 123136, 123180, 123184, 123197, 123200, 123209, 123214, 123214, 123584, 123641, 124928, 125124, 125136, 125142, 125184, 125259, 125264, 125273, 126464, 126467, 126469, 126495, 126497, 126498, 126500, 126500, 126503, 126503, 126505, 126514, 126516, 126519, 126521, 126521, 126523, 126523, 126530, 126530, 126535, 126535, 126537, 126537, 126539, 126539, 126541, 126543, 126545, 126546, 126548, 126548, 126551, 126551, 126553, 126553, 126555, 126555, 126557, 126557, 126559, 126559, 126561, 126562, 126564, 126564, 126567, 126570, 126572, 126578, 126580, 126583, 126585, 126588, 126590, 126590, 126592, 126601, 126603, 126619, 126625, 126627, 126629, 126633, 126635, 126651, 131072, 173782, 173824, 177972, 177984, 178205, 178208, 183969, 183984, 191456, 194560, 195101, 917760, 917999};

        /**
         * Test for whether a single line comment's text contains a directive.
         */
        regex commentDirectiveRegExSingleLine = regex(S("^\\s*\\/\\/\\/?\\s*@(ts-expect-error|ts-ignore)"));

        /**
         * Test for whether a multi-line comment's last line contains a directive.
         */
        regex commentDirectiveRegExMultiLine = regex(S("^\\s*(?:\\/|\\*)*\\s*@(ts-expect-error|ts-ignore)"));

        auto lookupInUnicodeMap(number code, std::vector<number> map) -> boolean
        {
            // Bail out quickly if it couldn't possibly be in the map.
            if (code < map[0])
            {
                return false;
            }

            // Perform binary search in one of the Unicode range maps
            auto lo = 0;
            auto hi = map.size();
            number mid;

            while (lo + 1 < hi)
            {
                mid = lo + (hi - lo) / 2;
                // mid has to be even to catch a range's beginning
                mid -= mid % 2;
                if (map[mid] <= code && code <= map[mid + 1])
                {
                    return true;
                }

                if (code < map[mid])
                {
                    hi = mid;
                }
                else
                {
                    lo = mid + 2;
                }
            }

            return false;
        }

        /* @internal */ auto isUnicodeIdentifierStart(CharacterCodes code, ScriptTarget languageVersion)
        {
            return languageVersion >= ScriptTarget::ES2015 ? lookupInUnicodeMap((number)code, unicodeESNextIdentifierStart) : languageVersion == ScriptTarget::ES5 ? lookupInUnicodeMap((number)code, unicodeES5IdentifierStart)
                                                                                                                                                                : lookupInUnicodeMap((number)code, unicodeES3IdentifierStart);
        }

        auto isUnicodeIdentifierPart(CharacterCodes code, ScriptTarget languageVersion)
        {
            return languageVersion >= ScriptTarget::ES2015 ? lookupInUnicodeMap((number)code, unicodeESNextIdentifierPart) : languageVersion == ScriptTarget::ES5 ? lookupInUnicodeMap((number)code, unicodeES5IdentifierPart)
                                                                                                                                                               : lookupInUnicodeMap((number)code, unicodeES3IdentifierPart);
        }

        auto makeReverseMap(std::map<string, SyntaxKind> source) -> std::map<SyntaxKind, string>
        {
            std::map<SyntaxKind, string> result;
            for (auto &item : source)
            {
                result[item.second] = item.first;
            };
            return result;
        }

        std::map<SyntaxKind, string> tokenStrings = makeReverseMap(textToToken);
public:        
        auto tokenToString(SyntaxKind t) -> string
        {
            return tokenStrings[t];
        }

        auto syntaxKindString(SyntaxKind t) -> string
        {
            return tokenToText[t];
        }

private:
        /* @internal */
        auto stringToToken(string s) -> SyntaxKind
        {
            return textToToken.at(s);
        }

        /* @internal */
        auto computeLineStarts(safe_string text) -> std::vector<number>
        {
            std::vector<number> result;
            auto pos = 0;
            auto lineStart = 0;
            while (pos < text.length())
            {
                auto ch = text[pos];
                pos++;
                switch (ch)
                {
                case CharacterCodes::carriageReturn:
                    if (text[pos] == CharacterCodes::lineFeed)
                    {
                        pos++;
                    }
                // falls through
                case CharacterCodes::lineFeed:
                    result.push_back(lineStart);
                    lineStart = pos;
                    break;
                default:
                    if (ch > CharacterCodes::maxAsciiCharacter && isLineBreak(ch))
                    {
                        result.push_back(lineStart);
                        lineStart = pos;
                    }
                    break;
                }
            }
            result.push_back(lineStart);
            return result;
        }

        auto getPositionOfLineAndCharacter(SourceFileLike sourceFile, number line, number character, bool allowEdits = true) -> number
        {
            return sourceFile.hasGetPositionOfLineAndCharacter ? sourceFile.getPositionOfLineAndCharacter(line, character, allowEdits) : computePositionOfLineAndCharacter(getLineStarts(sourceFile), line, character, sourceFile.text, allowEdits);
        }

        /* @internal */
        auto computePositionOfLineAndCharacter(std::vector<number> lineStarts, number line, number character, string debugText, bool allowEdits = true) -> number
        {
            if (line < 0 || line >= lineStarts.size())
            {
                if (allowEdits)
                {
                    // Clamp line to nearest allowable value
                    line = line < 0 ? 0 : line >= lineStarts.size() ? lineStarts.size() - 1
                                                                    : line;
                }
                else
                {
                    sstream msg;
                    msg << S("Bad line number. Line: ") << line << S("), lineStarts.length: ") << lineStarts.size() << S(" , line map is correct? ") << (!debugText.empty() ? arraysEqual(lineStarts, computeLineStarts(debugText)) : S("unknown"));
                    debug(msg.str());
                }
            }

            auto res = lineStarts[line] + character;
            if (allowEdits)
            {
                // Clamp to nearest allowable values to allow the underlying to be edited without crashing (accuracy is lost, instead)
                // TODO: Somehow track edits between file as it was during the creation of sourcemap we have and the current file and
                // apply them to the computed position to improve accuracy
                return res > lineStarts[line + 1] ? lineStarts[line + 1] : !debugText.empty() && res > debugText.length() ? debugText.length()
                                                                                                                          : res;
            }
            if (line < lineStarts.size() - 1)
            {
                debug(res < lineStarts[line + 1]);
            }
            else if (!debugText.empty())
            {
                debug(res <= debugText.length()); // Allow single character overflow for trailing newline
            }
            return res;
        }

        /* @internal */
        auto getLineStarts(SourceFileLike sourceFile) -> std::vector<number>
        {
            if (!sourceFile.lineMap.empty())
            {
                return sourceFile.lineMap;
            }

            auto lineMap = computeLineStarts(sourceFile.text);
            for (auto &item : lineMap)
            {
                sourceFile.lineMap.push_back(item);
            }
            return sourceFile.lineMap;
        }

        /* @internal */
        auto computeLineAndCharacterOfPosition(std::vector<number> lineStarts, number position) -> LineAndCharacter
        {
            auto lineNumber = computeLineOfPosition(lineStarts, position);
            return LineAndCharacter({lineNumber,
                                     position - lineStarts[lineNumber]});
        }

        /**
         * @internal
         * We assume the first line starts at position 0 and 'position' is non-negative.
         */
        auto computeLineOfPosition(std::vector<number> lineStarts, number position, number lowerBound = 0) -> number
        {
            auto lineNumber = binarySearch<number, number>(lineStarts, position, &identity<number>, &compareValues<number>, lowerBound);
            if (lineNumber < 0)
            {
                // If the actual position was not found,
                // the binary search returns the 2's-complement of the next line start
                // e.g. if the line starts at [5, 10, 23, 80] and the position requested was 20
                // then the search will return -2.
                //
                // We want the index of the previous line start, so we subtract 1.
                // Review 2's-complement if this is confusing.
                lineNumber = ~lineNumber - 1;
                debug(lineNumber != -1, S("position cannot precede the beginning of the file"));
            }
            return lineNumber;
        }

        /** @internal */
        auto getLinesBetweenPositions(SourceFileLike sourceFile, number pos1, number pos2)
        {
            if (pos1 == pos2)
                return 0;
            auto lineStarts = getLineStarts(sourceFile);
            auto lower = std::min(pos1, pos2);
            auto isNegative = lower == pos2;
            auto upper = isNegative ? pos1 : pos2;
            auto lowerLine = computeLineOfPosition(lineStarts, lower);
            auto upperLine = computeLineOfPosition(lineStarts, upper, lowerLine);
            return isNegative ? lowerLine - upperLine : upperLine - lowerLine;
        }

        auto getLineAndCharacterOfPosition(SourceFileLike sourceFile, number position) -> LineAndCharacter
        {
            return computeLineAndCharacterOfPosition(getLineStarts(sourceFile), position);
        }

        auto isWhiteSpaceLike(CharacterCodes ch) -> boolean
        {
            return isWhiteSpaceSingleLine(ch) || isLineBreak(ch);
        }

        /** Does not include line breaks. For that, see isWhiteSpaceLike. */
        auto isWhiteSpaceSingleLine(CharacterCodes ch) -> boolean
        {
            // Note: nextLine is in the Zs space, and should be considered to be a whitespace.
            // It is explicitly not a line-break as it isn't in the exact set specified by EcmaScript.
            return ch == CharacterCodes::space ||
                   ch == CharacterCodes::tab ||
                   ch == CharacterCodes::verticalTab ||
                   ch == CharacterCodes::formFeed ||
                   ch == CharacterCodes::nonBreakingSpace ||
                   ch == CharacterCodes::nextLine ||
                   ch == CharacterCodes::ogham ||
                   ch >= CharacterCodes::enQuad && ch <= CharacterCodes::zeroWidthSpace ||
                   ch == CharacterCodes::narrowNoBreakSpace ||
                   ch == CharacterCodes::mathematicalSpace ||
                   ch == CharacterCodes::ideographicSpace ||
                   ch == CharacterCodes::byteOrderMark;
        }

        auto isLineBreak(CharacterCodes ch) -> boolean
        {
            // ES5 7.3:
            // The ECMAScript line terminator characters are listed in Table 3.
            //     Table 3: Line Terminator Characters
            //     Code Unit Value     Name                    Formal Name
            //     \u000A              Line Feed               <LF>
            //     \u000D              Carriage Return         <CR>
            //     \u2028              Line separator          <LS>
            //     \u2029              Paragraph separator     <PS>
            // Only the characters in Table 3 are treated as line terminators. Other new line or line
            // breaking characters are treated as white space but not as line terminators.

            return ch == CharacterCodes::lineFeed ||
                   ch == CharacterCodes::carriageReturn ||
                   ch == CharacterCodes::lineSeparator ||
                   ch == CharacterCodes::paragraphSeparator;
        }

        auto isDigit(CharacterCodes ch) -> boolean
        {
            return ch >= CharacterCodes::_0 && ch <= CharacterCodes::_9;
        }

        auto isHexDigit(CharacterCodes ch) -> boolean
        {
            return isDigit(ch) || ch >= CharacterCodes::A && ch <= CharacterCodes::F || ch >= CharacterCodes::a && ch <= CharacterCodes::f;
        }

        auto isCodePoint(number code) -> boolean
        {
            return code <= 0x10FFFF;
        }

        /* @internal */
        auto isOctalDigit(CharacterCodes ch) -> boolean
        {
            return ch >= CharacterCodes::_0 && ch <= CharacterCodes::_7;
        }

        auto couldStartTrivia(safe_string &text, number pos) -> boolean
        {
            // Keep in sync with skipTrivia
            auto ch = text[pos];
            switch (ch)
            {
            case CharacterCodes::carriageReturn:
            case CharacterCodes::lineFeed:
            case CharacterCodes::tab:
            case CharacterCodes::verticalTab:
            case CharacterCodes::formFeed:
            case CharacterCodes::space:
            case CharacterCodes::slash:
            // starts of normal trivia
            // falls through
            case CharacterCodes::lessThan:
            case CharacterCodes::bar:
            case CharacterCodes::equals:
            case CharacterCodes::greaterThan:
                // Starts of conflict marker trivia
                return true;
            case CharacterCodes::hash:
                // Only if its the beginning can we have #! trivia
                return pos == 0;
            default:
                return ch > CharacterCodes::maxAsciiCharacter;
            }
        }

        /* @internal */
        auto skipTrivia(safe_string &text, number pos, bool stopAfterLineBreak = false, bool stopAtComments = false) -> number
        {
            if (positionIsSynthesized(pos))
            {
                return pos;
            }

            // Keep in sync with couldStartTrivia
            while (true)
            {
                auto ch = text[pos];
                switch (ch)
                {
                case CharacterCodes::carriageReturn:
                    if (text[pos + 1] == CharacterCodes::lineFeed)
                    {
                        pos++;
                    }
                // falls through
                case CharacterCodes::lineFeed:
                    pos++;
                    if (stopAfterLineBreak)
                    {
                        return pos;
                    }
                    continue;
                case CharacterCodes::tab:
                case CharacterCodes::verticalTab:
                case CharacterCodes::formFeed:
                case CharacterCodes::space:
                    pos++;
                    continue;
                case CharacterCodes::slash:
                    if (stopAtComments)
                    {
                        break;
                    }
                    if (text[pos + 1] == CharacterCodes::slash)
                    {
                        pos += 2;
                        while (pos < text.length())
                        {
                            if (isLineBreak(text[pos]))
                            {
                                break;
                            }
                            pos++;
                        }
                        continue;
                    }
                    if (text[pos + 1] == CharacterCodes::asterisk)
                    {
                        pos += 2;
                        while (pos < text.length())
                        {
                            if (text[pos] == CharacterCodes::asterisk && text[pos + 1] == CharacterCodes::slash)
                            {
                                pos += 2;
                                break;
                            }
                            pos++;
                        }
                        continue;
                    }
                    break;

                case CharacterCodes::lessThan:
                case CharacterCodes::bar:
                case CharacterCodes::equals:
                case CharacterCodes::greaterThan:
                    if (isConflictMarkerTrivia(text, pos))
                    {
                        pos = scanConflictMarkerTrivia(text, pos);
                        continue;
                    }
                    break;

                case CharacterCodes::hash:
                    if (pos == 0 && isShebangTrivia(text, pos))
                    {
                        pos = scanShebangTrivia(text, pos);
                        continue;
                    }
                    break;

                default:
                    if (ch > CharacterCodes::maxAsciiCharacter && (isWhiteSpaceLike(ch)))
                    {
                        pos++;
                        continue;
                    }
                    break;
                }
                return pos;
            }
        }

        // All conflict markers consist of the same character repeated seven times.  If it is
        // a <<<<<<< or >>>>>>> marker then it is also followed by a space.
        number mergeConflictMarkerLength = std::strlen("<<<<<<<");

        auto isConflictMarkerTrivia(safe_string &text, number pos) -> boolean
        {
            debug(pos >= 0);

            // Conflict markers must be at the start of a line.
            if (pos == 0 || isLineBreak(text[pos - 1]))
            {
                auto ch = text[pos];

                if ((pos + mergeConflictMarkerLength) < text.length())
                {
                    for (auto i = 0; i < mergeConflictMarkerLength; i++)
                    {
                        if (text[pos + i] != ch)
                        {
                            return false;
                        }
                    }

                    return ch == CharacterCodes::equals ||
                           text[pos + mergeConflictMarkerLength] == CharacterCodes::space;
                }
            }

            return false;
        }

        auto scanConflictMarkerTrivia(safe_string &text, number pos, std::function<void(DiagnosticMessage, number, number)> error = nullptr) -> number
        {
            if (error)
            {
                error(Diagnostics::Merge_conflict_marker_encountered, pos, mergeConflictMarkerLength);
            }

            auto ch = text[pos];
            auto len = text.length();

            if (ch == CharacterCodes::lessThan || ch == CharacterCodes::greaterThan)
            {
                while (pos < len && !isLineBreak(text[pos]))
                {
                    pos++;
                }
            }
            else
            {
                debug(ch == CharacterCodes::bar || ch == CharacterCodes::equals);
                // Consume everything from the start of a ||||||| or ===== marker to the start
                // of the next ===== or >>>>>>> marker.
                while (pos < len)
                {
                    auto currentChar = text[pos];
                    if ((currentChar == CharacterCodes::equals || currentChar == CharacterCodes::greaterThan) && currentChar != ch && isConflictMarkerTrivia(text, pos))
                    {
                        break;
                    }

                    pos++;
                }
            }

            return pos;
        }

        regex shebangTriviaRegex = regex(S("^#!.*"));

        /*@internal*/
        auto isShebangTrivia(string &text, number pos) -> boolean
        {
            // Shebangs check must only be done at the start of the file
            debug(pos == 0);
            return regex_search(text, shebangTriviaRegex);
        }

        /*@internal*/
        auto scanShebangTrivia(string &text, number pos) -> number
        {
            auto words_begin = sregex_iterator(text.begin(), text.end(), shebangTriviaRegex);
            auto words_end = sregex_iterator();
            for (auto i = words_begin; i != words_end; ++i)
            {
                auto match = *i;
                auto match_str = match.str();
                pos = pos + match_str.size();
                return pos;
            }

            return pos;
        }

        /**
         * Invokes a callback for each comment range following the provided position.
         *
         * Single-line comment ranges include the leading double-slash characters but not the ending
         * line break. Multi-line comment ranges include the leading slash-asterisk and trailing
         * asterisk-slash characters.
         *
         * @param reduce If true, accumulates the result of calling the callback in a fashion similar
         *      to reduceLeft. If false, iteration stops when the callback returns a truthy value.
         * @param text The source text to scan.
         * @param pos The position at which to start scanning.
         * @param trailing If false, whitespace is skipped until the first line break and comments
         *      between that location and the next token are returned. If true, comments occurring
         *      between the given position and the next line break are returned.
         * @param cb The callback to execute as each comment range is encountered.
         * @param state A state value to pass to each iteration of the callback.
         * @param initial An initial value to pass when accumulating results (when "reduce" is true).
         * @returns If "reduce" is true, the accumulated value. If "reduce" is false, the first truthy
         *      return value of the callback.
         */
        template <typename T, typename U>
        auto iterateCommentRanges(boolean reduce, safe_string text, number pos, boolean trailing, cb_type<T, U> cb, T state, U initial = U()) -> U
        {
            number pendingPos;
            number pendingEnd;
            SyntaxKind pendingKind;
            boolean pendingHasTrailingNewLine;
            auto hasPendingCommentRange = false;
            auto collecting = trailing;
            auto accumulator = initial;
            if (pos == 0)
            {
                collecting = true;
                auto shebang = getShebang(text);
                if (!shebang.empty())
                {
                    pos = shebang.length();
                }
            }

            while (pos >= 0 && pos < text.length())
            {
                auto ch = text[pos];
                switch (ch)
                {
                case CharacterCodes::carriageReturn:
                    if (text[pos + 1] == CharacterCodes::lineFeed)
                    {
                        pos++;
                    }
                // falls through
                case CharacterCodes::lineFeed:
                    pos++;
                    if (trailing)
                    {
                        goto scan;
                    }

                    collecting = true;
                    if (hasPendingCommentRange)
                    {
                        pendingHasTrailingNewLine = true;
                    }

                    continue;
                case CharacterCodes::tab:
                case CharacterCodes::verticalTab:
                case CharacterCodes::formFeed:
                case CharacterCodes::space:
                    pos++;
                    continue;
                case CharacterCodes::slash:
                {
                    auto nextChar = text[pos + 1];
                    auto hasTrailingNewLine = false;
                    if (nextChar == CharacterCodes::slash || nextChar == CharacterCodes::asterisk)
                    {
                        auto kind = nextChar == CharacterCodes::slash ? SyntaxKind::SingleLineCommentTrivia : SyntaxKind::MultiLineCommentTrivia;
                        auto startPos = pos;
                        pos += 2;
                        if (nextChar == CharacterCodes::slash)
                        {
                            while (pos < text.length())
                            {
                                if (isLineBreak(text[pos]))
                                {
                                    hasTrailingNewLine = true;
                                    break;
                                }
                                pos++;
                            }
                        }
                        else
                        {
                            while (pos < text.length())
                            {
                                if (text[pos] == CharacterCodes::asterisk && text[pos + 1] == CharacterCodes::slash)
                                {
                                    pos += 2;
                                    break;
                                }
                                pos++;
                            }
                        }

                        if (collecting)
                        {
                            if (hasPendingCommentRange)
                            {
                                accumulator = cb(pendingPos, pendingEnd, pendingKind, pendingHasTrailingNewLine, state, accumulator);
                                if (!reduce && !!accumulator)
                                {
                                    // If we are not reducing and we have a truthy result, return it.
                                    return accumulator;
                                }
                            }

                            pendingPos = startPos;
                            pendingEnd = pos;
                            pendingKind = kind;
                            pendingHasTrailingNewLine = hasTrailingNewLine;
                            hasPendingCommentRange = true;
                        }

                        continue;
                    }
                    goto scan;
                }
                default:
                    if (ch > CharacterCodes::maxAsciiCharacter && (isWhiteSpaceLike(ch)))
                    {
                        if (hasPendingCommentRange && isLineBreak(ch))
                        {
                            pendingHasTrailingNewLine = true;
                        }
                        pos++;
                        continue;
                    }
                    goto scan;
                }
            }
            scan:

            if (hasPendingCommentRange)
            {
                accumulator = cb(pendingPos, pendingEnd, pendingKind, pendingHasTrailingNewLine, state, accumulator);
            }

            return accumulator;
        }

        template <typename T, typename U>
        auto forEachLeadingCommentRange(string &text, number pos, cb_type<T, U> cb, T state = T()) -> U
        {
            return iterateCommentRanges(/*reduce*/ false, text, pos, /*trailing*/ false, cb, state);
        }

        template <typename T, typename U>
        auto forEachTrailingCommentRange(string &text, number pos, cb_type<T, U> cb, T state = T()) -> U
        {
            return iterateCommentRanges(/*reduce*/ false, text, pos, /*trailing*/ true, cb, state);
        }

        template <typename T, typename U>
        auto reduceEachLeadingCommentRange(string &text, number pos, cb_type<T, U> cb, T state, U initial)
        {
            return iterateCommentRanges(/*reduce*/ true, text, pos, /*trailing*/ false, cb, state, initial);
        }

        template <typename T, typename U>
        auto reduceEachTrailingCommentRange(string &text, number pos, cb_type<T, U> cb, T state, U initial)
        {
            return iterateCommentRanges(/*reduce*/ true, text, pos, /*trailing*/ true, cb, state, initial);
        }

        auto appendCommentRange(number pos, number end, SyntaxKind kind, boolean hasTrailingNewLine, number state, std::vector<CommentRange> comments) -> std::vector<CommentRange>
        {
            comments.push_back({kind, pos, end, hasTrailingNewLine});
            return comments;
        }

        auto getLeadingCommentRanges(string &text, number pos) -> std::vector<CommentRange>
        {
            return reduceEachLeadingCommentRange<number, std::vector<CommentRange>>(
                text,
                pos,
                std::bind(&ScannerImpl::appendCommentRange, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6),
                0,
                std::vector<CommentRange>());
        }

        auto getTrailingCommentRanges(string &text, number pos) -> std::vector<CommentRange>
        {
            return reduceEachTrailingCommentRange<number, std::vector<CommentRange>>(
                text,
                pos,
                std::bind(&ScannerImpl::appendCommentRange, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6),
                0,
                std::vector<CommentRange>());
        }

        /** Optionally, get the shebang */
        auto getShebang(string &text) -> string
        {
            auto words_begin = sregex_iterator(text.begin(), text.end(), shebangTriviaRegex);
            auto words_end = sregex_iterator();
            for (auto i = words_begin; i != words_end; ++i)
            {
                auto match = *i;
                return match.str();
            }

            return string();
        }

        auto isIdentifierStart(CharacterCodes ch, ScriptTarget languageVersion) -> boolean
        {
            return ch >= CharacterCodes::A && ch <= CharacterCodes::Z || ch >= CharacterCodes::a && ch <= CharacterCodes::z ||
                   ch == CharacterCodes::$ || ch == CharacterCodes::_ ||
                   ch > CharacterCodes::maxAsciiCharacter && isUnicodeIdentifierStart(ch, languageVersion);
        }

        auto isIdentifierPart(CharacterCodes ch, ScriptTarget languageVersion, LanguageVariant identifierVariant = LanguageVariant::Standard) -> boolean
        {
            return ch >= CharacterCodes::A && ch <= CharacterCodes::Z || ch >= CharacterCodes::a && ch <= CharacterCodes::z ||
                   ch >= CharacterCodes::_0 && ch <= CharacterCodes::_9 || ch == CharacterCodes::$ || ch == CharacterCodes::_ ||
                   // "-" and ":" are valid in JSX Identifiers
                   (identifierVariant == LanguageVariant::JSX ? (ch == CharacterCodes::minus || ch == CharacterCodes::colon) : false) ||
                   ch > CharacterCodes::maxAsciiCharacter && isUnicodeIdentifierPart(ch, languageVersion);
        }

        /* @internal */
        auto isIdentifierText(safe_string &name, ScriptTarget languageVersion, LanguageVariant identifierVariant = LanguageVariant::Standard) -> boolean
        {
            auto ch = codePointAt(name, 0);
            if (!isIdentifierStart(ch, languageVersion))
            {
                return false;
            }

            for (auto i = charSize(ch); i < name.length(); i += charSize(ch))
            {
                if (!isIdentifierPart((ch = codePointAt(name, i)), languageVersion, identifierVariant))
                {
                    return false;
                }
            }

            return true;
        }

        ScriptTarget languageVersion;

        boolean _skipTrivia;

        LanguageVariant languageVariant;

public:
        // scanner text
        safe_string text;

        // Current position (end position of text of current token)
        number pos;

        // end of text
        number end;

        // Start position of whitespace before current token
        number startPos;

        // Start position of text of current token
        number tokenPos;

        SyntaxKind token;
        string tokenValue;
        TokenFlags tokenFlags;

private:
        std::vector<CommentDirective> commentDirectives;
        number inJSDocType = 0;

        ErrorCallback onError = nullptr;

public:
        // Creates a scanner over a (possibly unspecified) range of a piece of text.
        static auto createScanner(ScriptTarget languageVersion,
                                  boolean skipTrivia,
                                  LanguageVariant languageVariant = LanguageVariant::Standard,
                                  string textInitial = string(),
                                  ErrorCallback onError = nullptr,
                                  number start = 0,
                                  number length = -1) -> ScannerImpl*
        {

            auto scanner = new ScannerImpl();
            scanner->languageVersion = languageVersion;
            scanner->_skipTrivia = skipTrivia;
            scanner->languageVariant = languageVariant;
            scanner->onError = onError;
            scanner->setText(textInitial, start, length);
            return scanner;
        }

private:
        auto error(DiagnosticMessage message, number errPos = -1, number length = 0) -> void
        {
            if (errPos < 0)
            {
                errPos = pos;
            }

            if (onError)
            {
                auto oldPos = pos;
                pos = errPos;
                onError(message, length);
                pos = oldPos;
            }
        }

        auto scanNumberFragment() -> string
        {
            auto start = pos;
            auto allowSeparator = false;
            auto isPreviousTokenSeparator = false;
            auto result = string();
            while (true)
            {
                auto ch = text[pos];
                if (ch == CharacterCodes::_)
                {
                    tokenFlags |= TokenFlags::ContainsSeparator;
                    if (allowSeparator)
                    {
                        allowSeparator = false;
                        isPreviousTokenSeparator = true;
                        result += text.substring(start, pos);
                    }
                    else if (isPreviousTokenSeparator)
                    {
                        error(Diagnostics::Multiple_consecutive_numeric_separators_are_not_permitted, pos, 1);
                    }
                    else
                    {
                        error(Diagnostics::Numeric_separators_are_not_allowed_here, pos, 1);
                    }
                    pos++;
                    start = pos;
                    continue;
                }
                if (isDigit(ch))
                {
                    allowSeparator = true;
                    isPreviousTokenSeparator = false;
                    pos++;
                    continue;
                }
                break;
            }
            if (text[pos - 1] == CharacterCodes::_)
            {
                error(Diagnostics::Numeric_separators_are_not_allowed_here, pos - 1, 1);
            }
            return result + text.substring(start, pos);
        }

        auto scanNumber() -> ScanResult
        {
            auto start = pos;
            auto mainFragment = scanNumberFragment();
            string decimalFragment;
            string scientificFragment;
            if (text[pos] == CharacterCodes::dot)
            {
                pos++;
                decimalFragment = scanNumberFragment();
            }
            auto end = pos;
            if (text[pos] == CharacterCodes::E || text[pos] == CharacterCodes::e)
            {
                pos++;
                tokenFlags |= TokenFlags::Scientific;
                if (text[pos] == CharacterCodes::plus || text[pos] == CharacterCodes::minus)
                    pos++;
                auto preNumericPart = pos;
                auto finalFragment = scanNumberFragment();
                if (finalFragment.empty())
                {
                    error(Diagnostics::Digit_expected);
                }
                else
                {
                    scientificFragment = text.substring(end, preNumericPart) + finalFragment;
                    end = pos;
                }
            }
            string result;
            if (!!(tokenFlags & TokenFlags::ContainsSeparator))
            {
                result = mainFragment;
                if (!decimalFragment.empty())
                {
                    result += S(".") + decimalFragment;
                }
                if (!scientificFragment.empty())
                {
                    result += scientificFragment;
                }
            }
            else
            {
                result = text.substring(start, end); // No need to use all the fragments; no _ removal needed
            }

            if (!decimalFragment.empty() || !!(tokenFlags & TokenFlags::Scientific))
            {
                checkForIdentifierStartAfterNumericLiteral(start, decimalFragment.empty() && !!(tokenFlags & TokenFlags::Scientific));
                return {
                    SyntaxKind::NumericLiteral,
                    to_string(+to_float(result)) // if value is not an integer, it can be safely coerced to a number
                };
            }
            else
            {
                tokenValue = result;
                auto type = checkBigIntSuffix(); // if value is an integer, check whether it is a bigint
                checkForIdentifierStartAfterNumericLiteral(start);
                return {type, tokenValue};
            }
        }

        auto checkForIdentifierStartAfterNumericLiteral(number numericStart, bool isScientific = false) -> void
        {
            if (!isIdentifierStart(codePointAt(text, pos), languageVersion))
            {
                return;
            }

            auto identifierStart = pos;
            auto length = scanIdentifierParts().length();

            if (length == 1 && text[identifierStart] == CharacterCodes::n)
            {
                if (isScientific)
                {
                    error(Diagnostics::A_bigint_literal_cannot_use_exponential_notation, numericStart, identifierStart - numericStart + 1);
                }
                else
                {
                    error(Diagnostics::A_bigint_literal_must_be_an_integer, numericStart, identifierStart - numericStart + 1);
                }
            }
            else
            {
                error(Diagnostics::An_identifier_or_keyword_cannot_immediately_follow_a_numeric_literal, identifierStart, length);
                pos = identifierStart;
            }
        }

        auto scanOctalDigits() -> number
        {
            auto start = pos;
            while (isOctalDigit(text[pos]))
            {
                pos++;
            }
            return +std::stod((text.substring(start, pos)));
        }

        /**
         * Scans the given number of hexadecimal digits in the text,
         * returning -1 if the given number is unavailable.
         */
        auto scanExactNumberOfHexDigits(number count, boolean canHaveSeparators) -> number
        {
            auto valueString = scanHexDigits(/*minCount*/ count, /*scanAsManyAsPossible*/ false, canHaveSeparators);
            return !valueString.empty() ? to_number_base(valueString, 16) : -1;
        }

        /**
         * Scans as many hexadecimal digits as are available in the text,
         * returning string() if the given number of digits was unavailable.
         */
        auto scanMinimumNumberOfHexDigits(number count, boolean canHaveSeparators) -> string
        {
            return scanHexDigits(/*minCount*/ count, /*scanAsManyAsPossible*/ true, canHaveSeparators);
        }

        auto scanHexDigits(number minCount, boolean scanAsManyAsPossible, boolean canHaveSeparators) -> string
        {
            std::vector<char_t> valueChars;
            auto allowSeparator = false;
            auto isPreviousTokenSeparator = false;
            while (valueChars.size() < minCount || scanAsManyAsPossible)
            {
                auto ch = text[pos];
                if (canHaveSeparators && ch == CharacterCodes::_)
                {
                    tokenFlags |= TokenFlags::ContainsSeparator;
                    if (allowSeparator)
                    {
                        allowSeparator = false;
                        isPreviousTokenSeparator = true;
                    }
                    else if (isPreviousTokenSeparator)
                    {
                        error(Diagnostics::Multiple_consecutive_numeric_separators_are_not_permitted, pos, 1);
                    }
                    else
                    {
                        error(Diagnostics::Numeric_separators_are_not_allowed_here, pos, 1);
                    }
                    pos++;
                    continue;
                }
                allowSeparator = canHaveSeparators;
                if (ch >= CharacterCodes::A && ch <= CharacterCodes::F)
                {
                    ch = (CharacterCodes) ((number)ch + ((number)CharacterCodes::a - (number)CharacterCodes::A)); // standardize hex literals to lowercase
                }
                else if (!((ch >= CharacterCodes::_0 && ch <= CharacterCodes::_9) ||
                           (ch >= CharacterCodes::a && ch <= CharacterCodes::f)))
                {
                    break;
                }
                valueChars.push_back((char_t)ch);
                pos++;
                isPreviousTokenSeparator = false;
            }
            if (valueChars.size() < minCount)
            {
                valueChars.clear();
            }
            if (text[pos - 1] == CharacterCodes::_)
            {
                error(Diagnostics::Numeric_separators_are_not_allowed_here, pos - 1, 1);
            }
            return string(valueChars.begin(), valueChars.end());
        }

        auto scanString(boolean jsxAttributeString = false) -> string
        {
            auto quote = text[pos];
            pos++;
            string result;
            auto start = pos;
            while (true)
            {
                if (pos >= end)
                {
                    result += text.substring(start, pos);
                    tokenFlags |= TokenFlags::Unterminated;
                    error(Diagnostics::Unterminated_string_literal);
                    break;
                }
                auto ch = text[pos];
                if (ch == quote)
                {
                    result += text.substring(start, pos);
                    pos++;
                    break;
                }
                if (ch == CharacterCodes::backslash && !jsxAttributeString)
                {
                    result += text.substring(start, pos);
                    result += scanEscapeSequence();
                    start = pos;
                    continue;
                }
                if (isLineBreak(ch) && !jsxAttributeString)
                {
                    result += text.substring(start, pos);
                    tokenFlags |= TokenFlags::Unterminated;
                    error(Diagnostics::Unterminated_string_literal);
                    break;
                }
                pos++;
            }
            return result;
        }

        /**
         * Sets the current 'tokenValue' and returns a NoSubstitutionTemplateLiteral or
         * a literal component of a TemplateExpression.
         */
        auto scanTemplateAndSetTokenValue(boolean isTaggedTemplate) -> SyntaxKind
        {
            auto startedWithBacktick = text[pos] == CharacterCodes::backtick;

            pos++;
            auto start = pos;
            string contents;
            SyntaxKind resultingToken;

            while (true)
            {
                if (pos >= end)
                {
                    contents += text.substring(start, pos);
                    tokenFlags |= TokenFlags::Unterminated;
                    error(Diagnostics::Unterminated_template_literal);
                    resultingToken = startedWithBacktick ? SyntaxKind::NoSubstitutionTemplateLiteral : SyntaxKind::TemplateTail;
                    break;
                }

                auto currChar = text[pos];

                // '`'
                if (currChar == CharacterCodes::backtick)
                {
                    contents += text.substring(start, pos);
                    pos++;
                    resultingToken = startedWithBacktick ? SyntaxKind::NoSubstitutionTemplateLiteral : SyntaxKind::TemplateTail;
                    break;
                }

                // '${'
                if (currChar == CharacterCodes::$ && pos + 1 < end && text[pos + 1] == CharacterCodes::openBrace)
                {
                    contents += text.substring(start, pos);
                    pos += 2;
                    resultingToken = startedWithBacktick ? SyntaxKind::TemplateHead : SyntaxKind::TemplateMiddle;
                    break;
                }

                // Escape character
                if (currChar == CharacterCodes::backslash)
                {
                    contents += text.substring(start, pos);
                    contents += scanEscapeSequence(isTaggedTemplate);
                    start = pos;
                    continue;
                }

                // Speculated ECMAScript 6 Spec 11.8.6.1:
                // <CR><LF> and <CR> LineTerminatorSequences are normalized to <LF> for Template Values
                if (currChar == CharacterCodes::carriageReturn)
                {
                    contents += text.substring(start, pos);
                    pos++;

                    if (pos < end && text[pos] == CharacterCodes::lineFeed)
                    {
                        pos++;
                    }

                    contents += S("\n");
                    start = pos;
                    continue;
                }

                pos++;
            }

            debug(resultingToken != SyntaxKind::Unknown);

            tokenValue = contents;
            return resultingToken;
        }

        auto scanEscapeSequence(boolean isTaggedTemplate = false) -> string
        {
            auto start = pos;
            pos++;
            if (pos >= end)
            {
                error(Diagnostics::Unexpected_end_of_text);
                return string();
            }
            auto ch = text[pos];
            pos++;
            switch (ch)
            {
            case CharacterCodes::_0:
                // '\01'
                if (isTaggedTemplate && pos < end && isDigit(text[pos]))
                {
                    pos++;
                    tokenFlags |= TokenFlags::ContainsInvalidEscape;
                    return text.substring(start, pos);
                }
                return S("\0");
            case CharacterCodes::b:
                return S("\b");
            case CharacterCodes::t:
                return S("\t");
            case CharacterCodes::n:
                return S("\n");
            case CharacterCodes::v:
                return S("\v");
            case CharacterCodes::f:
                return S("\f");
            case CharacterCodes::r:
                return S("\r");
            case CharacterCodes::singleQuote:
                return S("\'");
            case CharacterCodes::doubleQuote:
                return S("\"");
            case CharacterCodes::u:
                if (isTaggedTemplate)
                {
                    // '\u' or '\u0' or '\u00' or '\u000'
                    for (auto escapePos = pos; escapePos < pos + 4; escapePos++)
                    {
                        if (escapePos < end && !isHexDigit(text[escapePos]) && text[escapePos] != CharacterCodes::openBrace)
                        {
                            pos = escapePos;
                            tokenFlags |= TokenFlags::ContainsInvalidEscape;
                            return text.substring(start, pos);
                        }
                    }
                }
                // '\u{DDDDDDDD}'
                if (pos < end && text[pos] == CharacterCodes::openBrace)
                {
                    pos++;

                    // '\u{'
                    if (isTaggedTemplate && !isHexDigit(text[pos]))
                    {
                        tokenFlags |= TokenFlags::ContainsInvalidEscape;
                        return text.substring(start, pos);
                    }

                    if (isTaggedTemplate)
                    {
                        auto savePos = pos;
                        auto escapedValueString = scanMinimumNumberOfHexDigits(1, /*canHaveSeparators*/ false);
                        auto escapedValue = !escapedValueString.empty() ? to_number_base(escapedValueString, 16) : -1;

                        // '\u{Not Code Point' or '\u{CodePoint'
                        if (!isCodePoint(escapedValue) || text[pos] != CharacterCodes::closeBrace)
                        {
                            tokenFlags |= TokenFlags::ContainsInvalidEscape;
                            return text.substring(start, pos);
                        }
                        else
                        {
                            pos = savePos;
                        }
                    }
                    tokenFlags |= TokenFlags::ExtendedUnicodeEscape;
                    return scanExtendedUnicodeEscape();
                }

                tokenFlags |= TokenFlags::UnicodeEscape;
                // '\uDDDD'
                return scanHexadecimalEscape(/*numDigits*/ 4);

            case CharacterCodes::x:
                if (isTaggedTemplate)
                {
                    if (!isHexDigit(text[pos]))
                    {
                        tokenFlags |= TokenFlags::ContainsInvalidEscape;
                        return text.substring(start, pos);
                    }
                    else if (!isHexDigit(text[pos + 1]))
                    {
                        pos++;
                        tokenFlags |= TokenFlags::ContainsInvalidEscape;
                        return text.substring(start, pos);
                    }
                }
                // '\xDD'
                return scanHexadecimalEscape(/*numDigits*/ 2);

            // when encountering a LineContinuation (i.e. a backslash and a line terminator sequence),
            // the line terminator is interpreted to be "the empty code unit sequence".
            case CharacterCodes::carriageReturn:
                if (pos < end && text[pos] == CharacterCodes::lineFeed)
                {
                    pos++;
                }
            // falls through
            case CharacterCodes::lineFeed:
            case CharacterCodes::lineSeparator:
            case CharacterCodes::paragraphSeparator:
                return string();
            default:
                return string(1, (char_t)ch);
            }
        }

        auto scanHexadecimalEscape(number numDigits) -> string
        {
            auto escapedValue = scanExactNumberOfHexDigits(numDigits, /*canHaveSeparators*/ false);

            if (escapedValue >= 0)
            {
                return string(1, (char_t)escapedValue);
            }
            else
            {
                error(Diagnostics::Hexadecimal_digit_expected);
                return string();
            }
        }

        auto scanExtendedUnicodeEscape() -> string
        {
            auto escapedValueString = scanMinimumNumberOfHexDigits(1, /*canHaveSeparators*/ false);
            auto escapedValue = !escapedValueString.empty() ? to_number_base(escapedValueString, 16) : -1;
            auto isInvalidExtendedEscape = false;

            // Validate the value of the digit
            if (escapedValue < 0)
            {
                error(Diagnostics::Hexadecimal_digit_expected);
                isInvalidExtendedEscape = true;
            }
            else if (escapedValue > 0x10FFFF)
            {
                error(Diagnostics::An_extended_Unicode_escape_value_must_be_between_0x0_and_0x10FFFF_inclusive);
                isInvalidExtendedEscape = true;
            }

            if (pos >= end)
            {
                error(Diagnostics::Unexpected_end_of_text);
                isInvalidExtendedEscape = true;
            }
            else if (text[pos] == CharacterCodes::closeBrace)
            {
                // Only swallow the following character up if it's a '}'.
                pos++;
            }
            else
            {
                error(Diagnostics::Unterminated_Unicode_escape_sequence);
                isInvalidExtendedEscape = true;
            }

            if (isInvalidExtendedEscape)
            {
                return string();
            }

            return utf16EncodeAsString((CharacterCodes) escapedValue);
        }

        // Current character is known to be a backslash. Check for Unicode escape of the form '\uXXXX'
        // and return code point value if valid Unicode escape is found. Otherwise return -1.
        auto peekUnicodeEscape() -> CharacterCodes
        {
            if (pos + 5 < end && text[pos + 1] == CharacterCodes::u)
            {
                auto start = pos;
                pos += 2;
                auto value = scanExactNumberOfHexDigits(4, /*canHaveSeparators*/ false);
                pos = start;
                return (CharacterCodes) value;
            }
            return CharacterCodes::outOfBoundary;
        }

        auto peekExtendedUnicodeEscape() -> CharacterCodes
        {
            if (languageVersion >= ScriptTarget::ES2015 && codePointAt(text, pos + 1) == CharacterCodes::u && codePointAt(text, pos + 2) == CharacterCodes::openBrace)
            {
                auto start = pos;
                pos += 3;
                auto escapedValueString = scanMinimumNumberOfHexDigits(1, /*canHaveSeparators*/ false);
                auto escapedValue = !escapedValueString.empty() ? to_number_base(escapedValueString, 16) : -1;
                pos = start;
                return (CharacterCodes) escapedValue;
            }
            return CharacterCodes::outOfBoundary;
        }

        auto scanIdentifierParts() -> string
        {
            string result;
            auto start = pos;
            while (pos < end)
            {
                auto ch = codePointAt(text, pos);
                if (isIdentifierPart(ch, languageVersion))
                {
                    pos += charSize(ch);
                }
                else if (ch == CharacterCodes::backslash)
                {
                    ch = peekExtendedUnicodeEscape();
                    if (ch >= CharacterCodes::nullCharacter && isIdentifierPart(ch, languageVersion))
                    {
                        pos += 3;
                        tokenFlags |= TokenFlags::ExtendedUnicodeEscape;
                        result += scanExtendedUnicodeEscape();
                        start = pos;
                        continue;
                    }
                    ch = peekUnicodeEscape();
                    if (!(ch >= CharacterCodes::nullCharacter && isIdentifierPart(ch, languageVersion)))
                    {
                        break;
                    }
                    tokenFlags |= TokenFlags::UnicodeEscape;
                    result += text.substring(start, pos);
                    result += utf16EncodeAsString(ch);
                    // Valid Unicode escape is always six characters
                    pos += 6;
                    start = pos;
                }
                else
                {
                    break;
                }
            }
            result += text.substring(start, pos);
            return result;
        }

        auto getIdentifierToken() -> SyntaxKind
        {
            // Reserved words are between 2 and 12 characters long and start with a lowercase letter
            auto len = tokenValue.size();
            if (len >= 2 && len <= 12)
            {
                auto ch = (CharacterCodes) tokenValue[0];
                if (ch >= CharacterCodes::a && ch <= CharacterCodes::z)
                {
                    auto keyword = textToKeyword[tokenValue];
                    if (keyword != SyntaxKind::Unknown)
                    {
                        return token = keyword;
                    }
                }
            }
            return token = SyntaxKind::Identifier;
        }

        auto scanBinaryOrOctalDigits(number base) -> string
        {
            string value;
            // For counting number of digits; Valid binaryIntegerLiteral must have at least one binary digit following B or b.
            // Similarly valid octalIntegerLiteral must have at least one octal digit following o or O.
            auto separatorAllowed = false;
            auto isPreviousTokenSeparator = false;
            while (true)
            {
                auto ch = text[pos];
                // Numeric separators are allowed anywhere within a numeric literal, except not at the beginning, or following another separator
                if (ch == CharacterCodes::_)
                {
                    tokenFlags |= TokenFlags::ContainsSeparator;
                    if (separatorAllowed)
                    {
                        separatorAllowed = false;
                        isPreviousTokenSeparator = true;
                    }
                    else if (isPreviousTokenSeparator)
                    {
                        error(Diagnostics::Multiple_consecutive_numeric_separators_are_not_permitted, pos, 1);
                    }
                    else
                    {
                        error(Diagnostics::Numeric_separators_are_not_allowed_here, pos, 1);
                    }
                    pos++;
                    continue;
                }
                separatorAllowed = true;
                if (!isDigit(ch) || ((number)ch - (number)CharacterCodes::_0) >= base)
                {
                    break;
                }
                value += (char_t) text[pos];
                pos++;
                isPreviousTokenSeparator = false;
            }
            if (text[pos - 1] == CharacterCodes::_)
            {
                // Literal ends with underscore - not allowed
                error(Diagnostics::Numeric_separators_are_not_allowed_here, pos - 1, 1);
            }
            return value;
        }

        auto checkBigIntSuffix() -> SyntaxKind
        {
            if (text[pos] == CharacterCodes::n)
            {
                tokenValue += S("n");
                // Use base 10 instead of base 2 or base 8 for shorter literals
                if (!!(tokenFlags & TokenFlags::BinaryOrOctalSpecifier))
                {
                    tokenValue = parsePseudoBigInt(tokenValue) + S("n");
                }
                pos++;
                return SyntaxKind::BigIntLiteral;
            }
            else
            { // not a bigint, so can convert to number in simplified form
                // Number() may not support 0b or 0o, so use stoi() instead
                auto numericValue = !!(tokenFlags & TokenFlags::BinarySpecifier)
                                        ? to_string(to_bignumber_base(tokenValue.substr(2), 2)) // skip "0b"
                                        : !!(tokenFlags & TokenFlags::OctalSpecifier)
                                            ? to_string(to_bignumber_base(tokenValue.substr(2), 8)) // skip "0o"
                                            : to_string(+to_bignumber(tokenValue));
                tokenValue = numericValue;
                return SyntaxKind::NumericLiteral;
            }
        }

    public:
        auto scan() -> SyntaxKind
        {
            startPos = pos;
            tokenFlags = TokenFlags::None;
            auto asteriskSeen = false;
            while (true)
            {
                tokenPos = pos;
                if (pos >= end)
                {
                    return token = SyntaxKind::EndOfFileToken;
                }
                auto ch = codePointAt(text, pos);

                // Special handling for shebang
                if (ch == CharacterCodes::hash && pos == 0 && isShebangTrivia(text, pos))
                {
                    pos = scanShebangTrivia(text, pos);
                    if (_skipTrivia)
                    {
                        continue;
                    }
                    else
                    {
                        return token = SyntaxKind::ShebangTrivia;
                    }
                }

                switch (ch)
                {
                case CharacterCodes::lineFeed:
                case CharacterCodes::carriageReturn:
                    tokenFlags |= TokenFlags::PrecedingLineBreak;
                    if (_skipTrivia)
                    {
                        pos++;
                        continue;
                    }
                    else
                    {
                        if (ch == CharacterCodes::carriageReturn && pos + 1 < end && text[pos + 1] == CharacterCodes::lineFeed)
                        {
                            // consume both CR and LF
                            pos += 2;
                        }
                        else
                        {
                            pos++;
                        }
                        return token = SyntaxKind::NewLineTrivia;
                    }
                case CharacterCodes::tab:
                case CharacterCodes::verticalTab:
                case CharacterCodes::formFeed:
                case CharacterCodes::space:
                case CharacterCodes::nonBreakingSpace:
                case CharacterCodes::ogham:
                case CharacterCodes::enQuad:
                case CharacterCodes::emQuad:
                case CharacterCodes::enSpace:
                case CharacterCodes::emSpace:
                case CharacterCodes::threePerEmSpace:
                case CharacterCodes::fourPerEmSpace:
                case CharacterCodes::sixPerEmSpace:
                case CharacterCodes::figureSpace:
                case CharacterCodes::punctuationSpace:
                case CharacterCodes::thinSpace:
                case CharacterCodes::hairSpace:
                case CharacterCodes::zeroWidthSpace:
                case CharacterCodes::narrowNoBreakSpace:
                case CharacterCodes::mathematicalSpace:
                case CharacterCodes::ideographicSpace:
                case CharacterCodes::byteOrderMark:
                    if (_skipTrivia)
                    {
                        pos++;
                        continue;
                    }
                    else
                    {
                        while (pos < end && isWhiteSpaceSingleLine(text[pos]))
                        {
                            pos++;
                        }
                        return token = SyntaxKind::WhitespaceTrivia;
                    }
                case CharacterCodes::exclamation:
                    if (text[pos + 1] == CharacterCodes::equals)
                    {
                        if (text[pos + 2] == CharacterCodes::equals)
                        {
                            return pos += 3, token = SyntaxKind::ExclamationEqualsEqualsToken;
                        }
                        return pos += 2, token = SyntaxKind::ExclamationEqualsToken;
                    }
                    pos++;
                    return token = SyntaxKind::ExclamationToken;
                case CharacterCodes::doubleQuote:
                case CharacterCodes::singleQuote:
                    tokenValue = scanString();
                    return token = SyntaxKind::StringLiteral;
                case CharacterCodes::backtick:
                    return token = scanTemplateAndSetTokenValue(/* isTaggedTemplate */ false);
                case CharacterCodes::percent:
                    if (text[pos + 1] == CharacterCodes::equals)
                    {
                        return pos += 2, token = SyntaxKind::PercentEqualsToken;
                    }
                    pos++;
                    return token = SyntaxKind::PercentToken;
                case CharacterCodes::ampersand:
                    if (text[pos + 1] == CharacterCodes::ampersand)
                    {
                        if (text[pos + 2] == CharacterCodes::equals)
                        {
                            return pos += 3, token = SyntaxKind::AmpersandAmpersandEqualsToken;
                        }
                        return pos += 2, token = SyntaxKind::AmpersandAmpersandToken;
                    }
                    if (text[pos + 1] == CharacterCodes::equals)
                    {
                        return pos += 2, token = SyntaxKind::AmpersandEqualsToken;
                    }
                    pos++;
                    return token = SyntaxKind::AmpersandToken;
                case CharacterCodes::openParen:
                    pos++;
                    return token = SyntaxKind::OpenParenToken;
                case CharacterCodes::closeParen:
                    pos++;
                    return token = SyntaxKind::CloseParenToken;
                case CharacterCodes::asterisk:
                    if (text[pos + 1] == CharacterCodes::equals)
                    {
                        return pos += 2, token = SyntaxKind::AsteriskEqualsToken;
                    }
                    if (text[pos + 1] == CharacterCodes::asterisk)
                    {
                        if (text[pos + 2] == CharacterCodes::equals)
                        {
                            return pos += 3, token = SyntaxKind::AsteriskAsteriskEqualsToken;
                        }
                        return pos += 2, token = SyntaxKind::AsteriskAsteriskToken;
                    }
                    pos++;
                    if (inJSDocType && !asteriskSeen && !!(tokenFlags & TokenFlags::PrecedingLineBreak))
                    {
                        // decoration at the start of a JSDoc comment line
                        asteriskSeen = true;
                        continue;
                    }
                    return token = SyntaxKind::AsteriskToken;
                case CharacterCodes::plus:
                    if (text[pos + 1] == CharacterCodes::plus)
                    {
                        return pos += 2, token = SyntaxKind::PlusPlusToken;
                    }
                    if (text[pos + 1] == CharacterCodes::equals)
                    {
                        return pos += 2, token = SyntaxKind::PlusEqualsToken;
                    }
                    pos++;
                    return token = SyntaxKind::PlusToken;
                case CharacterCodes::comma:
                    pos++;
                    return token = SyntaxKind::CommaToken;
                case CharacterCodes::minus:
                    if (text[pos + 1] == CharacterCodes::minus)
                    {
                        return pos += 2, token = SyntaxKind::MinusMinusToken;
                    }
                    if (text[pos + 1] == CharacterCodes::equals)
                    {
                        return pos += 2, token = SyntaxKind::MinusEqualsToken;
                    }
                    pos++;
                    return token = SyntaxKind::MinusToken;
                case CharacterCodes::dot:
                    if (isDigit(text[pos + 1]))
                    {
                        tokenValue = scanNumber().value;
                        return token = SyntaxKind::NumericLiteral;
                    }
                    if (text[pos + 1] == CharacterCodes::dot && text[pos + 2] == CharacterCodes::dot)
                    {
                        return pos += 3, token = SyntaxKind::DotDotDotToken;
                    }
                    pos++;
                    return token = SyntaxKind::DotToken;
                case CharacterCodes::slash:
                    // Single-line comment
                    if (text[pos + 1] == CharacterCodes::slash)
                    {
                        pos += 2;

                        while (pos < end)
                        {
                            if (isLineBreak(text[pos]))
                            {
                                break;
                            }
                            pos++;
                        }

                        commentDirectives = appendIfCommentDirective(
                            commentDirectives,
                            text.substring(tokenPos, pos),
                            commentDirectiveRegExSingleLine,
                            tokenPos);

                        if (_skipTrivia)
                        {
                            continue;
                        }
                        else
                        {
                            return token = SyntaxKind::SingleLineCommentTrivia;
                        }
                    }
                    // Multi-line comment
                    if (text[pos + 1] == CharacterCodes::asterisk)
                    {
                        pos += 2;
                        if (text[pos] == CharacterCodes::asterisk && text[pos + 1] != CharacterCodes::slash)
                        {
                            tokenFlags |= TokenFlags::PrecedingJSDocComment;
                        }

                        auto commentClosed = false;
                        auto lastLineStart = tokenPos;
                        while (pos < end)
                        {
                            auto ch = text[pos];

                            if (ch == CharacterCodes::asterisk && text[pos + 1] == CharacterCodes::slash)
                            {
                                pos += 2;
                                commentClosed = true;
                                break;
                            }

                            pos++;

                            if (isLineBreak(ch))
                            {
                                lastLineStart = pos;
                                tokenFlags |= TokenFlags::PrecedingLineBreak;
                            }
                        }

                        commentDirectives = appendIfCommentDirective(commentDirectives, text.substring(lastLineStart, pos), commentDirectiveRegExMultiLine, lastLineStart);

                        if (!commentClosed)
                        {
                            error(Diagnostics::Asterisk_Slash_expected);
                        }

                        if (_skipTrivia)
                        {
                            continue;
                        }
                        else
                        {
                            if (!commentClosed)
                            {
                                tokenFlags |= TokenFlags::Unterminated;
                            }
                            return token = SyntaxKind::MultiLineCommentTrivia;
                        }
                    }

                    if (text[pos + 1] == CharacterCodes::equals)
                    {
                        return pos += 2, token = SyntaxKind::SlashEqualsToken;
                    }

                    pos++;
                    return token = SyntaxKind::SlashToken;

                case CharacterCodes::_0:
                    if (pos + 2 < end && (text[pos + 1] == CharacterCodes::X || text[pos + 1] == CharacterCodes::x))
                    {
                        pos += 2;
                        tokenValue = scanMinimumNumberOfHexDigits(1, /*canHaveSeparators*/ true);
                        if (tokenValue.empty())
                        {
                            error(Diagnostics::Hexadecimal_digit_expected);
                            tokenValue = S("0");
                        }
                        tokenValue = S("0x") + tokenValue;
                        tokenFlags |= TokenFlags::HexSpecifier;
                        return token = checkBigIntSuffix();
                    }
                    else if (pos + 2 < end && (text[pos + 1] == CharacterCodes::B || text[pos + 1] == CharacterCodes::b))
                    {
                        pos += 2;
                        tokenValue = scanBinaryOrOctalDigits(/* base */ 2);
                        if (tokenValue.empty())
                        {
                            error(Diagnostics::Binary_digit_expected);
                            tokenValue = S("0");
                        }
                        tokenValue = S("0b") + tokenValue;
                        tokenFlags |= TokenFlags::BinarySpecifier;
                        return token = checkBigIntSuffix();
                    }
                    else if (pos + 2 < end && (text[pos + 1] == CharacterCodes::O || text[pos + 1] == CharacterCodes::o))
                    {
                        pos += 2;
                        tokenValue = scanBinaryOrOctalDigits(/* base */ 8);
                        if (tokenValue.empty())
                        {
                            error(Diagnostics::Octal_digit_expected);
                            tokenValue = S("0");
                        }
                        tokenValue = S("0o") + tokenValue;
                        tokenFlags |= TokenFlags::OctalSpecifier;
                        return token = checkBigIntSuffix();
                    }
                    // Try to parse as an octal
                    if (pos + 1 < end && isOctalDigit(text[pos + 1]))
                    {
                        tokenValue = to_string(scanOctalDigits());
                        tokenFlags |= TokenFlags::Octal;
                        return token = SyntaxKind::NumericLiteral;
                    }
                // This fall-through is a deviation from the EcmaScript grammar. The grammar says that a leading zero
                // can only be followed by an octal digit, a dot, or the end of the number literal. However, we are being
                // permissive and allowing decimal digits of the form 08* and 09* (which many browsers also do).
                // falls through
                case CharacterCodes::_1:
                case CharacterCodes::_2:
                case CharacterCodes::_3:
                case CharacterCodes::_4:
                case CharacterCodes::_5:
                case CharacterCodes::_6:
                case CharacterCodes::_7:
                case CharacterCodes::_8:
                case CharacterCodes::_9:
                {
                    auto res = scanNumber();
                    token = res.kind;
                    tokenValue = res.value;
                    return token;
                }
                case CharacterCodes::colon:
                    pos++;
                    return token = SyntaxKind::ColonToken;
                case CharacterCodes::semicolon:
                    pos++;
                    return token = SyntaxKind::SemicolonToken;
                case CharacterCodes::lessThan:
                    if (isConflictMarkerTrivia(text, pos))
                    {
                        pos = scanConflictMarkerTrivia(text, pos, std::bind(&ScannerImpl::error, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
                        if (_skipTrivia)
                        {
                            continue;
                        }
                        else
                        {
                            return token = SyntaxKind::ConflictMarkerTrivia;
                        }
                    }

                    if (text[pos + 1] == CharacterCodes::lessThan)
                    {
                        if (text[pos + 2] == CharacterCodes::equals)
                        {
                            return pos += 3, token = SyntaxKind::LessThanLessThanEqualsToken;
                        }
                        return pos += 2, token = SyntaxKind::LessThanLessThanToken;
                    }
                    if (text[pos + 1] == CharacterCodes::equals)
                    {
                        return pos += 2, token = SyntaxKind::LessThanEqualsToken;
                    }
                    if (languageVariant == LanguageVariant::JSX &&
                        text[pos + 1] == CharacterCodes::slash &&
                        text[pos + 2] != CharacterCodes::asterisk)
                    {
                        return pos += 2, token = SyntaxKind::LessThanSlashToken;
                    }
                    pos++;
                    return token = SyntaxKind::LessThanToken;
                case CharacterCodes::equals:
                    if (isConflictMarkerTrivia(text, pos))
                    {
                        pos = scanConflictMarkerTrivia(text, pos, std::bind(&ScannerImpl::error, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
                        if (_skipTrivia)
                        {
                            continue;
                        }
                        else
                        {
                            return token = SyntaxKind::ConflictMarkerTrivia;
                        }
                    }

                    if (text[pos + 1] == CharacterCodes::equals)
                    {
                        if (text[pos + 2] == CharacterCodes::equals)
                        {
                            return pos += 3, token = SyntaxKind::EqualsEqualsEqualsToken;
                        }
                        return pos += 2, token = SyntaxKind::EqualsEqualsToken;
                    }
                    if (text[pos + 1] == CharacterCodes::greaterThan)
                    {
                        return pos += 2, token = SyntaxKind::EqualsGreaterThanToken;
                    }
                    pos++;
                    return token = SyntaxKind::EqualsToken;
                case CharacterCodes::greaterThan:
                    if (isConflictMarkerTrivia(text, pos))
                    {
                        pos = scanConflictMarkerTrivia(text, pos, std::bind(&ScannerImpl::error, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
                        if (_skipTrivia)
                        {
                            continue;
                        }
                        else
                        {
                            return token = SyntaxKind::ConflictMarkerTrivia;
                        }
                    }

                    pos++;
                    return token = SyntaxKind::GreaterThanToken;
                case CharacterCodes::question:
                    if (text[pos + 1] == CharacterCodes::dot && !isDigit(text[pos + 2]))
                    {
                        return pos += 2, token = SyntaxKind::QuestionDotToken;
                    }
                    if (text[pos + 1] == CharacterCodes::question)
                    {
                        if (text[pos + 2] == CharacterCodes::equals)
                        {
                            return pos += 3, token = SyntaxKind::QuestionQuestionEqualsToken;
                        }
                        return pos += 2, token = SyntaxKind::QuestionQuestionToken;
                    }
                    pos++;
                    return token = SyntaxKind::QuestionToken;
                case CharacterCodes::openBracket:
                    pos++;
                    return token = SyntaxKind::OpenBracketToken;
                case CharacterCodes::closeBracket:
                    pos++;
                    return token = SyntaxKind::CloseBracketToken;
                case CharacterCodes::caret:
                    if (text[pos + 1] == CharacterCodes::equals)
                    {
                        return pos += 2, token = SyntaxKind::CaretEqualsToken;
                    }
                    pos++;
                    return token = SyntaxKind::CaretToken;
                case CharacterCodes::openBrace:
                    pos++;
                    return token = SyntaxKind::OpenBraceToken;
                case CharacterCodes::bar:
                    if (isConflictMarkerTrivia(text, pos))
                    {
                        pos = scanConflictMarkerTrivia(text, pos, std::bind(&ScannerImpl::error, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
                        if (_skipTrivia)
                        {
                            continue;
                        }
                        else
                        {
                            return token = SyntaxKind::ConflictMarkerTrivia;
                        }
                    }

                    if (text[pos + 1] == CharacterCodes::bar)
                    {
                        if (text[pos + 2] == CharacterCodes::equals)
                        {
                            return pos += 3, token = SyntaxKind::BarBarEqualsToken;
                        }
                        return pos += 2, token = SyntaxKind::BarBarToken;
                    }
                    if (text[pos + 1] == CharacterCodes::equals)
                    {
                        return pos += 2, token = SyntaxKind::BarEqualsToken;
                    }
                    pos++;
                    return token = SyntaxKind::BarToken;
                case CharacterCodes::closeBrace:
                    pos++;
                    return token = SyntaxKind::CloseBraceToken;
                case CharacterCodes::tilde:
                    pos++;
                    return token = SyntaxKind::TildeToken;
                case CharacterCodes::at:
                    pos++;
                    return token = SyntaxKind::AtToken;
                case CharacterCodes::backslash:
                {
                    auto extendedCookedChar = peekExtendedUnicodeEscape();
                    if (extendedCookedChar >= CharacterCodes::nullCharacter && isIdentifierStart(extendedCookedChar, languageVersion))
                    {
                        pos += 3;
                        tokenFlags |= TokenFlags::ExtendedUnicodeEscape;
                        tokenValue = scanExtendedUnicodeEscape() + scanIdentifierParts();
                        return token = getIdentifierToken();
                    }

                    auto cookedChar = peekUnicodeEscape();
                    if (cookedChar >= CharacterCodes::nullCharacter && isIdentifierStart(cookedChar, languageVersion))
                    {
                        pos += 6;
                        tokenFlags |= TokenFlags::UnicodeEscape;
                        tokenValue = string(1, (char_t)cookedChar) + scanIdentifierParts();
                        return token = getIdentifierToken();
                    }

                    error(Diagnostics::Invalid_character);
                    pos++;
                    return token = SyntaxKind::Unknown;
                }
                case CharacterCodes::hash:
                    if (pos != 0 && text[pos + 1] == CharacterCodes::exclamation)
                    {
                        error(Diagnostics::can_only_be_used_at_the_start_of_a_file);
                        pos++;
                        return token = SyntaxKind::Unknown;
                    }
                    pos++;
                    if (isIdentifierStart(ch = text[pos], languageVersion))
                    {
                        pos++;
                        while (pos < end && isIdentifierPart(ch = text[pos], languageVersion))
                            pos++;
                        tokenValue = text.substring(tokenPos, pos);
                        if (ch == CharacterCodes::backslash)
                        {
                            tokenValue += scanIdentifierParts();
                        }
                    }
                    else
                    {
                        tokenValue = S("#");
                        error(Diagnostics::Invalid_character);
                    }
                    return token = SyntaxKind::PrivateIdentifier;
                default:
                    auto identifierKind = scanIdentifier(ch, languageVersion);
                    if (!!identifierKind)
                    {
                        return token = identifierKind;
                    }
                    else if (isWhiteSpaceSingleLine(ch))
                    {
                        pos += charSize(ch);
                        continue;
                    }
                    else if (isLineBreak(ch))
                    {
                        tokenFlags |= TokenFlags::PrecedingLineBreak;
                        pos += charSize(ch);
                        continue;
                    }
                    error(Diagnostics::Invalid_character);
                    pos += charSize(ch);
                    return token = SyntaxKind::Unknown;
                }
            }
        }

    private:
        auto reScanInvalidIdentifier() -> SyntaxKind
        {
            debug(token == SyntaxKind::Unknown, S("'reScanInvalidIdentifier' should only be called when the current token is 'SyntaxKind::Unknown'."));
            pos = tokenPos = startPos;
            tokenFlags = TokenFlags::None;
            auto ch = codePointAt(text, pos);
            auto identifierKind = scanIdentifier(ch, ScriptTarget::ESNext);
            if (!!identifierKind)
            {
                return token = identifierKind;
            }
            pos += charSize(ch);
            return token; // Still `SyntaKind.Unknown`
        }

        auto scanIdentifier(CharacterCodes startCharacter, ScriptTarget languageVersion) -> SyntaxKind
        {
            auto ch = startCharacter;
            if (isIdentifierStart(ch, languageVersion))
            {
                pos += charSize(ch);
                while (pos < end && isIdentifierPart(ch = codePointAt(text, pos), languageVersion))
                    pos += charSize(ch);
                tokenValue = text.substring(tokenPos, pos);
                if (ch == CharacterCodes::backslash)
                {
                    tokenValue += scanIdentifierParts();
                }
                return getIdentifierToken();
            }

            return SyntaxKind::Unknown;
        }

        auto reScanGreaterToken() -> SyntaxKind
        {
            if (token == SyntaxKind::GreaterThanToken)
            {
                if (text[pos] == CharacterCodes::greaterThan)
                {
                    if (text[pos + 1] == CharacterCodes::greaterThan)
                    {
                        if (text[pos + 2] == CharacterCodes::equals)
                        {
                            return pos += 3, token = SyntaxKind::GreaterThanGreaterThanGreaterThanEqualsToken;
                        }
                        return pos += 2, token = SyntaxKind::GreaterThanGreaterThanGreaterThanToken;
                    }
                    if (text[pos + 1] == CharacterCodes::equals)
                    {
                        return pos += 2, token = SyntaxKind::GreaterThanGreaterThanEqualsToken;
                    }
                    pos++;
                    return token = SyntaxKind::GreaterThanGreaterThanToken;
                }
                if (text[pos] == CharacterCodes::equals)
                {
                    pos++;
                    return token = SyntaxKind::GreaterThanEqualsToken;
                }
            }
            return token;
        }

        auto reScanAsteriskEqualsToken() -> SyntaxKind
        {
            debug(token == SyntaxKind::AsteriskEqualsToken, S("'reScanAsteriskEqualsToken' should only be called on a '*='"));
            pos = tokenPos + 1;
            return token = SyntaxKind::EqualsToken;
        }

        auto reScanSlashToken() -> SyntaxKind
        {
            if (token == SyntaxKind::SlashToken || token == SyntaxKind::SlashEqualsToken)
            {
                auto p = tokenPos + 1;
                auto inEscape = false;
                auto inCharacterClass = false;
                while (true)
                {
                    // If we reach the end of a file, or hit a newline, then this is an unterminated
                    // regex.  Report error and return what we have so far.
                    if (p >= end)
                    {
                        tokenFlags |= TokenFlags::Unterminated;
                        error(Diagnostics::Unterminated_regular_expression_literal);
                        break;
                    }

                    auto ch = text[p];
                    if (isLineBreak(ch))
                    {
                        tokenFlags |= TokenFlags::Unterminated;
                        error(Diagnostics::Unterminated_regular_expression_literal);
                        break;
                    }

                    if (inEscape)
                    {
                        // Parsing an escape character;
                        // reset the flag and just advance to the next char.
                        inEscape = false;
                    }
                    else if (ch == CharacterCodes::slash && !inCharacterClass)
                    {
                        // A slash within a character class is permissible,
                        // but in general it signals the end of the regexp literal.
                        p++;
                        break;
                    }
                    else if (ch == CharacterCodes::openBracket)
                    {
                        inCharacterClass = true;
                    }
                    else if (ch == CharacterCodes::backslash)
                    {
                        inEscape = true;
                    }
                    else if (ch == CharacterCodes::closeBracket)
                    {
                        inCharacterClass = false;
                    }
                    p++;
                }

                while (p < end && isIdentifierPart(text[p], languageVersion))
                {
                    p++;
                }
                pos = p;
                tokenValue = text.substring(tokenPos, pos);
                token = SyntaxKind::RegularExpressionLiteral;
            }
            return token;
        }

        auto appendIfCommentDirective(
            std::vector<CommentDirective> commentDirectives,
            string text,
            regex commentDirectiveRegEx,
            number lineStart) -> std::vector<CommentDirective>
        {
            auto type = getDirectiveFromComment(text, commentDirectiveRegEx);
            if (type == CommentDirectiveType::Undefined)
            {
                return commentDirectives;
            }

            commentDirectives.push_back({
                {lineStart, pos},
                type
            });
            return commentDirectives;
        }

        auto getDirectiveFromComment(string &text, regex commentDirectiveRegEx) -> CommentDirectiveType
        {
            auto words_begin = sregex_iterator(text.begin(), text.end(), commentDirectiveRegEx);
            auto words_end = sregex_iterator();
            if (words_begin == words_end)
            {
                return CommentDirectiveType::Undefined;
            }

            for (auto i = words_begin; i != words_end; ++i)
            {
                auto match = *i;
                auto match_str = match.str();
                if (match_str == S("ts-expect-error"))
                    return CommentDirectiveType::ExpectError;

                return CommentDirectiveType::Ignore;
            }

            return CommentDirectiveType::Undefined;
        }

        /**
         * Unconditionally back up and scan a template expression portion.
         */
        auto reScanTemplateToken(boolean isTaggedTemplate) -> SyntaxKind
        {
            debug(token == SyntaxKind::CloseBraceToken, S("'reScanTemplateToken' should only be called on a '}'"));
            pos = tokenPos;
            return token = scanTemplateAndSetTokenValue(isTaggedTemplate);
        }

        auto reScanTemplateHeadOrNoSubstitutionTemplate() -> SyntaxKind
        {
            pos = tokenPos;
            return token = scanTemplateAndSetTokenValue(/* isTaggedTemplate */ true);
        }

        auto reScanJsxToken(boolean allowMultilineJsxText = true) -> SyntaxKind
        {
            pos = tokenPos = startPos;
            return token = scanJsxToken(allowMultilineJsxText);
        }

        auto reScanLessThanToken() -> SyntaxKind
        {
            if (token == SyntaxKind::LessThanLessThanToken)
            {
                pos = tokenPos + 1;
                return token = SyntaxKind::LessThanToken;
            }
            return token;
        }

        auto reScanQuestionToken() -> SyntaxKind
        {
            debug(token == SyntaxKind::QuestionQuestionToken, S("'reScanQuestionToken' should only be called on a '??'"));
            pos = tokenPos + 1;
            return token = SyntaxKind::QuestionToken;
        }

        auto scanJsxToken(boolean allowMultilineJsxText = true) -> SyntaxKind
        {
            startPos = tokenPos = pos;

            if (pos >= end)
            {
                return token = SyntaxKind::EndOfFileToken;
            }

            auto char_ = text[pos];
            if (char_ == CharacterCodes::lessThan)
            {
                if (text[pos + 1] == CharacterCodes::slash)
                {
                    pos += 2;
                    return token = SyntaxKind::LessThanSlashToken;
                }
                pos++;
                return token = SyntaxKind::LessThanToken;
            }

            if (char_ == CharacterCodes::openBrace)
            {
                pos++;
                return token = SyntaxKind::OpenBraceToken;
            }

            // First non-whitespace character on this line.
            auto firstNonWhitespace = 0;

            // These initial values are special because the first line is:
            // firstNonWhitespace = 0 to indicate that we want leading whitespace,

            while (pos < end)
            {
                char_ = text[pos];
                if (char_ == CharacterCodes::openBrace)
                {
                    break;
                }
                if (char_ == CharacterCodes::lessThan)
                {
                    if (isConflictMarkerTrivia(text, pos))
                    {
                        pos = scanConflictMarkerTrivia(text, pos, std::bind(&ScannerImpl::error, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
                        return token = SyntaxKind::ConflictMarkerTrivia;
                    }
                    break;
                }
                if (char_ == CharacterCodes::greaterThan)
                {
                    error(Diagnostics::Unexpected_token_Did_you_mean_or_gt, pos, 1);
                }
                if (char_ == CharacterCodes::closeBrace)
                {
                    error(Diagnostics::Unexpected_token_Did_you_mean_or_rbrace, pos, 1);
                }

                // FirstNonWhitespace is 0, then we only see whitespaces so far. If we see a linebreak, we want to ignore that whitespaces.
                // i.e (- : whitespace)
                //      <div>----
                //      </div> becomes <div></div>
                //
                //      <div>----</div> becomes <div>----</div>
                if (isLineBreak(char_) && firstNonWhitespace == 0)
                {
                    firstNonWhitespace = -1;
                }
                else if (!allowMultilineJsxText && isLineBreak(char_) && firstNonWhitespace > 0)
                {
                    // Stop JsxText on each line during formatting. This allows the formatter to
                    // indent each line correctly.
                    break;
                }
                else if (!isWhiteSpaceLike(char_))
                {
                    firstNonWhitespace = pos;
                }

                pos++;
            }

            tokenValue = text.substring(startPos, pos);

            return firstNonWhitespace == -1 ? SyntaxKind::JsxTextAllWhiteSpaces : SyntaxKind::JsxText;
        }

        // Scans a JSX identifier; these differ from normal identifiers in that
        // they allow dashes
        auto scanJsxIdentifier() -> SyntaxKind
        {
            if (tokenIsIdentifierOrKeyword(token))
            {
                // An identifier or keyword has already been parsed - check for a `-` or a single instance of `:` and then append it and
                // everything after it to the token
                // Do note that this means that `scanJsxIdentifier` effectively _mutates_ the visible token without advancing to a new token
                // Any caller should be expecting this behavior and should only read the pos or token value after calling it.
                auto namespaceSeparator = false;
                while (pos < end)
                {
                    auto ch = text[pos];
                    if (ch == CharacterCodes::minus)
                    {
                        tokenValue += S("-");
                        pos++;
                        continue;
                    }
                    else if (ch == CharacterCodes::colon && !namespaceSeparator)
                    {
                        tokenValue += S(":");
                        pos++;
                        namespaceSeparator = true;
                        continue;
                    }
                    auto oldPos = pos;
                    tokenValue += scanIdentifierParts(); // reuse `scanIdentifierParts` so unicode escapes are handled
                    if (pos == oldPos)
                    {
                        break;
                    }
                }
                // Do not include a trailing namespace separator in the token, since this is against the spec.
                if (tokenValue.substr(-1) == S(":"))
                {
                    tokenValue = tokenValue.substr(0, -1);
                    pos--;
                }
            }
            return token;
        }

        auto scanJsxAttributeValue() -> SyntaxKind
        {
            startPos = pos;

            switch (text[pos])
            {
            case CharacterCodes::doubleQuote:
            case CharacterCodes::singleQuote:
                tokenValue = scanString(/*jsxAttributeString*/ true);
                return token = SyntaxKind::StringLiteral;
            default:
                // If this scans anything other than `{`, it's a parse error.
                return scan();
            }
        }

        auto reScanJsxAttributeValue() -> SyntaxKind
        {
            pos = tokenPos = startPos;
            return scanJsxAttributeValue();
        }

        auto scanJsDocToken() -> SyntaxKind
        {
            startPos = tokenPos = pos;
            tokenFlags = TokenFlags::None;
            if (pos >= end)
            {
                return token = SyntaxKind::EndOfFileToken;
            }

            auto ch = codePointAt(text, pos);
            pos += charSize(ch);
            switch (ch)
            {
            case CharacterCodes::tab:
            case CharacterCodes::verticalTab:
            case CharacterCodes::formFeed:
            case CharacterCodes::space:
                while (pos < end && isWhiteSpaceSingleLine(text[pos]))
                {
                    pos++;
                }
                return token = SyntaxKind::WhitespaceTrivia;
            case CharacterCodes::at:
                return token = SyntaxKind::AtToken;
            case CharacterCodes::carriageReturn:
                if (text[pos] == CharacterCodes::lineFeed)
                {
                    pos++;
                }
                // falls through
            case CharacterCodes::lineFeed:
                tokenFlags |= TokenFlags::PrecedingLineBreak;
                return token = SyntaxKind::NewLineTrivia;
            case CharacterCodes::asterisk:
                return token = SyntaxKind::AsteriskToken;
            case CharacterCodes::openBrace:
                return token = SyntaxKind::OpenBraceToken;
            case CharacterCodes::closeBrace:
                return token = SyntaxKind::CloseBraceToken;
            case CharacterCodes::openBracket:
                return token = SyntaxKind::OpenBracketToken;
            case CharacterCodes::closeBracket:
                return token = SyntaxKind::CloseBracketToken;
            case CharacterCodes::lessThan:
                return token = SyntaxKind::LessThanToken;
            case CharacterCodes::greaterThan:
                return token = SyntaxKind::GreaterThanToken;
            case CharacterCodes::equals:
                return token = SyntaxKind::EqualsToken;
            case CharacterCodes::comma:
                return token = SyntaxKind::CommaToken;
            case CharacterCodes::dot:
                return token = SyntaxKind::DotToken;
            case CharacterCodes::backtick:
                return token = SyntaxKind::BacktickToken;
            case CharacterCodes::backslash:
                pos--;
                auto extendedCookedChar = peekExtendedUnicodeEscape();
                if (extendedCookedChar >= CharacterCodes::nullCharacter && isIdentifierStart(extendedCookedChar, languageVersion))
                {
                    pos += 3;
                    tokenFlags |= TokenFlags::ExtendedUnicodeEscape;
                    tokenValue = scanExtendedUnicodeEscape() + scanIdentifierParts();
                    return token = getIdentifierToken();
                }

                auto cookedChar = peekUnicodeEscape();
                if (cookedChar >= CharacterCodes::nullCharacter && isIdentifierStart(cookedChar, languageVersion))
                {
                    pos += 6;
                    tokenFlags |= TokenFlags::UnicodeEscape;
                    tokenValue = string(1, (char_t)cookedChar) + scanIdentifierParts();
                    return token = getIdentifierToken();
                }
                pos++;
                return token = SyntaxKind::Unknown;
            }

            if (isIdentifierStart(ch, languageVersion))
            {
                auto char_ = ch;
                while (pos < end && isIdentifierPart(char_ = codePointAt(text, pos), languageVersion) || text[pos] == CharacterCodes::minus)
                    pos += charSize(char_);
                tokenValue = text.substring(tokenPos, pos);
                if (char_ == CharacterCodes::backslash)
                {
                    tokenValue += scanIdentifierParts();
                }
                return token = getIdentifierToken();
            }
            else
            {
                return token = SyntaxKind::Unknown;
            }
        }

        template <typename T>
        auto speculationHelper(std::function<T()> callback, boolean isLookahead) -> T
        {
            auto savePos = pos;
            auto saveStartPos = startPos;
            auto saveTokenPos = tokenPos;
            auto saveToken = token;
            auto saveTokenValue = tokenValue;
            auto saveTokenFlags = tokenFlags;
            auto result = callback();

            // If our callback returned something 'falsy' or we're just looking ahead,
            // then unconditionally restore us to where we were.
            if (!result || isLookahead)
            {
                pos = savePos;
                startPos = saveStartPos;
                tokenPos = saveTokenPos;
                token = saveToken;
                tokenValue = saveTokenValue;
                tokenFlags = saveTokenFlags;
            }
            return result;
        }

        template <typename T>
        auto scanRange(number start, number length, std::function<T()> callback) -> T
        {
            auto saveEnd = end;
            auto savePos = pos;
            auto saveStartPos = startPos;
            auto saveTokenPos = tokenPos;
            auto saveToken = token;
            auto saveTokenValue = tokenValue;
            auto saveTokenFlags = tokenFlags;
            auto saveErrorExpectations = commentDirectives;

            setText(text, start, length);
            auto result = callback();

            end = saveEnd;
            pos = savePos;
            startPos = saveStartPos;
            tokenPos = saveTokenPos;
            token = saveToken;
            tokenValue = saveTokenValue;
            tokenFlags = saveTokenFlags;
            commentDirectives = saveErrorExpectations;

            return result;
        }

        template <typename T>
        auto lookAhead(std::function<T()> callback) -> T
        {
            return speculationHelper(callback, /*isLookahead*/ true);
        }

        template <typename T>
        auto tryScan(std::function<T()> callback) -> T
        {
            return speculationHelper(callback, /*isLookahead*/ false);
        }

        auto getText() -> string
        {
            return text;
        }

public:
        auto getCommentDirectives() -> std::vector<CommentDirective>
        {
            return commentDirectives;
        }

        auto clearCommentDirectives()
        {
            commentDirectives.clear();
        }

        auto setText(string newText, number start, number length) -> void
        {
            text = newText;
            end = length == -1 ? text.length() : start + length;
            setTextPos(start);
        }

        auto setOnError(ErrorCallback errorCallback)
        {
            onError = errorCallback;
        }

        auto setScriptTarget(ScriptTarget scriptTarget)
        {
            languageVersion = scriptTarget;
        }

        auto setLanguageVariant(LanguageVariant variant)
        {
            languageVariant = variant;
        }

        auto setTextPos(number textPos) -> void
        {
            debug(textPos >= 0);
            pos = textPos;
            startPos = textPos;
            tokenPos = textPos;
            token = SyntaxKind::Unknown;
            tokenValue = string();
            tokenFlags = TokenFlags::None;
        }

private:
        auto setInJSDocType(boolean inType)
        {
            inJSDocType += inType ? 1 : -1;
        }

        /* @internal */
        auto codePointAt(safe_string &str, number i) -> CharacterCodes
        {
            // from https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/codePointAt
            auto size = str.length();
            // Account for out-of-bounds indices:
            if (i < 0 || i >= size)
            {
                return CharacterCodes::outOfBoundary; // String.codePointAt returns `-1` for OOB indexes
            }
            // Get the first code unit
            auto first = str[i];
            // check if it’s the start of a surrogate pair
            if (first >= CharacterCodes::_startOfSurrogate && first <= CharacterCodes::_endOfSurrogate && size > i + 1)
            { // high surrogate and there is a next code unit
                auto second = str[i + 1];
                if (second >= CharacterCodes::_startOfSurrogateLow && second <= CharacterCodes::_endOfSurrogateLow)
                { // low surrogate
                    // https://mathiasbynens.be/notes/javascript-encoding#surrogate-formulae
                    return (CharacterCodes) (((number)first - (number)CharacterCodes::_startOfSurrogate) * 0x400 + (number)second - (number)CharacterCodes::_startOfSurrogateLow + (number)CharacterCodes::_2bytes);
                }
            }
            return first;
        };

        /* @internal */
        auto charSize(CharacterCodes ch) -> number
        {
            return (ch >= CharacterCodes::_2bytes) ? 2 : 1;
        }

        // Derived from the 10.1.1 UTF16Encoding of the ES6 Spec.
        auto utf16EncodeAsStringFallback(number codePoint) -> string
        {
            debug(0x0 <= codePoint && codePoint <= 0x10FFFF);

            // TODO: review code
            /*
            if (codePoint <= 65535)
            {
                return string(1, (char_t)codePoint);
            }

            auto codeUnit1 = (number)((codePoint - 65536) / 1024) + 0xD800;
            auto codeUnit2 = ((codePoint - 65536) % 1024) + 0xDC00;

            // unit code
            return string({codeUnit1, codeUnit2});
            */

           return string(1, (char_t)codePoint);
        }

        /* @internal */
        auto utf16EncodeAsString(CharacterCodes codePoint) -> string
        {
            return utf16EncodeAsStringFallback((number)codePoint);
        }
    };

    Scanner::Scanner(ScriptTarget languageVersion,
                                boolean skipTrivia,
                                LanguageVariant languageVariant,
                                string textInitial,
                                ErrorCallback onError,
                                number start,
                                number length)
    {
        impl = ScannerImpl::createScanner(languageVersion, skipTrivia, languageVariant, textInitial, onError, start, length);        
    }

    auto Scanner::setText(string text, number start, number length) -> void
    {
        return impl->setText(text, start, length);
    }

    auto Scanner::setOnError(ErrorCallback errorCallback) -> void
    {
        impl->setOnError(errorCallback);
    }

    auto Scanner::setScriptTarget(ScriptTarget scriptTarget) -> void
    {
        impl->setScriptTarget(scriptTarget);
    }

    auto Scanner::setLanguageVariant(LanguageVariant variant) -> void
    {
        impl->setLanguageVariant(variant);
    }    

    auto Scanner::scan() -> SyntaxKind
    {
        return impl->scan();
    }

    auto Scanner::tokenToString(SyntaxKind t) -> string
    {
        return impl->tokenToString(t);
    }    

    auto Scanner::syntaxKindString(SyntaxKind t) -> string
    {
        return impl->syntaxKindString(t);
    }    

    auto Scanner::getToken() -> SyntaxKind
    {
        return impl->token;
    }      

    auto Scanner::getStartPos() -> number
    {
        return impl->startPos;
    }  

    auto Scanner::getTokenPos() -> number
    {
        return impl->tokenPos;
    }  
    
    auto Scanner::getTokenText() -> string
    {
        return impl->text.substring(impl->tokenPos, impl->pos);
    } 

    auto Scanner::getTokenValue() -> string
    {
        return impl->tokenValue;
    }     

    auto Scanner::getCommentDirectives() -> std::vector<CommentDirective>
    {
        return impl->getCommentDirectives();
    }

    auto Scanner::setTextPos(number textPos) -> void
    {
        impl->setTextPos(textPos);
    }    

    auto Scanner::clearCommentDirectives() -> void
    {
        impl->clearCommentDirectives();
    }

    auto Scanner::hasUnicodeEscape() -> boolean
    {
        return (impl->tokenFlags & TokenFlags::hasUnicodeEscape) != 0;
    }

    auto Scanner::hasExtendedUnicodeEscape() -> boolean
    {
        return (impl->tokenFlags & TokenFlags::hasExtendedUnicodeEscape) != 0;
    }

    auto Scanner::hasPrecedingLineBreak() -> boolean
    {
        return (impl->tokenFlags & TokenFlags::hasPrecedingLineBreak) != 0;
    }

    auto Scanner::hasPrecedingJSDocComment() -> boolean
    {
        return (impl->tokenFlags & TokenFlags::PrecedingJSDocComment) != 0;
    }

    Scanner::~Scanner()
    {
        delete impl;
    }    
}
