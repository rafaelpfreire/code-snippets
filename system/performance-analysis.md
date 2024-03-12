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
