#include <algorithm>
#include <utility>

#include <cstdio>


template <typename ... Args>
void info(const char *fn_name, Args&& ... args)
{
    printf("%s: ", fn_name);
    printf(std::forward<Args>(args) ...);
    printf("\n");
}

struct Something
{
    void go() { printf("doing, doing\n"); }
};

struct Idiom: public Something
{
    Idiom() { info(__func__, "constructor"); }
    
    ~Idiom() { info(__func__, "destructor"); }

    Idiom(Idiom const&)
    {
        info(__func__, "copy constructor");
    }

    Idiom& operator=(Idiom other)
    {
        info(__func__, "copy/move assignment");
    
        swap(*this, other);
        return *this;
    }

    Idiom(Idiom&&) noexcept
    {
        info(__func__, "move constructor");
    }

    /* Providing own swap() function is necessary 
       due to infinite recurrence caused by std::swap() 
       which uses some function(s) implemented above, 
       i.e. probably the equality operator or/and the 
       move constructor. */
    friend void swap(Idiom&, Idiom&) noexcept { }
};

int main()
{
    Idiom bb;
    Idiom cc;
    cc = std::move(bb);
    Idiom dd = cc;
    Idiom ee;
    ee = dd;
}
