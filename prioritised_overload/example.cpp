#include <stdexcept>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <ctime>


// simple struct pretending to be car diagnostic system record
struct test_flags
{
    bool fault = false;
    uint8_t number_of_errors = 0;
    char error_causes[UINT8_MAX][50] { };
};


namespace detail {

// picker: inherits one after another, higher- after lower-numbered
template <size_t N>
struct pick: pick<N-1> { };
template <>
struct pick<0> { };
constexpr size_t MAX_PICK = UINT8_MAX;

// first choice
template <typename Tester>
auto self_test(Tester& t, test_flags& tf, pick<2>)
    /*  - this checks if 't.thorough_test(tf)' is well-formed but the comma operator 
          discards this expression so decltype results in type of 'void()', so the
          resulting type is just void 
        - this by its nature enables use of kind of type erasure: it doesn't matter 
          what the function returns - we still can have uniform interface */
    -> decltype(t.thorough_test(tf), void())
{
    t.thorough_test(tf);
}

// second choice
template <typename Tester>
auto self_test(Tester& t, test_flags& tf, pick<1>)
    -> decltype(t.standard_test(tf), void())
{
    t.standard_test(tf);
}

// fallback choice
template <typename Tester>
auto self_test(Tester& t, test_flags& tf, pick<0>)
    -> decltype(t.brief_test(tf), void())
{
    t.brief_test(tf);
}

} // namespace detail

/* chooser: tries to instantiate with high number so that compiler goes 
   down inheritance hierarchy and chooses first met (top-numbered) 
   existing picker type */
template <typename Tester>
auto self_test(Tester& t, test_flags& tf)
{
    detail::self_test(t, tf, detail::pick<detail::MAX_PICK> { });
}

struct brief_tester
{
    virtual bool brief_test(test_flags&) = 0;
};

struct standard_tester
{
    virtual uint8_t standard_test(test_flags&) = 0;
};

struct thorough_tester
{
    virtual uint8_t thorough_test(test_flags&) = 0;
};


struct TyreCheck: brief_tester
{
    bool brief_test(test_flags& tf) final
    {
        auto fault = rand() & 0x01;
        tf.number_of_errors += fault;
        tf.fault |= !!fault;
        return fault;
    }
};

struct BulbsCheck: standard_tester
{
    uint8_t standard_test(test_flags& tf) final
    {
        auto bulb_errors = static_cast<uint8_t>(rand() % 8);
        tf.number_of_errors += bulb_errors;
        tf.fault |= (tf.number_of_errors > 0);
        return bulb_errors;
    }
};

struct EngineCheck: thorough_tester
{
    uint8_t thorough_test(test_flags& tf) final
    {
        char const error_causes[2][50] {
            "air filter polluted",
            "injector circuit open"
        };

        uint8_t total_engine_errors = 0;
        for (size_t ii = 0; ii < sizeof(error_causes) / sizeof(error_causes[0]); ++ii) {
            auto engine_error = static_cast<uint8_t>(rand() & 0x01);
            if (!!!engine_error) {
                continue;
            }

            ++total_engine_errors;
            strcpy(tf.error_causes[ii], error_causes[ii]);
        }

        tf.fault |= !!total_engine_errors;
        tf.number_of_errors += total_engine_errors;
        return total_engine_errors;
    }
};


int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    test_flags flags;
    TyreCheck tc;
    BulbsCheck bc;
    EngineCheck ec;

    self_test(tc, flags);
    self_test(bc, flags);
    self_test(ec, flags);

    printf("Fault present: %s\n", (flags.fault) ? "YES" : "NO");
    if (!flags.fault) {
        return 0;
    }

    printf("\tTotal number of errors: %hhu\n", flags.number_of_errors);
    bool detail_info_print = false;
    for (size_t ii = 0; ii < sizeof(flags.error_causes) / sizeof(flags.error_causes[0]); ++ii) {
        if (flags.error_causes[ii][0] == '\0') {
            continue;
        }

        if (!detail_info_print) {
            detail_info_print = true;
            printf("\t\t...including engine errors:\n");
        }
        printf("\t\t\tcode: %03zu because of: '%s'\n", ii, flags.error_causes[ii]);
    }
    printf("\n");
}
