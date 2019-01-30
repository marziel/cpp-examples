#include <cstdio>


/*  by not including 'OdrViol.hpp' the type is 
    redefined and violates the One-Definition Rule
    - this is already an undefined behaviour */
struct OdrViol
{
    char a;
    short b;
};

/*  external - no definition here but will link with 
    that provided by 'OdrViol.cpp' */
OdrViol do_something();

int main()
{
    /*  the undefined behaviour is triggered here - the 
        function from 'OdrViol.cpp' is called but it 
        expects to work on the 'OdrViol' type defined 
        there, not here */
    auto ov = do_something();
    printf("%c\n", ov.a);
}
