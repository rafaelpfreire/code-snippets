#include <algorithm>
#include <chrono>
#include <cstdint>
#include <execution>
#include <iostream>
#include <random>
#include <vector>
 
void measure(auto policy, std::vector<std::uint64_t> v)
{
    const auto start = std::chrono::steady_clock::now();
    std::sort(policy, v.begin(), v.end());
    const auto finish = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count()
              << '\n';
};
 
int main()
{
    std::vector<std::uint64_t> v(700000);
    std::mt19937 gen{ std::random_device{}() };
    std::ranges::generate(v, gen);
 
    // May not be parallelized neither vectorized
    measure(std::execution::seq, v);
 
    // May be vectorized
    measure(std::execution::unseq, v);
 
    // May be parallelized, vectorized or migrated across threads
    measure(std::execution::par_unseq, v);
 
    // May be parallelized
    measure(std::execution::par, v);
}
