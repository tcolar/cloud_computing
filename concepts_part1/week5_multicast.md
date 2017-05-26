# Multicast Ordering
- Multicast : Sent to a group of processes
- Broadcast : Sent to all Processes
- Unicast : Sent to one process

Ordering:

- Causal ordering : Multicast that are Casually related must be received in order.
- FIFO ordering : Multicast from a Sender must be recieved in the order they where sent (by this sender)
- Total ordering : "Atomic Broadcast", Ensures All events are received in the same order at all processes (M1, then M2, then M3....)

## Implementation

### FIFO:

Each process maintains a vector or sequence numbers of last known sequence at the processes.
IE: with 4 Processes, they all start with (0,0,0,0)

Send a multicast from P(j):

- p(j)++
- send multicast with new p(j) value(v)

Receiving the multicast at P(i) - from P(j):

- If received v == pi(j)+1 (expected), set pi(j) = v
- else : Buffer until v == pi(j)+1 becomes true 

### Total Ordering
- Use a sequencer from an elected leader (Global sequence s)
- Broadcast s with the message and ensure order, buffer as needed.

### Causal Ordering

Each process maintains a vector or sequence numbers of last known sequence at the processes.
IE: with 4 Processes, they all start with (0,0,0,0)

- p(j)++
- send multicast with the whole vector, including the new p(j) value(v).

Receiving the multicast at P(i) - from P(j), **buffer until**: 
- If received v[j] == pi(j)+1 (expected)
- for all other v[k] : v[k] <= pi[k]  . Obeys Causality

Then set `pi(j) = v[j]`.

```
P1 ----1-------R12-------R14------>
P2 -----R21--2---------------R24-->
P3 ------------R32----R34----R31-->
P4 -----R41--4---------------R42-->

- 2 Means Sent Multicast 2
- R12 Means Received at P1 multicast 2.

- 1   : [1,0,0,0]
- R21 : [1,0,0,0]
- R41 : [1,0,0,0]
- 2   : [0,1,0,0] -> [1,1,0,0]
- R12 : [1,1,0,0]
- R32 : [1,1,0,0] -> Buffer. local is [0,0,0,0], need to receive from P1 first.
- 4   : [1,0,0,1]
- R14 : [1,0,0,1] -> [1,1,0,1]
- R24 : [1,0,0,1] -> [1,1,0,1]
- R34 : [1,0,0,1] -> Buffer. local is [0,0,0,0], need to receive from P1 first.
- R31 : [1,0,0,0] -> ok, also deliver buffered R32 [1,1,0,0] and R34 [1,0,0,1] -> [1,1,0,1]
- R42 : [1,1,0,0] -> [1,1,0,1]
```

## Reliable Multicast

- Says all "non faulty" processes must receive all multicasts
- Not acceptabe for a multicast NOT to be sent to all other corrcet processes

Possibe solution: When one process receives a multicast, re-multicast it to all other processes (fault tolerance) -> Works but slow.

## Virtual Synchrony

Also knows as "View Synchony"

Combines Membership + Multicast

A multicast is said to be delivered in a view if it is sent by a process while that is the current view.

- Each process maintains a membership list (View)
- Any membership update (join,leave,fail) is a View chnage
- All View changes are **Guaranteed** to be delivered in the same order at all correct processes
- Might be at different times at different processes but the Order is respected.

Guarantees:

- All View changes are **Guaranteed** to be delivered in the same order at all correct processes
- Multicasts delivered in a view are the same at each process. What happened in a view stays in a view.
- The sender of the message is always included in the view
- If a process delivers a view that is missing multicasts expected in that view, that process will be removed.

```
P1 V1[N:1,2,3 M1, M2] V2[[N:1,3 M4, M5]]
P2 V1[N:1,2,3 M1, M2] V2[[N:1,3 M4, M5]]

Not OK:
- P3 V2[[N:1,3 M4, M5]] V1[N:1,2,3 M1, M2] -> Views out of order
- P3 V1[N:1,2,3 M1, M2] V2[[N:1,3 M4, M5]] -> P3 must be in view
- P3 V1[N:1,3 M1, M2] V2[[N:1,3 M4, M5]] -> V1 is missing N2
- P3 V1[N:1,2,3 M1] V2[[N:2,3 M4, M5]] -> M2 missing from V1
- P3 V1[N:1,2,3 M1] V2[[N:2,3 M2, M4, M5]] -> M2 in wrong view

OK:
P3 V1[N:1,2,3 M1, M2] V2[[N:1,3 M4, M5]] -> same view order and same members and multicast messages
```

Orthogonal to Multicast ordering (any impl ok)

Make an Asynchronous system appear synchronous (virtually), but still succeptible to Partitioning (CAP).