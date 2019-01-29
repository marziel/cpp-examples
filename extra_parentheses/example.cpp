#include <cstdio>
#include <typeinfo>
#include <cxxabi.h>


namespace whatever {
    struct Xx { };
    void ff(Xx) { printf("Hello!\n\n"); }
    void hh(int);
}

struct Example
{
    Example(int) { }
    double rr;
};

void gg()
{
    whatever::Xx xx;
    ff(xx);
    // would be a compile error: the parentheses turn off the ADL (Argument-dependent lookup)
    // (ff)(xx);
}

struct Tracer
{
    static size_t global_id;
    size_t id;

    Tracer() { this->id = global_id++; info("ctor"); }
    ~Tracer() { info("dtor"); }
    Tracer(Tracer const&) { info("copy ctor"); }
    Tracer& operator=(Tracer const&) { info("copy assign"); return *this; }
    Tracer(Tracer&&) = delete;
    Tracer& operator=(Tracer&&) = delete;

private:
    void info(char const *fn)
    {
        printf("%s, id = %zu\n", fn, this->id);
    }
};
size_t Tracer::global_id;

decltype(auto) qq1()
{
    Tracer tr;
    return(tr);
}

decltype(auto) qq2()
{
    Tracer tr;
    return tr;
}

void ii(double kk)
{
    Example a(int(kk));
    Example b(int());
    Example c((int)kk);
    Example d = int(kk);

    int status;
    printf("typeid of 'a': %s\n", abi::__cxa_demangle(typeid(a).name(), nullptr, nullptr, &status));
    printf("typeid of 'b': %s\n", abi::__cxa_demangle(typeid(b).name(), nullptr, nullptr, &status));
    printf("typeid of 'c': %s\n", abi::__cxa_demangle(typeid(c).name(), nullptr, nullptr, &status));
    printf("typeid of 'd': %s\n", abi::__cxa_demangle(typeid(d).name(), nullptr, nullptr, &status));

    Example* yy = new Example(4);
    decltype(yy->rr) e = 8.0;
    decltype((yy->rr)) f = e;   // reference!
    printf("'e' before changing 'f': %f\n", e);
    f = 9.1;
    printf("'e' after changing 'f': %f\n", e);
    delete yy;
}

int main()
{
    gg();
    ii(5.0);
    
    auto ay = qq2();
    printf("^______ if this is the only ctor triggered by the function qq2(), then the NRVO occured:\n\n"
    "\tIn a return statement, when the operand is the name of\n"
    "\ta non-volatile object with automatic storage duration, which\n"
    "\tisn't a function parameter or a catch clause parameter, and which\n"
    "\tis of the same class type (ignoring cv-qualification) as the\n"
    "\tfunction return type. This variant of copy elision is known as\n"
    "\tNRVO, \"named return value optimization\".\t[cppreference.com]\n\n");
    
    printf("\n----- NOW ABOUT TO RETURN REFERENCE TO LOCAL OBJECT -----\n");
    auto az = qq1();
}
