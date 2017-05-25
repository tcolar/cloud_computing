## MapReduce
- Map : Process records and generate key:value pairs
- Reduce : Merges the results per key.

### Scheduling

- All mappers need to be done before reduce can start.
- Assign Map to servers that are closest to data (same server/rack/dc)
- Reduce to distributed file system (HDFS)

### YARN (Hadoop)

Each server considered as several containers (CPU + mem)

- Global Resource manager (RM): assigns map and reduce to servers
- Node manager (NM):
- Application master (AM): 

Process: AM asks RM for container, AM starts task on that container (could be on another node)

### Fault Tolerance

- NM heartbeats to RM
- NM keep track of all tasks (can kill or restart if needed)
- AM heartbeats to RM (can be restarted)
- RM has checkpointing if restart or secondary RM needed

Stragglers (slow/hung task) -> speculative execution: detect slowness, give same job to a different node and just use whichever completes first.

Locality : HDFS usually has 3 replicas by default (tries at least 2 racks). Try to schedule map closer to data: same node first, same rack, anywhere.