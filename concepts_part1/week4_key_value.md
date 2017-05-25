# Key-Value stores

- ~ Distribute hash tables 
- write heavy support
- may be schema-less
- speed
- availability
- horizontal scalability
- get/put/delete support

## Cassandra

- Map key to server : virtual ring of 2^m points (one ring per DC)
- partitioner maps keys to server
- Keys get stored at first node clockwise + backup replicas
- client send query to a node (coordinator),  this contacts the replicas
- no fingers or routing meta used

### Replication strategy: 

- simple strategy : random (hash) or ByteOrdered (good for range searchs)
- network topology strategy : 2 or 3 replicas per DC (often just clockwise until on a different rack) 

### Snitches (Map IP to DC/Rack):

- Simple : Random
- RackInferring : ip bytes map like this: xxx.<DC>.<Rack>.<Node>
- PropertyFile
- EC2: aws_region = DC, aws_az = rack

### Writes
Need to be fast and lock free

- Client sends query to a coordinator
- Coordinator use partitioner to send query to all replicas
- When x replicas replies, coordinator send ack to client 
- If any replica down, coordinator keeps the write locally for up to few hous
- One coordinator per DC talks to other DC (ZooKeeper election)

On the replica:
- Log to disk (Hlog)
- Store in MemTable (write back cache)

When MemTable full, flush

- SSTable (key value pairs)
- Index (Of SSTable)
- Bloom filter (faster searches)

Compaction:

- Keys maybe be in multiple SSTable -> merge them (runs periodically)

Deletes :

Don't delete right away (tombstone), will be deleted during compaction

Reads:

- Coordiantor asks x replicas, return latest timestamp
- Once responded if 2+ values diverge -> initiate a repair (latest timestamp)
- Coordinator also contact more replicas to initiate repair if needed (background)
- A column could be across multiple SSTables (reads slower than writes)

All servers need to know membership & coordinator
Gossip based + suspicion mechanism to avoid false positive

Much much faster than Relational DBs, but eventual consistency.

## CAP Theorem
Consistency, Availability, Partitioning -> Can only have 2

Base : Basically Available soft State  Eventual consistency

Cassandra as options : Any, All, One, Quorum (majority per cluster/DC)

Want W+R > N+1 to guarantee quorum 

## Consistency Spectrum
Eventual -------------------- Strong
Fast     -------------------- Consistent

In order (weak to strong consistency)
- Eventual
- Causal
- Per Key sequential
- Red Blue
- Probabilistic
- CRDT's (Communative replicated Data Types)
- Linearizability
- Sequential consistency (Lamport)
- Transaction ACID  (Spanner ...)

## HBase
Similar to  igTable

Prefers Consitency (unlike Cassandra)

- Small group of servers does conscensus (ZooKeeper)
- Multiple Regions with a HLOG, Multiple stores, with a MemStore & HFiles (stored on HDFS)

HBase Table:

- Split into multiple regions + replicated across servers
- One store per column family + region
- MemStore for each store, flushed to disk when full
- Store files, where the data lives -> HFile(SSTable)

Writes:

- Write to HLOG first (for recovery/replay after crash or at startup)
- Write to MemStore in the region