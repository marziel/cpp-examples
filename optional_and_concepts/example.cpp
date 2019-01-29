#include <iostream>

#include <optional>
#include <type_traits>


template <typename T>
concept bool Integral = std::is_integral_v<T>;

std::optional<Integral> safeDiv(Integral x, Integral y)
{
    if (y != 0) {
        return x / y;
    }

    return { };
}

template <Integral X, Integral Y>
std::optional<X> safeDivGeneric(X x, Y y)
{
    if (y != 0) {
        return x / y;
    }

    return { };
}

template <typename T>
inline void printDiv(std::optional<T> const& oo)
{
    if (oo) {
        std::cout << *oo;
    } else {
        std::cout << "nothing";
    }
    
    std::cout << std::endl;
}

int main()
{
    auto aa = safeDiv(5, 0);
    printDiv(aa);
    
    auto bb = safeDiv(5, 1);
    printDiv(bb);
    
    // won't compile - OK, prevented by concepts
        //auto cc = safeDiv(4.0, 2.0);
        
    // won't compile - OK, no such function (two distinct types):
        //auto dd = safeDiv(4, 2.0);
        
    // won't compile - OK, no such function (two distinct types):
        // auto ee = safeDiv(4, 2U);
        
    auto ff = safeDiv(4U, 2U);
    printDiv(ff);
    
    auto gg = safeDivGeneric(6, 2U);
    printDiv(gg);
}
