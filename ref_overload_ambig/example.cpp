#include <type_traits>
#include <cstdio>


template <typename From, typename To>
concept bool NotConvertible = !std::is_convertible_v<std::decay_t<From> *, To *>;
struct Best
{
    Best() = default;
    Best(Best const&) { printf("%s:\n\tOk.\n", __PRETTY_FUNCTION__); }
    
    template <typename T> requires NotConvertible<T, Best>
    Best(T&&) { printf("%s:\n\tCalled on demand - no surprise.\n", __PRETTY_FUNCTION__); }
};

struct Good
{
    Good() = default;
    Good(Good const&) { printf("%s:\n\tOk.\n", __PRETTY_FUNCTION__); }
    
    template <typename T, typename = std::enable_if_t<!std::is_convertible_v<std::decay_t<T> *, Good *>>>
    Good(T&&) { printf("%s:\n\tCalled on demand - no surprise.\n", __PRETTY_FUNCTION__); }
};

struct Bad
{
    Bad() = default;
    Bad(Bad const&) { printf("%s:\n\tOk.\n", __PRETTY_FUNCTION__); }
    
    /*  This overload takes a forwarding reference (which 
        can be a usual reference) and it's less 'cv-qualified' 
        ('cv' means const and/or volatile) than the copy 
        constructor above so it will be called! */
    template <typename T>
    Bad(T&&) { printf("%s:\n\tSurprise!\n", __PRETTY_FUNCTION__); }
};

int main()
{
    int zz = 5;

    Best aa;
    Best bb(aa);
    Best qq(zz);
    
    Good cc;
    Good dd(cc);
    Good ee(zz);
    
    Bad ff;
    Bad gg(ff);
}
