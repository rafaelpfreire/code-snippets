# Core Dump

A “core dump” is a snapshot of memory at the instant the program crashed, typically saved in a file called “core”.

The core contains the memory contents of the process at the point of the seg-fault including its 
- code segment, 
- data segment, 
- stack segment and 
- heap segment

## Uses of Core Dump Files

- Core dumps allow a user to save a crash for later or off-site analysis, or comparison with other crashes.
- For embedded computers, it may be impractical to support debugging on the computer itself, so analysis of a dump may take place on a different computer.

## Resource Limits

Every process has various limits associated with it.

```bash
$ man setrlimit
```

Bash offers a built-in ulimit through which we can edit these. Core-file max-size (ulimit -c/RLIMIT_CORE) controls the maximum core file size that can be generated when the process snaps.

```bash
$ ulimit -c unlimited
```
## What do do with a core file

The core is dumped in the current working directory of the process. Core files can be examined with gdb, the GNU debugger. It can read the crash informations, and display (among other things) the backtrace that leads to the crash.

```bash
$ gdb /path/to/binary /path/to/core/file
```
After gdb finished to read the input and shows its prompt, execute:

```bash
(gdb) backtrace
```

or 

```bash
(gdb) bt
```

GDB will then output the backtrace.

## Configuring Apport Service (Ubuntu)

Apport is the crash managing service in Ubuntu systems. First of all, make sure the service is running:

```bash
$ sudo systemctl status apport.service
```

Create a config file for your programs

```bash
mkdir -p ~/.config/apport
printf '[main]
unpackaged=true
' >> ~/.config/apport/settings
```

Check Apport logs to get info about your core dump files. Ususally core dump files are located inside `/var/lib/apport/coredump/`

```bash
cat /var/log/apport.log
```

## Dumping core from outside the program

One possibility is with gdb, if available. This will let the program running:

```bash
(gdb) attach <pid>
(gdb) generate-core-file <optional-filename>
(gdb) detach
```

Another possibility is to signal the process. This will terminate it, assuming the signal is not caught by a custom signal handler:

```bash
kill -s SIGABRT <pid>
```

## Dumping core from within the program

```bash
void dump_core_and_terminate(void)
{
    /*
     * Alternative:
     *   char *p = NULL; *p = 0;
     */
    abort();
}
```

## Common Memory Issues in C Programming

* Incorrect memory accesses  
	- Using uninitialized variables 
	- Out-of-bounds memory accesses (read/write underflow/overflow bugs)
	- Use-after-free/use-after-return (out-of-scope) bugs 
	- Double-free
* Leakage
* Undefined Behavior
* Data Races

To get warning for this issue

```bash
$ gcc 1.c -o 1 -Wall
```

### Out of bonds Memory Access

- Write overflow: A bug where a write is attempted into a memory buffer after its last legally accessible location 
- Write underflow: A write is attempted into a memory buffer before its first legally accessible location
- Read underflow: A read is attempted on a memory buffer before its first legally accessible location 
- Read overflow: A read is attempted on a memory buffer after its last legally accessible location

### free keyword

The free utility displays in kilobytes
- the current (approximate) amount of memory used
- free, and
- available  on the system as whole

It further divides the used memory between shared buffer/page-cached. It also displays swap partition statistics.

```bash
$ free
#             total       used       free     shared    buffers     cached
#Mem:       7088788    2477848    4610940      13892     686348     746876
#-/+ buffers/cache:    1044624    6044164
#Swap:            0          0          0

$ free | grep "^Mem"
#Mem:       7088788    2477740    4611048      13892     686428     746880
```

This displays only the Mem line

We see the two scenarios executing; check out the values of the free column. We allocate, and leak, a tiny amount of memory (32 bytes) but in a loop 100,000 times: 

```bash
#	Leaked memory = 297708 - 293120 = 4588 KB ~= 4.5 MB 
```

We allocate, and leak, a large amount of memory (1 MB) in a loop 12 times: 
```bash
#	Leaked memory = 292616 - 280992 = 11624 KB ~= 11.4 MB 
```

Of course, do realize that once the process dies, all its memory is freed back to the system. That's why we performed the one-liner script within the process, while it was alive.


## About Valgrind:

1. Debugging Tool
2. It is a wrapper around various tools for debugging and profiling. Best tool out of these is MemCheck that is used to find out memory leaks etc.

In order to use valgrind you have to include debugging information that is you should compile the application with -g option if you are using gcc .

```bash
$ gcc -o 1 1.c -g

$ valgrind --tool=memcheck --leak-check=yes  ./1
```
## Pros

Catches common memory bugs (UB) on dynamically allocated memory regions
- Using Uninitialized Variables
- Out-of-bounds memory access(read/write underflow/overflow bugs)
- Use-after-free/use after return(out of scope) bugs
- Double free
- Leakage

## Cons

Performance: target software may run up to 10 to 30 times slower when run under Valgrind.

Memory footprint: each allocation within the target program requires Valgrind to make a memory allocation as well (making running Valgrind on highly-resource-constrained embedded Linux systems difficult).

In order to see the call stack with line-number information, a recompile/build with the -g flag is required.
