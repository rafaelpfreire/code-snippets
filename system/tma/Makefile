# Run perf without root access
# sudo sh -c echo -1 > /proc/sys/kernel/perf_event_paranoid
# sudo sh -c echo 0 > /proc/sys/kernel/kptr_restrict

# If you are running this on a VM you might need to enable
# vPMC hardware access from your guest OS. See documentation
# of the hypervisor you are using.
# vPMC: Virtual Performance Monitoring Counters

# Requirements: nasm and linux-tools-`uname -r`
# pmu-tools: github

BINARY=perf-test

.PHONY: all clean run

all: $(BINARY)

foo.o:
	nasm -f elf64 foo.asm

main.o:
	g++ -O2 -std=c++11 -c main.cpp

$(BINARY): main.o foo.o
	g++ $? -o $(BINARY)

clean:
	rm -f *.o
	rm -f $(BINARY)

run:
	#perf stat --topdown -a -- taskset -c 0 ./$(BINARY)
	../pmu-tools/toplev.py --core S0-C0 -l2 -v --no-desc taskset -c 0 ./$(BINARY)
