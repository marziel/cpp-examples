#include <array>
#include <atomic>
#include <mutex>
#include <thread>

#include <cstdio>


static std::once_flag done;
static std::atomic_size_t counter;

void work()
{
    std::call_once(done, [] () {
       printf("Halo!\n\n"); 
    });

    printf("%zu\n", counter++);
}

int main()
{
    std::array<std::thread, 10> pool { };

    for (auto& th: pool) {
        th = std::thread(work);
    }

    for (auto& th: pool) {
        th.join();
    }
}
