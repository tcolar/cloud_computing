# Scheduling

## Single processor
- FIFO - One at a time, in order -> av completion time may be high
- STF - Shortest task first - shortest abg time (optimal)
- Round Robin - time slices given to taks at intervals (preempting)

Round robin better for interactive tasks, STF good for batch tasks

## HADOOP Scheduling
Multiple Map Reduce tasks scheduled by YARN

Yarn Aproaches:
- Capacity 
- Fair scheduler 

### Capacity scheduler
- Multiple queue, multiple jobs, each guaranteed some cluster capacity
- ie: Q1: 70%, Q2: 30% (Soft + Hard limit), Elasticity allowed 
- FIFO within a queue
- No Preemption - Job must run completely
- Queues can be hierarchical

### Fair Scheduler
Good for multi trenant system, all tenants/jobs get equal/fair share of cluster

- Cluster divided in pools
- Resources dictributed equally per pool
- Each pool can use Fifo, or fair scheduling etc...
- Preemption: If a job can't get resources for a while another job maybe preempted (here killed).
- If kills, then pick a recently started task to minimize wasted work

Good to run shorter tasks first, but difficult to estimate tasks length

### Dominant Resource Fair Scheduler
- ie: VM's in a cloud , limited CPU, Memory
- Used in Mesos and clouds

If a job is CPU intensive give it more CPU but less memory and vice-versa

Can generalize for more resources, disk space, io speed,  etc...


