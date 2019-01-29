#include <iostream>
#include <type_traits>
#include <typeinfo>


template <typename ... Ts>
void printAll(std::ostream& os, Ts const& ... args)
{
    ((os << args << ' '), ...);
}

template <typename T1, typename T2>
std::common_type_t<T1 const&, T2 const&> min(T1 const& a, T2 const& b)
{
    return (a < b) ? a : b;
}

template <typename T1, typename T2, typename ... Args>
std::common_type_t<T1 const&, T2 const&, Args const& ...> min(T1 const& a, T2 const& b, Args const& ... args)
{
    return min(min(a, b), args ...);
}

int main()
{
    auto xx = min(1.4, 1.2f, 4, 'a');
    std::cout << xx << std::endl;
    std::cout << typeid(decltype(xx)).name() << std::endl;
    printAll(std::cout, 1, 2, 3, 4);
    std::cout << std::endl;
}
