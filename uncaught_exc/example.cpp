#include <iostream>
#include <exception>
#include <stdexcept>

 
struct Something
{
    static size_t global_id;
    size_t id;
    int count = std::uncaught_exceptions();

    Something()
    {
        this->id = global_id++;
    }
    
    ~Something()
    {
        std::cout << (count == std::uncaught_exceptions()
            ? "~Something() called normally"
            : "~Something() called during stack unwinding");
        std::cout << ", object id = " << this->id << std::endl;
    }
};
size_t Something::global_id;

int main()
{
    Something f;
    try {
        Something f;
        std::cout << "Exception throwing...\n";
        throw std::runtime_error("test exception");
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << '\n';
    }
}
