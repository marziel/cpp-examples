#include <cstdio>

#include <stdexcept>
#include <type_traits>
#include <vector>


struct out_of_service: public std::runtime_error
{
    out_of_service():
        std::runtime_error { "something's wrong" } { }
};

template <typename ... Args>
inline void errPr(Args ... args)
{
    fprintf(stderr, args ...);
}

void printCurrentException()
{
    auto prExc = [] <typename E> (E const& ex) {
        auto exTypeToStr = [] () -> char const * {
            if constexpr (std::is_same_v<E, std::exception>) {
                return "Generic";
            } else if (std::is_same_v<E, std::runtime_error>) {
                return "Runtime";
            } else {
                return "Specialised";
            }
        };
    
        fprintf(stderr, "%s error:\n\t%s\n", exTypeToStr(), ex.what());
    };

    try {
        throw;
    } catch (out_of_service const& ex) {
        prExc(ex);
    } catch (std::runtime_error const& ex) {
        prExc(ex);
    } catch (std::exception const& ex) {
        prExc(ex);
    }
}

void printCurrentExceptionWithNested()
{
    try {
        throw;
    } catch (...) {
        printCurrentException();
    }

    try {
        throw;
    } catch (std::nested_exception const& nestEx) {
        try {
            nestEx.rethrow_nested();
        } catch (...) {
            printCurrentExceptionWithNested();
        }
    } catch (...) { /* end recursion */ }
}

int suspicious(std::vector<int> const& vec)
{
    try {
        return vec.at(1);
    } catch (std::out_of_range const& ex) {
        std::throw_with_nested(out_of_service { });
    }
}

void run()
{
    std::vector<int> vec;
    try {
        suspicious(vec);
    } catch (...) {
        std::throw_with_nested(std::runtime_error("unable to run()"));
    }
}

int main()
{
    try {
        run();
    } catch (...) {
        printCurrentExceptionWithNested();
    }
}
