/*
 * Memory usage can be broadly simplified into two values, Virtual Memory (VMEM)
 * which a program believes it has and Resident Set Size (RSS) which is the
 * actual amount of memory it uses. In order to make better use of physical memory,
 * the operating system doesn't actually give a program the memory it requests
 * until the program uses it. This means multiple applications can request memory
 * and until they actually use it they won't affect the available RAM. Once data
 * is written to the memory it is actually in use and part of the RSS - the size
 * of the memory set that is resident in RAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

/* Get vmem and rss usage from /proc/<pid>/statm */
static int mem_used(pid_t pid, unsigned long* vmem, unsigned long* rss) {
    FILE* file;
    char path[40];
    unsigned int page_size;

    snprintf(path, 40, "/proc/%ld/statm", (long) pid);
    file = fopen(path, "r");
    // vmem and rss are the first values in the file
    fscanf(file, "%lu %lu", vmem, rss);
    // values in statm are in pages so to get bytes we need to know page size
    page_size = (unsigned) getpagesize();
    *vmem = *vmem * page_size;
    *rss = *rss * page_size;

    fclose(file);
    return 0;
}

int main(int argc, char **argv) {
    unsigned char *address;
    char input;
    size_t size = 1024*1024*1024;  // 1 GiB
    unsigned long i;
    unsigned long vmem = 0;
    unsigned long rss = 0;
    pid_t pid;

    pid = getpid();
    printf("Pid: %ld\n", (long) pid);

    mem_used(pid, &vmem, &rss);
    printf("VMEM: %lu RSS: %lu\n", vmem, rss);

    address = malloc(size);
    printf("Allocated %d Bytes of memory\n", (int) size);

    mem_used(pid, &vmem, &rss);
    printf("VMEM: %lu RSS: %lu\n", vmem, rss);

    printf("Press any key to continue");
    scanf("%c", &input);

    printf("Filling memory with data...");
    fflush(stdout);  // Flush output so message appears before end of loop
    for (i = 0; i < size; i++) {
        *(address + i) = 123;
    }

    mem_used(pid, &vmem, &rss);
    printf("\nVMEM: %lu RSS: %lu\n", vmem, rss);

    printf("Press any key to continue");
    scanf("%c", &input);

    free(address);
    return 0;
}
