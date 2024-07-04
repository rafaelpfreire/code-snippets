// https://en.cppreference.com/w/cpp/atomic/atomic
// https://en.cppreference.com/w/cpp/atomic/memory_order
// https://gcc.gnu.org/wiki/Atomic/GCCMM/AtomicSync

#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
 
std::atomic_int acnt;
int cnt;
 
void f()
{
    for (int n = 0; n < 10000; ++n)
    {
        ++acnt;
        ++cnt;
        // Note: for this example, relaxed memory order
        // is sufficient, e.g. acnt.fetch_add(1, std::memory_order_relaxed);
    }
}
 
int main()
{
    {
        std::vector<std::jthread> pool;
        for (int n = 0; n < 10; ++n)
            pool.emplace_back(f);
    }
 
    std::cout << "The atomic counter is " << acnt << '\n'
              << "The non-atomic counter is " << cnt << '\n';
}
\* Possible output:
The atomic counter is 100000
The non-atomic counter is 69696 *\
