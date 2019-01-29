#include <cstdint>
#include <cstdio>


struct A { };
struct B { int x = 1; };
struct C: A, B { int y = 2; double z = 3.3; };

int main()
{
    // 1: empty, but must be 1 byte big (smallest possible) to differentiate objects of this type e.g. in an array
    printf("sizeof(A): 0x%x\n", sizeof(A));

    double C::*p1 = &C::z;
    // notice that the line below is legit!
    double A::*p2 = static_cast<double A::*>(p1);
    // ...as well as this one
    double A::*p3 = static_cast<double A::*>(&C::z);

    // 8: empty base optimisation of A, then 4 bytes of and int from B and 4 bytes of an int in C
    printf("\np1: 0x%x\n", p1);
    // 8: pointer equal to p1
    printf("p2: 0x%x\n", p2);
    // 8: pointer equal to p1 and p2
    printf("p3: 0x%x\n", p3);

    // 0
    printf("\noffset of x in B: 0x%x\n", &B::x);
    // 0: empty base optimisation of A
    printf("offset of x in C: 0x%x\n", &C::x);
    // 4: empty base optimisation of A, then 4 bytes of and int from B
    printf("offset of y in C: 0x%x\n", &C::y);
    // 8 (as explained above for pointers)
    printf("offset of z in C: 0x%x\n", &C::z);
}
