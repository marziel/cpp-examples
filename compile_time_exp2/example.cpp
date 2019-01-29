#include <cstdio>

#include <algorithm>
#include <array>


size_t constexpr absMaxExp = 20;

template <size_t I>
auto constexpr powerOf2()
{
    std::array<size_t, I> powers { };
    for (size_t ii = 0; ii < I; ++ii) {
        powers[ii] = 1 << ii;
    }

    return powers;
}

int main()
{
    printf("Max. exponent:\n\t");
    size_t maxExp;
    scanf("%zu", &maxExp);

    auto yy = powerOf2<absMaxExp>();
    for (auto const& pp: yy) {
        printf("%zu\n", pp);
    }
}
