#include <cstdint>
#include <cstdio>
#include <type_traits>


enum class Half {
    Lower, Upper
};

template <typename T>
struct Lesser: std::false_type { };

template <>
struct Lesser<uint64_t>
{
    using _t = uint32_t;  
};

template <>
struct Lesser<uint32_t>
{
    using _t = uint16_t;  
};

template <>
struct Lesser<uint16_t>
{
    using _t = uint8_t;  
};

template <typename Integer>
typename Lesser<Integer>::_t half(Integer xx, Half which)
{
    using half_t = typename Lesser<Integer>::_t;
    constexpr size_t bits_per_half = 8 * sizeof(half_t);

    auto lower_positive_mask = [] () {
        auto tmp_mask = static_cast<half_t>(-1);
        return static_cast<Integer>(tmp_mask);
    };

    if (which == Half::Lower) {
        return static_cast<half_t>(xx & lower_positive_mask());
    }

    auto upper_positive_mask = ~lower_positive_mask();
    auto half_with_leading_zeroes = (xx & upper_positive_mask) >> bits_per_half;
    return static_cast<half_t>(half_with_leading_zeroes);
}

/* A line: 

        asm(".intel_syntax noprefix");
    
   switches the ASM syntax to Intel's version until reverted by:

        asm(".att_syntax prefix");
*/

/* Another operand types:

        https://gcc.gnu.org/onlinedocs/gcc-8.2.0/gcc/Simple-Constraints.html

   including 'g' which allows the compiler to automatically choose operands to 
   use from: registers, memory or immediates (constants) but not from 
   general-purpose registers.
*/

int main()
{
    uint64_t a = 10;
    uint64_t b = 0;
    printf("Before:\ta = %lu, b = %lu\n", a ,b);
    asm (   "mov rax, %1    \n\
             mov %0, rax"           // input and output operands are numbered together starting with 0
             :"=r" (b)              /*  equality sign: ASM snippet ignores the initial value of a clobbered 
                                        variable; this opens an opportunity for optimisation
                                    */
             :"r" (a)
             :"rax"                /*
                                        clobber list:
                                            - doesn't have to contain a register if the register holds an output
                                              argument
                                            - if labelled with the word "memory", the snippet won't be moved by 
                                              the compiler; nevertheless it can still be entirely cut out by 
                                              optimisation (phrase "asm volative" at the beginning of the snippet
                                              can be use to prevent this)
                                    */
    );
    printf("After:\ta = %lu, b = %lu\n", a, b);

    uint32_t backup_edx = 0;
    asm (   "mov %[bck], edx"           /*  label instead of numbering; lables have their own namespace so their 
                                            names won't conflict with variables/functions etc. */
            :[bck] "=r" (backup_edx)
    );
    printf("EDX has value (unsigned): %u\n", backup_edx);

    printf("\nEnter upper half of a number (decimal): ");
    uint32_t lower, upper;
    scanf("%u", &upper);
    printf("Enter lower half of the number (decimal): ");
    scanf("%u", &lower);
    uint64_t packed = (static_cast<uint64_t>(upper) << 32) | lower;
    uint64_t absolute = 0;
    asm (   "movq mm1, %[packed]    \n\
             pabsd mm0, mm1         \n\
             movq %[absolute], mm0"         /*  PABSD: computes the absolute values of two halves of a 64-bit number 
                                                treating the halves as independent numbers */
                 :[absolute] "=r" (absolute)
                 :[packed] "r" (packed)
    );
    printf("\tAbsolute values:\n\t\tupper half\t%u\n\t\tlower half\t%u\n", 
        half(absolute, Half::Upper), half(absolute, Half::Lower));

    uint32_t rax_avatar = 0;
    asm (   "mov rax, 0     \n\
             mov %[rax_avatar], 130"
                :[rax_avatar] "=a" (rax_avatar)     /*  "=a" takes the variable to EAX; here the return value simulates 
                                                        raising a SIGINT */
    );
    return rax_avatar;
}
