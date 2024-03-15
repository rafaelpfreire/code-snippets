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

## Cache
A piece of hardware of software that stores data, typically meant to retrieve that data faster than otherwise. Caching is typically used when you need to do a lot of long operations (i.e. networking requests, reads from database, perform long algorithm operations) and you want to avoid doing so. Note that data in the cache can become stale if the main source of truth for that data (i.e., the main database behind the cache) gets updated and the cache doesn't.

Popular COTS solution for caches is: Redis (https://redis.io/)

A cache hit is when requested data is found in a cache. Cache miss is when requested data could have been found in a cache but it isn't. This is typically used to refer to a negative consequence of a system failure or of a poor design choice. For example: If a server goes down, our load balancer will have to forward requests to a new server, which will result in cache misses.

### Cache Eviction Policy
The policy by which values get evicted or removed from a cache. Popular eviction policies: LRU (Least Recently Used), LFU (Least Frequently Used), LIFO, FIFO, Random, etc.

### Content Delivery Network (CDN)
A CDN is a third-party service that acts like a cache for your servers. Sometimes, web applications can be slow for users in a particular region if your servers are located only in another region. A CDN has servers all around the world, meaning that the latency to a CDN's servers will almost always be far better than the latency to your servers. A CDN's servers are often referred to as PoP (Pointes of Presence). Two of the most popular CDN's are Cloudflare and Google Cloud CDN.

### Write Through Cache
When you write a peace of data, the system will write in both in the cache and in the main source of truth using the same operation. With this type you will always have to access the main source of truth in each write operation. If you're dealing with static data (doesn't change too often) caches works beautifully, but you're dealing with data that is mutable things start to get tricky.

### Write Back Cache
When you write a peace of data, the system will only write in the cache. That way your cache would be some time out of sync with your main source of truth. Behind the scenes your system should asynchronously update the main source or truth (i.e. database) with the values stored in the cache (based on time or size of the cache).

## Proxy
Intermediary servers that boast many important real life applications within the context of caching, access control, censorship bypassing, gather metrics, load balancer, etc.

Popular COTS solution for proxies/load balancer: Nginx (https://www.nginx.com/)

### Forward Proxy
A server that sits between a client and servers and acts on behalf of the client, typically used to mask the client's identity (IP address). Note that forward proxies are often referred to as just proxies.

### Reverse Proxy
A server that sits between clients and servers and acts on behalf of the servers, typically used for logging, load balancing or caching.

## Load Balancer
A type of reverse proxy that distributes traffic accross servers. Load balancers can be found in many parts of a system, from the DNS layer all the way to the database layer.

### Server Selection Strategy
How a load balancer chooses servers when distributing traffic amongst multiple servers. Commonly used strategies include round-robin, random selection, performance-based selection (choosing the server with the best performance metrics, like the fastest response time or the least amount of traffic), and IP-based routing.

### Hot Spot
When distributing a workload accross a set of servers, that workload might be spread unevenly. This can happen if your sharding key of your hashing function are suboptimal, or if your workload is naturally skewed: some servers will receive a lot more traffic than others, thus creating a "hot spot".

### Technique of software load balancer
First of all the load balancer should know addresses and/or names of the servers that are available
- *DNS Round Robin Load Balancer*:
- *Random redirection*: 

## Hashing
## Relational Databases
## Key-Value Stores
## Specialized Storage Paradigms
## Replication And Sharding
## Leader Election
## Peer-to-Peer Networks
## Polling and Streaming
## Configuration
## Rate Limiting
## Logging and Monitoring
## Publish/Subscribe Pattern
## MapReduce
## Security and HTTPS

TODO: 
- graylog: https://www.graylog.org/
- spdlog
- fftw: https://www.fftw.org/
- volk: https://github.com/gnuradio/volk
- vectorclass: https://github.com/vectorclass/version2
- eigen: https://eigen.tuxfamily.org/index.php?title=Main_Page
