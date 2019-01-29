#include <cstdio>


[[gnu::naked]] int check_sgx_support()
{
    asm("\n\
            push rbx        \n\
            push rcx        \n\
            mov rax, 7      \n\
            xor rcx, rcx    \n\
            cpuid           \n\
            and rbx, 0x02   \n\
            shr rbx, 1      \n\
            mov rax, rbx    \n\
            pop rcx         \n\
            pop rbx         \n\
            ret             \n\
    ");
}

int main()
{
    printf("SGX supported?\t\t - %s\n", (check_sgx_support()) ? "YES" : "NO");
    return 0;
}
