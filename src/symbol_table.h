#ifndef SYMBOL_TABLE_H_
#define SYMBOL_TABLE_H_

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

/*
 * TODO: use real type from antlr
 *  and remove this. 
 */
enum class Type
{
    FUNCTION,
    VARIABLE,
    PARAMETER,
};

struct Symbol
{
    std::string name;
    Type type;

    Symbol(const std::string &name, Type type) : name(name), type(type) {}
    
    virtual ~Symbol() = default;
};

struct Variable : public Symbol
{
    explicit Variable(const std::string &name) : Symbol(name, Type::VARIABLE) {}

    ~Variable() = default;
};

struct Parameter : public Symbol
{
    explicit Parameter(const std::string &name, 
              bool by_reference = false) 
               : Symbol(name, Type::PARAMETER), by_reference(by_reference) {}

    ~Parameter() = default;

    bool by_reference;
};

class Scope
{
public:
    explicit Scope(Scope *s) : enclosing_scope(s) {}

    virtual ~Scope() = default;

    virtual std::string get_scope_name(void) = 0;

    void define(Symbol *s)
    {
        symbols.insert(std::pair<std::string, Symbol *>(s->name, s));
    }

    Symbol *resolve(const std::string &name)
    {
        Symbol *sym = symbols[name];

        if (sym != nullptr) 
            return sym;

        if (get_enclosing_scope() != nullptr)
        {
            auto f = get_enclosing_scope();
            return f->resolve(name);
        }

        return nullptr;
    }

    Scope *get_enclosing_scope(void)
    {
        return enclosing_scope;
    }

protected:
    Scope *enclosing_scope;
    using SymbolsMap = std::unordered_map<std::string, Symbol *>;
    SymbolsMap symbols;
};

class BasicScope : public Scope
{
public:
    explicit BasicScope(Scope *s) : Scope(s) {}

    ~BasicScope() = default;
        
    std::string get_scope_name(void) override
    {
        return std::string("unknown");
    }
};

class Function : public Symbol, public Scope
{
public:
    Function(const std::string name, Scope *s): Symbol(name, Type::FUNCTION), Scope(s) {}

    ~Function() = default;
    
    std::string get_scope_name(void) override
    {
        return name; 
    }
};

/* create symbol table objects with this factory */
namespace SymbolTableFactory
{
    template <typename T, typename... Args> 
    T *create_symbol(Args && ... args)
    {
        return new T(std::forward<Args>(args)...);
    }
}

#endif // SYMBOL_TABLE_H_
