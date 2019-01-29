// based on StackOverflow.com
#include <iostream>


template <auto *F>
struct Wrapper { };

template <typename Ret, typename ... Args, Ret (*F)(Args ...)>
struct Wrapper<F>
{
    auto operator()(Args ... args) const
    {
        return F(args ...);
    }
};

float whatever(std::string const& str, int times)
{
    while (times--) {
        std::cout << str << std::endl;
    }

    return 4.5f;
}

int main()
{
    std::string str("bla, bla");
    Wrapper<whatever> repeater;
    std::cout << repeater(str, 5) << std::endl;
}
