#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

#define N_REPEATS   1000
#define ARRAY_SIZE  1024 * 512

// This program shows the difference in performance when
// using aligned and unligned data

// Check cache performance with
// perf stat -e LLC-misses,LLC-loads ./program

static inline double tstamp(void) {
    struct timespec tv;
    clock_gettime(CLOCK_REALTIME, &tv);
    return tv.tv_sec + tv.tv_nsec * 1.0e-9;
}

void initialize_up(int* array, int n) {
    for (int i = 0; i < n; ++i) {
        array[i] = i;
    }
}

void initialize_random(int* array, int n) {
    int aux = 0;
    int idx = 0;

    initialize_up(array, n);

    for (int i = 0; i < n; ++i) {
        idx = rand() % n;
        aux = array[i];
        array[i] = array[idx];
        array[idx] = aux;
    }
}

int main() {
    int indexes[ARRAY_SIZE];
    int data[ARRAY_SIZE];

    initialize_up(data, ARRAY_SIZE);
    initialize_up(indexes, ARRAY_SIZE);
    //initialize_random(indexes, ARRAY_SIZE);

    double start = tstamp();
    unsigned sum = 0;
    for (unsigned int rep = 0; rep < N_REPEATS; ++rep) {
        for (int i = 0; i != ARRAY_SIZE; ++i) {
            int index = indexes[i];
            assert(index >= 0 && index < ARRAY_SIZE);
            sum += (unsigned) data[index];
        }
    }

    unsigned long lsize = ARRAY_SIZE;
    assert(sum == (unsigned) ((lsize * (lsize - 1)) / 2) * N_REPEATS);
    printf("OK in %.06f sec!\n", tstamp() - start);

    return 0;
}
