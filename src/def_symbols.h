#ifndef DEF_SYMBOLS_H_
#define DEF_SYMBOLS_H_

#include <antlr4-runtime.h>
#include <CBaseListener.h>
#include "symbol_table.h"

using namespace antlr4;
using namespace antlr4::tree;
using namespace antlrcpptest;

class DefSymbols : public CBaseListener
{
public:
    DefSymbols() : globals_(nullptr), current_scope_(nullptr) {}
    ~DefSymbols() = default;

    /* override stuff to walk the tree */
    void enterCompilationUnit(CParser::CompilationUnitContext *ctx) override;
    void exitCompilationUnit(CParser::CompilationUnitContext *ctx) override;
    void enterFunctionDefinition(CParser::FunctionDefinitionContext *ctx) override;
    void enterDeclaration(CParser::DeclarationContext *ctx) override;
    void enterDeclarationSpecifier(CParser::DeclarationSpecifierContext *ctx) override;
    void enterDirectDeclarator(CParser::DirectDeclaratorContext *ctx) override;
    void exitFunctionDefinition(CParser::FunctionDefinitionContext *ctx) override;
    void enterBlockItem(CParser::BlockItemContext *ctx) override;
    void exitBlockItem(CParser::BlockItemContext *ctx) override;

private:
    void save_scope(ParserRuleContext *ctx, Scope *s);
    void define_variable(CParser::TypeSpecifierContext *type_ctx, Token *name);

private:
    BasicScope globals_;
    Scope *current_scope_;
    ParseTreeProperty<Scope *> scopes_;
};

#endif // DEF_SYMBOLS_H_
