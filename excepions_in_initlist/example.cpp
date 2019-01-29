#include <cstdio>
#include <memory>


struct Malicious
{
    Malicious(int x)
    {
        if (x < 0) {
            throw std::runtime_error("negative");
        }

        this->x = x;
    }

private:
    int x;
};

class Safe
{    
private:
    std::unique_ptr<Malicious> mm;

public:
    Safe(int x) try: mm { std::make_unique<Malicious>(x) } {
        printf("Constructed with %d.\n", x);
    } catch(std::runtime_error const& err) {
        printf("Constructing failed because of: %s!\n", err.what());
    } // rethrow occurs here
};

int main()
{
    Safe xx(5);
    try {
        Safe yy(-1);
    } catch (...) { }
}
