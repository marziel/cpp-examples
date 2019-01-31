#include <type_traits>
#include <cstdio>


template <typename From, typename To>
concept bool NotConvertible = !std::is_convertible_v<std::decay<From> *, To *>;
struct Good
{
    Good() = default;
    Good(Good const&) { printf("Ok.\n"); }
    
    template <typename T, typename U> requires NotConvertible<T, Good>
    Good(T&&) { printf("This won't be called - no surprise.\n"); }
};

struct Better
{
    Better() = default;
    Better(Better const&) { printf("Ok.\n"); }
    
    template <typename T, typename std::enable_if_t<!std::is_convertible_v<std::decay<T> *, Better *>>>
    Better(T&&) { printf("This won't be called - no surprise.\n"); }  
};

struct Bad
{
    Bad() = default;
    Bad(Bad const&) { printf("Ok.\n"); }
    
    /*  This overload takes a forwarding reference (which 
        can be a usual reference) and it's less 'cv-qualified' 
        ('cv' means const and/or volatile) than the copy 
        constructor above so it will be called! */
    template <typename T>
    Bad(T&&) { printf("Surprise!\n"); }
};

int main()
{
    Good aa;
    Good bb(aa);
    
    Better cc;
    Better dd(cc);
    
    Bad ee;
    Bad ff(ee);
}
