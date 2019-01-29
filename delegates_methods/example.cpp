#include <functional>
#include <iostream>
#include <type_traits>
using namespace std::placeholders;


template <typename Result, typename Object>
struct wrapper
{
public:
    wrapper(void *const fptr, Object obj):
        optr { reinterpret_cast<void *>(&obj) },
        fptr { fptr } { }

    template <typename ... Args>
    Result operator()(Args ... args)
    {
        using Fptr = Result (*)(Object *, Args ...);
        auto realFn = reinterpret_cast<Fptr>(this->fptr);
        auto realObj = reinterpret_cast<Object *>(this->optr);
        return realFn(realObj, args ...);
    }
        
private:
    void *optr;
    void *fptr;
};

struct Multiplier
{
    float mult(float factor) const noexcept
    {
        return factor * this->aa;
    }

private:
    float aa = 1.2f;
};

int main()
{
    Multiplier abc;
    auto fn = std::bind(&Multiplier::mult, &abc, _1);
    printf("%f\n", fn(3.0));
}
