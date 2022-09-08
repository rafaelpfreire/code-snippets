#What is strace

strace stands for system call tracer

It is a debugging tool that 
- monitors the system calls used by a program and 
- all the signals it receives.

System calls are used by userspace applications when they need to do something that requires the kernel. 

#What it does

----> Learn which system calls a program make

----> Find those system calls that fail together with error code

----> Find which files a program opens

----> Find out what syscalls a running program is making, for example to see if it is struck in a loop

Using strace is quite simple. There are two ways to let strace monitor a program.

#Method 1

```bash
$ strace program_name
```

Ex: $ strace ls

```bash
$strace pwd
```

Reading strace output:

Each line in the output represents a system call. They follow the format: 

`system_call(argument1, argument2, ... ) = return_value`

Errors (typically a return value of -1) have the errno symbol and error string appended.

```bash
#open("/foo/bar", O_RDONLY) = -1 ENOENT (No such file or directory)
```

strace emits its entire output to stderr

#Method 2

If we want to monitor a process which is currently running we can attach to the process using –p option

```bash
$ strace –p <pid-of-the-application>

$ dd if=/dev/zero of=/dev/null bs=1 count=500k
$ strace dd if=/dev/zero of=/dev/null bs=1 count=500k
```

#When Is strace Useful?

strace is very useful while debugging crashes.  Some scenarios where strace can be helpful are –

----> When you don't have source code

----> program behaving poorly

----> nothing in the log files

----> nothing in stdout

----> no ports responding

----> don't want to open gdb

----> Debugging why an installation crashes on a machine.

----> Debugging random crashes that are most probably due to the program running out of memory or due to it requesting an arbitrarily large chunk of memory.

----> Finding out how the program interacts with the file system.

----> Debugging crashes reproducibly only on one machine.

----> Debugging crashes in unfamilar code or in cases when sources are unavailable.

strace may provide you with valuable information for many problem cases, for
example: which config files really were read, which was the last file or shared library read before your
program crashed, and so on
                                     
#What are all these calls between execve() and write()?

They take care of connecting all of the standard C libraries before the main program starts. 

They basically set up the runtime. If you look at them carefully you’ll see that they walk through a series of possible files, check to see if they are accessible, open them, map them into a memory location, and close them.

#Redirecting the output to a file 

Viewing data in the terminal is one thing, but sometimes we need to record the data to an file so we can analyze it later.

Using -o option we can redirect the complex output of strace into a file.

```bash
$ strace -o <output-file-name> <program-name>

$ strace -o empty-trace ./1
$ strace -o print-trace ./2
$ vimdiff empty-trace print-trace
```

#Generate statistics for System Calls

Sometimes, we only want to look at which system calls were made by the program and how many system calls of same type were made. 

These statistics can be used to identify the most commonly used system calls by the program. 

Using –c option strace provides summary information on executing a program. 

It provides information like 
- number of times a system call is used, 
- time spent executing various system calls, 
- number of times errors returned as shown below.

```bash
$ strace -c <command>
```

'-C' - prints the regular output + stats

```bash
$ strace -C <command>
```

#Time spent per system call 

Sometimes, it is important to understand which system call is taking how much time

This knowledge can be used to identify the bottlenecks in the application

Using –T option we can get time spent per system call.

-Ttt returns time spent per each system call as well as microsecond precision

```bash
$ strace -T pwd

$ strace -Ttt pwd
```

#Child Processes

Sometimes the process you trace doesn't do the real work itself, but delegates it to child processes that it creates.

If that's the case, you may want to pass -f to make strace "follow forks" and trace child processes, too, as soon as they're made.

'-ff' - follows forks with separate output files per-fork

#Attaching strace to a running process

strace can also be attached to a running process and can be used to record its system calls.

To do this, we must know the PID of the process which we want to debug. 

We can get this PID using the ps command. 

When we have the PID, we can pass it to strace using the -p parameter to the command.

```bash
$ strace -p 4724
```

The “strace -p ...” which is attached to a process may be stopped at any time by typing CTRL-C; the
tested program then continues to proceed normally and at full speed.

If the program was started under strace, typing CTRL-C will not only abort strace, but also the launched program

#Tracing only specific system calls 

Sometimes the full syscall trace is too much

Using –e option we can also specify which system calls to be traced.

To trace only open() and close() system calls use the following command:

```bash
$ strace –e trace=’open,close’ <program-name>
```

Similarly we can also use negation option to not trace specific system calls. If we don’t want to trace open() system call in previous example we can give the below command 

```bash
$ strace -e trace='!open,close' ./a.out
```

#Track by specific system call group

- -e trace=ipc – Track communication between processes (IPC)
- -e trace=memory – Track memory syscalls
- -e trace=network – Track memory syscalls
- -e trace=process – Track process calls (like fork, exec)
- -e trace=signal – Track process signal handling (like HUP, exit)
- -e trace=file (for syscalls that mention filenames)
- -e trace=desc (for read() and write() and friends, which mention file descriptors)

```bash
strace -e trace=open,stat,read,write gnome-calculator

strace -e trace=openat cat /etc/hosts
strace -e trace=openat,close cat /etc/hosts
strace -e trace=openat,close,read,write cat /etc/hosts
strace -e file cat /etc/hosts
-s [size] Print [size] characters per string displayed. This is useful if you are trying to trace what a program is writing to a file descriptor.

strace -s 80 ./program
```

This will print the first 80 characters of every string.

#Print Instruction Pointer During System Call

The -i option displays the instruction pointer at the time of each system call made by the program.

```bash
strace -i df -h
strace -s 2000 -f ./program1
```

the “-s” flag to strace telling it the maximum string size we want it to print. This is helpful for showing expanded function arguments. 

Here we pass 2000, which is abitrarily “enough” to see everything we need to see in this program. The default is 32, which in my experience means we’ll almost definitely miss information we care about in the trace

#LTrace

ltrace is a debugging utility in Linux, used to display the calls a userspace application makes to shared libraries.

Its name itself comes from library-call tracing.

This tool is very useful for debugging user-space applications to determine which library call is failing.

`ltrace ./executable <parameters>`

```bash
$ ltrace <application> <application_parameters>
$ ltrace /bin/cat
```

ltrace(1) also allows you to selectively trace library calls when executed with the “-e” option and a set of calls to trace:

```bash
$ ltrace -e malloc /bin/cat
```

If you need to view the library calls from a live process, you can use ltrace(1)’s “-p” option:

```bash
$ ltrace -p 2644
```

The parameter -c outputs the number and duration of the library calls that have occurred

```bash
$ ltrace -c ls /
```

