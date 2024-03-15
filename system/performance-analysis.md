# Book Summary
Author: Denis Bakhvalov
URL: easyperf.net

## Chapter 1 - Introduction
- HW is not getting that much performance boosts in single-threaded performance as it used to in the past years. That’s why performance tuning is becoming more important than it has been for the last 40 years. The computing industry is changing now much more heavily than at any time since the 90s.
- According to [Leiserson et al., 2020], SW tuning will be one of the key drivers for performance gains in the near future. The importance of performance tuning should not be underestimated. For large distributed applications, every small performance improvement results in immense cost savings.
- Software doesn’t have an optimal performance by default. Certain limitations exist that prevent applications to reach their full performance potential. Both HW and SW environments have such limitations. CPUs cannot magically speed up slow algorithms. Compilers are far from generating optimal code for every program. Due to HW specifics, the best-known algorithm for a certain problem is not always the most performant. All this leaves the room for tuning the performance of our applications.
- For some types of applications, performance is not just a feature. It enables users to solve new kinds of problems in a new way.
- SW optimizations should be backed by strong business needs. Developers should set quantifiable goals and metrics which must be used to measure progress.
- Predicting the performance of a certain piece of code is nearly impossible since there are so many factors that affect the performance of modern platforms. When implementing SW optimizations, developers should not rely on intuition but use careful performance analysis instead.

## Chapter 2 - Measuring Performance
- Debugging performance issues is usually harder than debugging functional bugs due to measurement instability.
- You can never stop optimizing unless you set a particular goal. To know if you reached the desired goal, you need to come up with meaningful definitions and metrics for how you will measure that. Depending on what you care about, it could be throughput, latency, operations per second (roofline performance), etc.
- Modern systems have non-deterministic performance. Eliminating non-determinism in a system is helpful for well-defined, stable performance tests, e.g., microbenchmarks. Measuring performance in production deployment requires dealing with a noisy environment by using statistical methods for analyzing results.
- More and more often, vendors of large distributed SW choose to profile and monitor performance directly on production systems, which requires using only light-weight profiling techniques.
- It is very beneficial to employ an automated performance tracking system for preventing performance regressions from leaking into production software. Such CI systems are supposed to run automated performance tests, visualize results, and flag potential defects.
- Visualizing performance distributions may help to discover performance anomalies. It is also a safe way of presenting performance results to a wide audience.
- Statistical relationship between performance distributions is identified using Hypothesis Testing methods, e.g., Student’s T-test. Once it’s determined that the difference is statistically significant, then the speedup can be calculated as a ratio between the means or geometric means.
- It’s OK to discard cold runs in order to ensure that everything is running hot, but do not deliberately discard unwanted data. If you choose to discard some samples, do it uniformly for all distributions.
- To benchmark execution time, engineers can use two different timers, which all the modern platforms provide. The system-wide high-resolution timer is suitable for measuring events whose duration is more than a microsecond. For measuring short events with high accuracy, use Time Stamp Counter.
- Microbenchmarks are good for proving something quickly, but you should always verify your ideas on a real application in practical conditions. Make sure that you are benchmarking the meaningful code by checking performance profiles.

## Chapter 3 - CPU Microarchitecture
## Chapter 4 - Terminology and Metrics
- Retired vs Executed Instruction: Modern processors typically execute more instructions than the program flow requires. This happens because some of them are executed speculatively. So, an instruction processed by the CPU can be executed but not necessarily retired.
- CPU Utilization: CPU_CLK_UNHALTED.REF_TSC PMC counts the number of reference cycles when the core is not in a halt state, TSC stands for timestamp counter (discussed in section 2.5), which is always ticking. CPU Utilization = CPU_CLK_UNHALTED / TSC.
- CPI & IPC: Cycles Per Instruction (CPI) - how many cycles it took to retire one instruction on average;  Instructions Per Cycle (IPC) - how many instructions were retired per one cycle on average.
- UOPs: Microprocessors with the x86 architecture translate complex CISC-like60 instructions into simple RISC-like61 microoperations - abbreviated μops or uops. The main advantage of this is that μops can be executed out of order
- Pipeline Slot: A pipeline slot represents hardware resources needed to process one uop. Figure 17 demonstrates the execution pipeline of a CPU that can handle four uops every cycle. Nearly all modern x86 CPUs are made with a pipeline width of 4.
- Core vs Referece Cycles: The majority of modern CPUs, including Intel and AMD CPUs, don’t have a fixed frequency at which they operate. Instead, they implement dynamic frequency scaling. The core clock cycles counter is counting clock cycles at the actual clock frequency that the CPU core is running at, rather than the external clock (reference cycles)
- Cache Miss: As discussed in section 3.5, any memory request missing in a particular level of cache must be serviced by higher-level caches or DRAM. This implies a significant increase in the latency of such memory access
- Mispredicted Branch: Modern CPUs try to predict the outcome of a branch instruction (taken or not taken)

## Chapter 5 - Performance Analysis Approaches
- Latency and throughput are often the ultimate metrics of the program performance. When seeking ways to improve them, we need to get more detailed information on how the application executes. Both HW and SW provide data that can be used for performance monitoring.
- Code instrumentation allows us to track many things in the program but causes relatively large overhead both on the development and runtime side. While developers do not manually instrument their code these days very often, this approach is still relevant for automated processes, e.g., PGO.
- Tracing is conceptually similar to instrumentation and is useful for exploring anomalies in the system. Tracing allows us to catch the entire sequence of events with timestamps attached to each event.
- Workload Characterization is a way to compare and group applications based on their runtime behavior. Once characterized, specific recipes could be followed to find optimization headrooms in the program.
- Sampling skips the large portion of the program execution and take just one sample that is supposed to represent the entire interval. Even though sampling usually gives precise enough distributions. The most well-known use case of sampling is finding hotspots in the code. Sampling is the most popular analysis approach since it doesn’t require recompilation of the program and has very little runtime overhead.
- Generally, counting and sampling incur very low runtime overhead (usually below 2%). Counting gets more expensive once you start multiplexing between different events (5-15% overhead), sampling gets more expensive with increasing sampling frequency [Nowak and Bitzes, 2014]. Consider using user-mode sampling for analyzing long-running workloads or when you don’t need very accurate data.
- Roofline is a throughput-oriented performance model that is heavily used in the HPC world. It allows plotting the performance of an application against hardware limitations. Roofline model helps to identify performance bottlenecks, guides software optimizations, and keeps track of optimization progress.
- There are tools that try to statically analyze the performance of the code. Such tools simulate the piece of code instead of executing it. Many limitations and constraints apply to this approach, but you get a very detailed and low-level report in return.
- Compiler Opt reports help to find missing compiler optimizations. It may also guide developers in composing new performance experiments.

## Chapter 6 - CPU Features For Performance Analysis
- Utilizing HW features for low-level tuning is recommended only once all high-level performance issues are fixed. Tuning poorly designed algorithms is a bad investment of a developer’s time. Once all the major performance problems get eliminated, one can use CPU performance monitoring features to analyze and further tune their application.
- Top-Down Microarchitecture Analysis (TMA) methodology is a very powerful technique for identifying ineffective usage of CPU microarchitecture by the program. It is a robust and formal methodology that is easy to use even for inexperienced developers. TMA is an iterative process that consists of multiple steps, including characterizing the workload and locating the exact place in the source code where the bottleneck occurs. We advise that TMA should be a starting point of analysis for every low-level tuning effort. TMA is available on Intel and AMD152 processors.
- Last Branch Record (LBR) mechanism continuously logs the most recent branch outcomes in parallel with executing the program, causing a minimal slowdown. It allows us to have a deep enough call stack for every sample we collect while profiling. Also, LBR helps identify hot branches, misprediction rates and allows for precise timing of machine code. LBR is supported on Intel and AMD processors.
- Processor Event-Based Sampling (PEBS) feature is another enhancement for profiling. It lowers the sampling overhead by automatically sampling multiple times to a dedicated buffer without interrupts. However, PEBS are more widely known for introducing “Precise Events”, which allow pinpointing exact instruction that caused a particular performance event. The feature is supported on Intel processors. AMD CPUs have a similar feature called Instruction Based Sampling (IBS).
- Intel Processor Traces (PT) is a CPU feature that records the program execution by encoding packets in a highly compressed binary format that can be used to reconstruct execution flow with a timestamp on every instruction. PT has extensive coverage and relatively small overhead. Its main usages are postmortem analysis and finding the root cause(s) of performance glitches. Processors based on ARM architecture also have a tracing capability called CoreSight153, but it is mostly used for debugging rather than for performance analysis.

### TMA Step by Step

- The concept behind TMA’s top-level breakdown
<img width="458" alt="image" src="https://github.com/rafaelpfreire/code-snippets/assets/14954472/36ea5efe-4d34-45c9-bb12-4ca915931d1f">

- The TMA hierarchy of performance bottlenecks
<img width="454" alt="image" src="https://github.com/rafaelpfreire/code-snippets/assets/14954472/64e30b4b-4075-4316-973e-8e7f49e36a7f">

- Step 1: Identify the bottleneck
Run the first level topdown so you can identify if the bottleneck is coming from Frontend, Bad Speculation, Backend or Retiring
You can use linux `perf` in order to run first level TMA
```
perf stat --topdown -a -- taskset -c 0 ./perf-test
```
Or you might want to use `pmu-tools`
```
./pmu-tools/toplev.py --core S0-C0 -l1 -v --no-desc taskset -c 0 ./perf-test
```
- Step 2: Locate the place in the code
Then you can run the second level in order to have more details. Also you can run `toplev` with --show-sample in order to get a full `perf` command with the PMC names to sample.
```
./pmu-tools/toplev.py --show-sample --core S0-C0 -l2 -v --no-desc taskset -c 0 ./perf-test
```
Once you have the PMC names use `perf record` and `perf report` in order to locate the bottleneck inside your code
```
perf record -e cpu/event=0xd1,umask=0x20,name=MEM_LOAD_RETIRED.L3_MISS/ppp ./a.out
perf report -n --stdio
```
- Step 3: fix it

### LBR Step by Step
- Users can make sure LBRs are enabled on their system by doing the following command:
```
dmesg | grep -i lbr
# [ 0.228149] Performance Events: PEBS fmt3+, 32-deep LBR, Skylake events,
# full-width counters, Intel PMU driver.
```
- With Linux perf, one can collect LBR stacks using the command below:
```
perf record -b -e cycles ./perf-test
```
- Below is the Linux perf command one can use to dump the contents of collected branch stacks:
```
perf script -F brstack &> dump.txt
```
- Capture call graph
```
perf record --call-graph lbr -- ./a.exe
perf report -n --stdio
```
- Identify hot branches
```
perf record -e cycles -b -- ./a.exe
perf report -n --sort overhead,srcline_from,srcline_to -F +dso,symbol_from,symbol_to --stdio
```
- Analyze branch misprediction rate
```
perf record -e cycles -b -- ./a.exe
perf report -n --sort symbol_from,symbol_to -F +mispredict,srcline_from,srcline_to --stdio
```
- Precise timing of machine code: This can be done by creating a probability density graph of the sampled number of cycles between branches. This sampling method is not affected by context switches, that's why you should use this in order to have a precise measurement of timing. This information can be extracted using perf or manually as explained in this post: https://easyperf.net/blog/2019/04/03/Precise-timing-of-machine-code-with-Linux-perf
```
perf record -e cycles -b -- ./perf-test
perf report -n --sort symbol_from,symbol_to -F +cycles,srcline_from,srcline_to --stdio
```
- Problem on measuring time within the code (e.g. rdtsc instruction): OS context switches, CPU frequency changes, you're not really measuring production code. (https://www.strchr.com/performance_measurements_with_rdtsc)
- Estimating branch probability using LBR: https://easyperf.net/blog/2019/05/06/Estimating-branch-probability

### PEBS Step by Step
- Check if PEBS is available in your system
```
dmesg | grep PEBS
```
- Hardware skid: https://software.intel.com/en-us/vtune-help-hardware-event-skid; https://easyperf.net/blog/2018/08/29/Understanding-performance-events-skid
- Analysing memory accesses
```
perf mem record -- ./perf-test
perf mem -t load report --sort=mem --stdio
```

### Intel Processor Traces Step by Step
- Part 1: https://easyperf.net/blog/2019/08/23/Intel-Processor-Trace
- Part 2: https://easyperf.net/blog/2019/08/30/Intel-PT-part2
- Part 3: https://easyperf.net/blog/2019/09/06/Intel-PT-part3
- Part 4: https://easyperf.net/blog/2019/09/13/Intel-PT-part4
