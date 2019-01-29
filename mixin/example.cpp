#include <cstdio>
#include <functional>
#include <stdexcept>
#include <string>
#include <type_traits>


template <typename T>
struct Message
{
    explicit Message(const T& msg):
        _msg { msg } { }

    T& content() { return _msg; }

private:
    T _msg;  
};

template <typename Element, typename T>
struct Iterable: public T
{
    using T::T;

    void forEach(std::function<void(Element&)> fn)
    {
        for (auto& xx: this->content()) {
            fn(xx);
        }
    }
};

template <typename T>
struct Printable: public T
{
    using T::T;

    void print()
    {
        this->forEach([] (auto& xx) {
            printf("%c", xx);
        });
        printf("\n");
    }
};

template <typename T>
struct Cryptable: public T
{
    using T::T;

    void crypt(uint8_t key)
    {
        if (key == 0) {
            throw std::runtime_error("key must not be zero");
        }

        this->forEach([key] (auto& xx) {
            using xx_t = std::decay_t<decltype(xx)>;
            xx ^= static_cast<xx_t>(key);
        });
    }
};

int main()
{
    Printable<Cryptable<Iterable<char, Message<std::string>>>> msg("Stanley has got a cat");
    printf("Plain message: ");
    msg.print();

    constexpr uint8_t key = 0x0A;
    msg.crypt(key);
    printf("Encrypted message: ");
    msg.print();

    msg.crypt(key);
    printf("Decrypted back: ");
    msg.print();
}
