#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <stdio.h>

/* Solution 0
 * Uses O_SYNC flag in order to synchronize each write command to the device
 * This is the same as calling fsynch() after each write.
 */

/* Solution 1
 * Removing the O_SYNC flag the program request asynchronous writes and relies
 * on the operating system to wite the data to the disk when it's convenient
 * (but after your write call has returned)
 */

/* Solution 2
 * This solution doesn't rely on expensive system calls in order to do the job.
 * Instead it uses function calls that are implemented in the c standard library
 * which keep their own cache in memory without involving the operating system.
 */

#define SOLUTION  2

static inline double tstamp(void) {
    struct timespec tv;
    clock_gettime(CLOCK_REALTIME, &tv);
    return tv.tv_sec + tv.tv_nsec * 1.0e-9;
}

static inline void report(size_t n, double elapsed) {
    fprintf(stderr, "\r\e[33m\e[7m%zd bytes   %.3f sec   %g byte/sec     ",
            n, elapsed, n / elapsed);
}

int64_t my_open(const char *pathname, mode_t mode) {
#if(SOLUTION == 0)
    return open(pathname, O_WRONLY | O_CREAT | O_TRUNC | O_SYNC, mode);
#elif(SOLUTION == 1)
    return open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);
#else
    return (int64_t)(intptr_t) fopen(pathname, "w+");
#endif
}

ssize_t my_write(int64_t fd, const void *buf, size_t count) {
#if((SOLUTION == 0) || (SOLUTION == 1))
    return write(fd, buf, count);
#else
    return fwrite(buf, 1, count, (FILE*)(intptr_t) fd);
#endif
}

int my_close(int64_t fd) {
#if((SOLUTION == 0) || (SOLUTION == 1))
    return close(fd);
#else
    return fclose((FILE*)(intptr_t)fd);
#endif
}

int main() {
    int64_t fd = my_open("data", 0666);

    if (fd < 0) {
        perror("open");
        exit(1);
    }

    // writes the characer '6' to the file
    size_t size = 5120000;
    const char* buf = "6";
    double start = tstamp();
    double t0 = start;
    double t1 = start;

    size_t n = 0;
    while (n < size) {
        ssize_t r = my_write(fd, buf, 1);
        if (r != 1) {
            perror("write");
            exit(1);
        }

        // with some frequency (defined in iobench.h), prints out
        // how long it takes to complete the write.
        n += r;
        t1 = tstamp();
        if ((t1 - t0) > 0.25) {
            t0 = tstamp();
            report(n, tstamp() - start);
        }
    }

    my_close(fd);
    report(n, tstamp() - start);
    fprintf(stderr, "\n");
    return 0;
}
