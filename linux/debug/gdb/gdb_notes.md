## How to compile a program to use with gdb
```bash
gcc -g -o binaryfile source_code.c
#-g tells the compiler to store symbol table information in the executable.
```
This includes:
- symbol names
- type info for symbols
- files and line numbers where the symbols came from

`Tip: Check the size of binary with and without debugging symbols`

```bash
gdb ./binaryfile
```

or

```bash
gdb
(gdb) file path_to_binary
```

GDB is a command line interface. This means you will be provided with a prompt at which you can type commands. The GDB commandline looks like this:

```bash
(gdb)
```

## Basic Commands

This starts the program which you want to debug. 

```bash
(gdb) run
```

To exit GDB, use the quit command (abbreviated q) or type an end-of-file character (usually Ctrl-d).

```bash
(gdb) quit
```

The "-q" (or "--quiet") option on the command line just tells GDB not to print version information on startup. 
(gdb) quiet

You can also start gdb from a PID. From the command line, include the pid as an argument after the executable name:

```bash
gdb /path/to/prog PID
```

From within gdb, you can use the attach command:

```bash
gdb /path/to/prog
gdb> attach PID
```

## Help

If you’re ever confused about a command or just want more information, use the “help” command, with or without an argument:

```bash
(gdb) help [command]
```

The whole purpose of coming to gdb was to pause, observe and proceed. There is no point in running a program without a breakpoint! 

## Breakpoints

Breakpoints can be used to stop the program run in the middle, at a designated point. Whenever gdb gets to a breakpoint it halts execution of your program and allows you to examine it. Simplest way of putting a breakpoint is using the function name or a line number.

```bash
(gdb) break factorial 
Breakpoint 1 at 0x400538: file source_code.c, line 5.

(gdb) break 7
Breakpoint 2 at 0x400545: file source_code.c, line 7.
```

### List of functions available

```bash
(gdb) info functions 
```

### List of breakpoints available

```bash
(gdb) info breakpoints 
```

Run the program and it will stop at the first breakpoint

```bash
(gdb) r
```

### Breakpoint in multithreaded system

When your program has multiple threads, you can choose whether to set breakpoints on all threads, or on a particular thread.

```bash
(gdb) break locspec thread thread-id
(gdb) break locspec thread thread-id if …
```

locspec specifies a code location or locations in your program. See Location Specifications, for details.

You can use the thread qualifier on conditional breakpoints as well; in this case, place ‘thread thread-id’ before or after the breakpoint condition, like this:

```bash
(gdb) break frik.c:13 thread 28 if bartab > lim
```

Thread-specific breakpoints are automatically deleted when GDB detects the corresponding thread is no longer in the thread list.

### Delete Breakpoints

```bash
(gdb) delete <bpnumber>
```

### Disable/Enable Breakpoints

```bash
(gdb) disable <bpnumber>

(gdb) enable <bpnumber>
```

## Step by step

Once you have hit a breakpoint, you can have fine control over the execution of the program, using the following commands

```bash
(gdb) continue
```

Continue execution till the next break point or end of program

Typing 'run' again instead of 'continue' would restart the program from the beginning.

```bash
(gdb) next
```

Proceed to the next line of execution (Doesn’t step into a function call in the current line)

```bash
(gdb) step
```

The same as next, but with difference that if you are at a function call
- next -  the function will execute and return
- step - step into the first line of the called function.

```bash
(gdb) finish
	Finish executing the current function, then pause (also called step out). Useful if you accidentally stepped into a function.


(gdb) print n
```

The print command prints the value of the variable specified

```bash
(gdb) print/x n
Prints the value in hexadecimal
```

### Tip

Typing “step” or “next” a lot of times can be tedious. If you just press ENTER, gdb will repeat the same command you just gave it.

## Different ways to pass command line arguments

You can run gdb with --args parameter,

```bash
$ gdb --args executablename arg1 arg2 arg3

$ gdb ./a.out

(gdb) r arg1 arg2 arg3
```

## Debugging Segmentation Fault Example

The first step is to compile the program with debugging flags:

```bash
$ gcc -g source_code.c

$ gdb ./a.out
```

We'll just run it and see what happens:

```bash
(gdb) run
Starting program: /home/panther2/Linux_System_Prog/day3_debugging/gdb/4/a.out 
hello

Program received signal SIGSEGV, Segmentation fault.
__GI__IO_getline_info (fp=fp@entry=0x7ffff7dd4640 <_IO_2_1_stdin_>, buf=buf@entry=0x0, n=1022, delim=delim@entry=10, 
    extract_delim=extract_delim@entry=1, eof=eof@entry=0x0) at iogetline.c:86
86	iogetline.c: No such file or directory.
```

So we received the SIGSEGV signal from the operating system. This means that we tried to access an invalid memory address

```bash
(gdb) backtrace
The command backtrace (or bt) will show you the current function call stack, with the current function at the top, and the callers in order beneath it:

(gdb) bt
#0  __GI__IO_getline_info (fp=fp@entry=0x7ffff7dd4640 <_IO_2_1_stdin_>, buf=buf@entry=0x0, n=1022, delim=delim@entry=10, 
    extract_delim=extract_delim@entry=1, eof=eof@entry=0x0) at iogetline.c:86
#1  0x00007ffff7a80368 in __GI__IO_getline (fp=fp@entry=0x7ffff7dd4640 <_IO_2_1_stdin_>, buf=buf@entry=0x0, n=<optimized out>, 
    delim=delim@entry=10, extract_delim=extract_delim@entry=1) at iogetline.c:38
#2  0x00007ffff7a7f206 in _IO_fgets (buf=0x0, n=<optimized out>, fp=0x7ffff7dd4640 <_IO_2_1_stdin_>) at iofgets.c:56
#3  0x0000000000400634 in main (argc=1, argv=0x7fffffffdfb8) at source_code.c:10
```

We are only interested in our own code here, so we want to switch to stack frame 3 and see where the program crashed:

```bash
(gdb) frame 3
#3  0x0000000000400634 in main (argc=1, argv=0x7fffffffdfb8) at source_code.c:10
10		fgets(buf, 1024, stdin);
```

We crashed inside the call to fgets. So the problem must be one of our arguments

```bash
(gdb) print buf
$1 = 0x0
```

The value of buf is 0x0, which is the NULL pointer. malloc returns NULL when it cannot allocate the amount of memory requested. So our malloc must have failed. 

## Print Source Code In GDB Console

```bash
(gdb) list
prints 10 lines of source code at a time
```

You can also pass the list command <a line number> or <a function name> to tell GDB where to start.

```bash
#Display Lines After A Line Number
(gdb) list 12

#Display Lines After A Function
(gdb) list main

#Display Lines 1 to 14
(gdb) list 1,14
```

## Displaying Data

You can use print command to display the value of variables and other expressions

The print or p command takes any C expression as its argument:

p \[/format\] \[expression\]

```bash
(gdb) print i

(gdb) print &i

(gdb) print sizeof(i)

(gdb) print sizeof(&i)
```

Gdb comes with a powerful tool for directly examing memory: the x command. 

The x command examines memory, starting at a particular address. 

```bash
(gdb) x &i
0x7fffffffdedc:	0x00000539

#It comes with a number of formatting commands that provide precise control over 
#	how many bytes you’d like to examine and 
#	how you’d like to print them

(gdb) x/4xb &i
0x7fffffffdedc:	0x39	0x05	0x00	0x00

#The flags indicate that I want to examine 4 values
#	formatted as he'x' numerals, one 'b'yte at a time
#
#on Intel machines, bytes are stored in “little-endian” order
```

## Examining types with ptype

It tells you the type of a C expression

```bash
(gdb) ptype i
type = int

(gdb) ptype &i
type = int *

(gdb) ptype main
type = int ()

(gdb) print a
$2 = {1, 2, 3}

(gdb) ptype a
type = int [3]

# use x to see what a looks like under the hood

(gdb) x/12xb &a
0x7fffffffded0:	0x01	0x00	0x00	0x00	0x02	0x00	0x00	0x00
0x7fffffffded8:	0x03	0x00	0x00	0x00

#The first four bytes store a[0], the next four store a[1], and the final four store a[2]. 

#Indeed, you can check that sizeof knows that a’s size in memory is twelve bytes:

(gdb) print sizeof(a)
$3 = 12
```

## Using gdb to View the CPU Registers

The i r command displays the current contents of the CPU registers. The first column is the name of the register. The second shows the current bit pattern in the register, in hexadecimal. The third column shows some the register contents in 32-bit/64-bit unsigned decimal. 

## Frames

A running application maintains a call stack that contains information about its functions that have been called.

Each item in the stack is a call frame, and each frame contains both the information needed to return to its caller and the information needed to provide the local variables of the function. When your program starts, the call stack has only one frame, that of the function main. 

Each function call pushes a new frame onto the stack, and each function return removes the frame for that function from the stack. Recursive functions can generate many frames. Use backtrace.c for the below commands

```bash
$ gcc backtrace.c -o backtrace -g

$ gdb ./backtrace

(gdb) b main

(gdb) run

(gdb) bt

(gdb) b func1

(gdb) bt
```

### Moving from one frame to another

You can move between the stack frames using ‘frame [number]’

### Get Information about a Stack Frame

You can get the information about a particular frame using ‘info frame [number]’ 

```bash
(gdb) info frame  1   # list information about the current stack frame

(gdb) info variables # list all global and static variables 

(gdb) info locals   # list local variable values of current stack frame

(gdb) info args     # list argument values of current stack frame


(gdb) info registers        # list register values

(gdb) info registers eax    # shows just the register eax


(gdb) info breakpoints      # list status of all breakpoints
```

## Conditional Breakpoints

As long as a breakpoint is enabled, the debugger always stops at that breakpoint. However, sometimes it's useful to tell the debugger to stop at a break point only if some condition is met, like the when a variable has a particularly interesting value. You can specify a break condition when you set a breakpoint by appending the keyword if to a normal break statement

`break [position] if expression`

In the above syntax position can be a function name or line number. If you already set a breakpoint at the desired position, you can use the condition command to add or change its break condition:

`condition bp_number [expression]`

Watchpoints are similar to breakpoints. Watchpoints are set on variables. When those variables are read or written, the watchpoint is triggered and program execution stops.

## How do I set a write watchpoint for a variable?

Use the watch command. The argument to the watch command is an expression that is evaluated. This implies that the variabel you want to set a watchpoint on must be in the current scope. So, to set a watchpoint on a non-global variable, you must have set a breakpoint that will stop your program when the variable is in scope. You set the watchpoint after the program breaks.

```bash
(gdb) watch x
```

### How do I set a read watchpoint for a variable?

Use the rwatch command. Usage is identical to the watch command.

```bash
(gdb) rwatch y 
```

### How do I set a read/write watchpoint for a variable?

Use the awatch command. Usage is identical to the watch command.

```bash
(gdb) awatch z
```

## How do I disable watchpoints?

Active watchpoints show up the breakpoint list. Use the info breakpoints command to get this list. Then use the disable command to turn off a watchpoint, just like disabling a breakpoint.

## GDB Text User Interface (TUI)

The gdb Text User Interface (TUI) is a terminal interface which uses the curses library to show the
- source file
- assembly output
- program registers
- and GDB Commands

in separate text windows. The TUI mode is supported only on platforms where a suitable version of the curses library is available. The TUI mode is enabled by default when you invoke gdb as either ‘gdbtui’ or ‘gdb -tui’. You can also switch in and out of TUI mode while gdb runs by using various TUI commands and key bindings, such as Ctrl-x a

## Commands

Ctrl - l -- to repaint the screen //when there are printf's displayed

You can type commands on the command line like usual, but the arrow keys will scroll the source code view instead of paging through history or navigating the entered command.

To switch focus to the command line view, type ctrl-x o and the arrow keys works as in the normal command line mode. Switching back to the source code view is done using the same key combination a second time.

You may want to save the output of gdb commands to a file. There are several commands to control gdb’s logging.

`set logging on`
Enable logging.	GDB saves all output from this point in a text file called gdb.txt that resides in the directory in which you are running GDB 

`set logging off`
Disable logging. Note that you can turn logging on and off several times and GDB will concatenate output to the gdb.txt file

`set logging file file`
Change the name of the current logfile. The default logfile is ‘gdb.txt’.

Useful when you’re dealing with a long stack trace, or a multi-threaded stack trace

## Debugging an Already-running Process

`attach process-id`
This command attaches to a running process—one that was started outside gdb

`detach`
This command attaches to a running process—one that was started outside gdb

Another Useful function of gdb debugger is the disassemble command. As its name suggesting, this command helps in disassembling of provide function assembler codes. Like if we want to disassemble main function. we just need to type

```bash
(gdb) disassemble main
```

## start command

Sets a temporary breakpoint on main() and starts executing a program under GDB. Command breakpoint-number specifies commands to run whenever the breakpoint is reached. 

```bash
(gdb) command 2
#  Type commands for when breakpoint 2 is hit, one per line.
#  End with a line saying just "end".
```
