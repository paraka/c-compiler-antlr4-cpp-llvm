#ifndef COMPILER_H
#define COMPILER_H

class Compiler
{
public:
    explicit Compiler(const std::string &file);
    ~Compiler() = default;
    Compiler() = delete;
    Compiler(const Compiler &) = delete;
    Compiler(Compiler &&) = delete;
    Compiler &operator=(const Compiler &) = delete;
    bool compile(void);

private:
    const std::string file_;
};

#endif // COMPILER_H
