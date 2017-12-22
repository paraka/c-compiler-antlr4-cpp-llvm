#include <iostream>
#include "def_symbols.h"

void DefSymbols::save_scope(ParserRuleContext *ctx, Scope *s)
{
    scopes_.put(ctx, s);
}

void DefSymbols::define_variable(CParser::TypeSpecifierContext *type_ctx, Token *name)
{
    std::cout << "define_variable: " << type_ctx->getText() << " " << name->getText() << std::endl;
}

void DefSymbols::enterCompilationUnit(CParser::CompilationUnitContext *ctx)
{
    current_scope_ = &globals_;
}

void DefSymbols::exitCompilationUnit(CParser::CompilationUnitContext *ctx)
{
    current_scope_ = current_scope_->get_enclosing_scope();
}

void DefSymbols::enterFunctionDefinition(CParser::FunctionDefinitionContext *ctx)
{
    Function *func = SymbolTableFactory::create_symbol<Function>("foo", current_scope_);
    current_scope_->define(func);
    save_scope(ctx, func);
    current_scope_ = func;
}

void DefSymbols::exitFunctionDefinition(CParser::FunctionDefinitionContext *ctx)
{
    current_scope_ = current_scope_->get_enclosing_scope();
}

void DefSymbols::enterDeclaration(CParser::DeclarationContext *ctx)
{
    std::cout << "enterDeclaration: " << ctx->getText() << std::endl;
    auto f = ctx->getRuleContexts<CParser::DeclarationSpecifiersContext>();
    auto t = f[0]->getRuleContexts<CParser::DeclarationSpecifierContext>();
    auto type = t[0]->getRuleContexts<CParser::TypeSpecifierContext>();
    for (auto &t1 : type)
    {
        std::cout << "Type: " << t1->getText() << std::endl;
        /* TODO: Where is type + Identofier in the same rule ??? */
        define_variable(t1, ctx->getStart());
    }
}

void DefSymbols::enterDeclarationSpecifier(CParser::DeclarationSpecifierContext *ctx)
{
    std::cout << "enterDeclarationSpecifier: " << ctx->getText() << std::endl;
}

void DefSymbols::enterDirectDeclarator(CParser::DirectDeclaratorContext *ctx)
{
    std::cout << "enterDirectDeclarator: " << ctx->getText() << std::endl;
}

void DefSymbols::enterBlockItem(CParser::BlockItemContext *ctx)
{
//    std::cout << "enterBlockItem: " << ctx->getText() << std::endl;
}

void DefSymbols::exitBlockItem(CParser::BlockItemContext *ctx)
{
//    std::cout << "exitBlockItem: " << ctx->getText() << std::endl;
}
