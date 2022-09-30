# Concepts
## Latency
The time it takes for certain operations to complete in a system. Most often this measure is a time duration, like milliseconds or seconds. You should know these order of magnitudes:
- **Reading 1MB from RAM**: 0.25 ms
- **Reading 1MB from SSD**: 1.00 ms
- **Transfer 1MB over Network**: 10 ms
- **Reading 1MB from HDD**: 20 ms
- **Inter-Continental Round Trip**: 150 ms

## Throughput
The number of operations that a system can handle properly per time unit. Fot instance the throughput of a server can often be measured in requests per second (RPS or QPS)

## Availability
The odds of a particular server or service being up and running in any point in time, measured in percentages. A server that has a 99% availability will be operational 99% of the time (this would be described as having two **nines** of availability).

### High Availability
Used to describe that have particularty high levels of availability, typically 5 nines or more; sometimes abbreviated "HA"

### Nines
Typically refers to peprcentages of uptime. For example five nines of availability means an uptime of 99.999% of the time. Below are the downtimes expected per year depending of those nines:
- 99%: 87.7 hours
- 99.9%: 8.8 hours
- 99.99%: 52.6 minutes
- 99.999%: 5.3 minutes

### Single Point of Failure (SPOF)
A single point of failure (SPOF) is a part of a system that, if it fails, will stop the entire system from working. SPOFs are undesirable in any system with a goal of high availability or reliability, be it a business practice, software application, or other industrial system.

### Redundancy
The process of replicating parts of a system in an effort to make it more reliable. It is a good design principle to avoid SPOFs.

### SLA
Short for "service-level agreement", SLA is a colection of guarantees given to a customer by a service provider. SLA typically make guarantees on a system's availability, amongst other things. SLAs are made up by one or multiple SLOs.

### SLO
Short for "service-level objective", SLO is a guarantee given to a customer by a service provider. SLOs typically make guarantees on a system's availability, amongst other things. SLO constitute an SLA
