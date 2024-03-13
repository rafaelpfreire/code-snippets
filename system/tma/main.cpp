#include <random>

extern "C" { void foo(char* a, int n); }

const int _200MB = 1024*1024*200;

int main() {
    char* a = (char*)malloc(_200MB); // 200 MB buffer
    for (int i = 0; i < _200MB; i++) {
        a[i] = 0;
    }

    const int min = 0;
    const int max = _200MB;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(min, max - 1);

    // Random indexing a big buffer would give us a lot of
    // L3 cache misses. Prefetching would fix the problem.
    // Also foo() was developed in ASM in order to avoid
    // compiler optimizations.
    for (int i = 0; i < 100000000; i++) {
         int random_int = distribution(generator);
        //__builtin_prefetch ( a + random_int, 0, 1);
        foo(a, random_int);
    }

    free(a);
    return 0;
}
