#include <array>
#include <initializer_list>
#include <iostream>
#include <utility>


template <typename T, T ... I>
void print_sequence(std::integer_sequence<T, I ...>)
{
    std::initializer_list<bool> {
        static_cast<bool>(std::cout << I << ' ') ... };
    std::cout << std::endl;
}

template <int Offset, typename T, T ... I>
void print_offset_sequence(std::integer_sequence<T, I ...>)
{
    print_sequence(std::integer_sequence<T, (I + Offset) ...>());
}

template <typename T, size_t ... I>
std::array<T, sizeof ...(I)> make_array(T const& value, std::index_sequence<I ...>)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-value"
    return std::array<T, sizeof ...(I)> { (I, value) ... };
#pragma GCC diagnostic pop
}

template <int N, typename T>
std::array<T, N> make_array(T const &value)
{
    return make_array(value, std::make_index_sequence<N>());
}

int main()
{
    print_sequence(std::integer_sequence<int, 1, 2, 3>());
    print_sequence(std::integer_sequence<char, 'h', 'e', 'l', 'l', 'o'>());

    print_sequence(std::make_index_sequence<10>());
    print_sequence(std::make_integer_sequence<short, 10>());
    print_offset_sequence<'A'>(std::make_integer_sequence<char, 26>());

    auto abc = make_array<20>(std::string("yo"));
    for (auto const& ix: abc) {
        std::cout << ix << ' ';
    }
    std::cout << std::endl;
}
