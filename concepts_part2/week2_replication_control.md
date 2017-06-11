# Replication Control
- ie: Distributed Concurrency Control
- Multiple copies on replicas -> Fault tolerance / load balancing
- Higher availability 5 9's etc...

Challenges:
- Replication transparency (client not aware of copies)
- Consistency (All clients see the same value)
- For transactions, obey ACID

2 Kinds of replication:
- Passive : uses a master
- Active : no master

Active Replication
- May use multicast ordering (Fifo, casual, total, hybrid etc...)
- Total ordering + state machine -> all replicas reflect the same updates to an object

For failures, may use Virtual synchrony

# 2 Phase commit
We want to ensure ALL servers commit the same value, or None (all aborted)
"Atomic commit problem" ~= "consensus problem"

2 phase commit:
- Phase 1 : prepare
- Phase 2 : commit all (if all phase 1 where ok), otherwise abort all

Can use Paxos
