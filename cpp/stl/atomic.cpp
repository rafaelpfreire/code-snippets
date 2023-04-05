#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
 
std::atomic<uint64_t> acnt;
volatile uint64_t vcnt;
uint64_t cnt;
 
void f()
{
    for (int n = 0; n < 10000; ++n)
    {
        ++acnt;
        ++vcnt;
        ++cnt;
        // Note: for this example, relaxed memory order
        // is sufficient, e.g. acnt.fetch_add(1, std::memory_order_relaxed);
    }
}
 
int main()
{

    std::vector<std::thread> pool;
    for (int n = 0; n < 10; ++n) {
        pool.emplace_back(f);
    }

    for (auto& t : pool) {
        t.join();
    }
 
    std::cout << "The atomic counter is " << acnt << '\n'
              << "The volatile counter is " << vcnt << '\n'
              << "The non-atomic counter is " << cnt << '\n';
}
