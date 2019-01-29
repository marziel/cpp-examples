#include <cstdio>
#include <stdexcept>


enum class Colours {
    _begin,
    Red = _begin, Green, Blue, Black, Magenta,
    _end
};

Colours& operator++(Colours& kk)
{
    if (kk == Colours::_end) {
        throw std::out_of_range("Colours incrementation oout of range");
    }

    auto underlyingIncremented = static_cast<std::underlying_type_t<Colours>>(kk) + 1;
    kk = static_cast<Colours>(underlyingIncremented);
    return kk;
}

int main()
{
    for (auto kk = Colours::_begin; kk != Colours::_end; ++kk) {
        printf("%d\n", static_cast<int>(kk));
    }
}
