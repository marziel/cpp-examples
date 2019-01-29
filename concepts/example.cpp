#include <cstdio>
#include <utility>


template <typename T, typename ... Args>
concept bool IntPrintable = requires(T xx, Args&& ... args) {
    { xx.print(std::forward<Args>(args) ...) } -> int
};

struct Abc
{
    int print() const
    {
        return printf("Wow\n");
    }
};

struct Fgh
{
    void print() const
    {
        printf("Halo\n");
    }
};

struct Jkl
{
    int print(const char *description, size_t times)
    {
        printf("%s:\n", description);
        for (size_t ii = 0; ii < times; ++ii) {
            printf("\tYupi\n");
        }

        return static_cast<int>(times);
    }  
};

void output(const IntPrintable& itp)
{
    itp.print();
}

int main()
{
    Abc abc;
    output(abc);

    Jkl jkl;
    jkl.print("What's going on", 5);
}
