# Concurrency Control

## RPC
LPC - Local procedure call, If process alive, function called exactly once

- RPC to a different process
- RPC's might fail

Semantics:
- At most once (ie Java RMI)
- At least once (ie: Sun RPC)
- best effort  (ie: Corba)

Idempotent transactions work well with "at least once" model.

Client talk to each others via RPC stubs (function signature)

RPC code is code generated form signature definition

Client & Server might have different architectures (endianess), so the
generated middleware uses a Common Data Representation (CDR) that
are then Marshalled / Unmarshalled.

## Transactions
Set operations done atomically, either:
- All operations are commited (success)
- All operations are cancelled (failure)

Typical model:
- Start transaction (tx id)
- tx.execute operations
- tx.execute operations
- commit(tx)

ACID model
- Atomicity
- Consistency (State)
- Isolation (Isolated from other transactions effects)
- Durability

Potential issues:
- Lost update (transactions overlap)
- Inconsistent retrieval

## Sequential Equivalence
To isolate transactions we could execute them one at a time -> works but
bad for latency.

Transactions are serially equivalent if:
- The two transactions can be interleaved without effect(ie: order of execution has no effects)

For all transactions mark them (T1->T2) ie: T1 to T2.
If all operations are T1->t2 or T2->T1 (but not mixed) then it's equivalent.

This catches the problem scenarios (Lost update & inconsistent retrieval)

If not serially equivalent then abort/rollback

## Pessimistic Concurrency
Assume the worst - Locking

### Full Locking:
- Each object has a lock, transaction locks or unlocks it (ie: Mutex)
- Works but not concurrent (high latency)
- Wasted concurrency for common read-heavy loads

### RW Locking (ie: write lock doesn't block reads)

### Two Phase Locking
- Growing phase : Acquire or promote locks
- Shrinking phase : Release locks
- Fits serial Equivalence

But ... Risk of deadlocks

Deadlock occurs if:
- Object accessed in exclusive lock mode
- Transaction holding locks can not be preempted
- Circular wait in the DAG

Combating Deadlocks:
- Timeout then cancel one -> Slow and wasteful
- Deadlock detection (detect cycles in wait graph), if cycle cancel one -> wasteful too.

## Optimistic Concurrency Control
- Preferable when conflicts are expected to be rare
- Increase RPS & latency
- Used in Dropbox, Gapps, Wikipedia, Cassandra, Riak, Dynamo etc ....

### Multi-version Concurrency Control
- Per transaction version of the object is maintained (tentative)
- Commited version is maintained
- On read/write find the correct version to read/write from
- "correct" based on transaction ID and only read from "immediately" previous transactions.

### Eventual Consistency
- It's a form of Optimistic concurrency, ie : Cassandra, Dynamo, Riak
- But not transaction based
- Strategy: simply LWW (Last write Win) based on (local) timestamp (Cassandra, DynamoDb)
- Or use Vector timestamp (Riak), in case of conflict a sibling value is created, to be resolved by user/app.
