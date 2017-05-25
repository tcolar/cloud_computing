# Snapshots
Global state of the system at a given "time"

Individual state of each Process + state of each communication channel

Uses:

- Checkpointing (for recovery)
- Garbage collection
- Deadlock detection
- Termination of computation

Global state chnages whenever an event happens, events:
- A process step is taken
- A message is sent
- A message is received

## Algorithm - Chandy Lamport

Requirements:

- Should not interfer or stop application
- Each process knows how to record it's own state
- Global state collected in a distributes manner
- Any process may trigger a snapshot

On Snashot:

- Initiater records it's own state
- Create a marker message
- foreach other processes p(j) : Send a marker to p(j) on channel c(ij)

On receiving **first** marker on C(ki) at p(i):
- P(i) records its state
- mark C(ki) as empty
- foreach other processes p(j) : Send a marker to p(j) on channel c(ij)
- foreach other processes, not i or k p(j), start recording incoming messages

On receiving **NOT first+** marker on C(ki) at p(i):
- Mark state of c(ki) as all the messages that where received since recording turned on for c (ki)

Done when all processes have received a marker, and on all other incoming channels.

```
P1 ----[a]----b----[c]------d---e-------->
               \           /     \
P2 -------------f--g------h-------\------>
                  /                \
P3 -------------[i]-----[j]---------k---->

- P1 initiates after event 'b'. record local state S1, start recording on C(21) and c(31), send markers.
- P3 Gets that marker between i and j.First marker, record state as S3, mark C13 as empty, start recording on C23, Send markers.
- P1 receives marker from P3 (between C and D). Duplicated marker, mark C(31) as empty, stop recording C(31).
- P2 receives marker from P3 (after H). First marker, record state S2. Mark C23 empty. Start recording C12. Send markers.
- P2 receives marker from P1 (after H). Duplicate stops recording C12. C12 is empty.
- P1 receives marker from P2. (after D). Duplicate stops recording C21. C21 has message (h->d).
- P2 receives marker from P3. (after J). Duplicate stops recording C23. C23 is empty.

Captured all 3 process states and one messages in flight (h->d) on C21.
```

## Consistent cuts
Events at the process/Channel that happen before the cut are  "in" the cut

A consitstent cut must obeys Casuality

## Safety & Liveness

**Liveness** = Something good will happen eventually (not guaranteed but goal)

Examples:

- At least one player will win
- The train will arrive at it's destination

**Safety** = Guarantee that something bad will (hpefully) never happen

Examples:

- An innocent person will not be jailed
- No deadlock will occur in a distributed system

Liveness AND Safety cannot be guaranteed, in an asynchronous sytem, within a time bound.