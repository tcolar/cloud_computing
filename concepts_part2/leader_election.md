# Leader election

## Ring election
- Nodes placed in a ring, similar to chord.
- Messages sent clockwise

Election round:
- If p(i) detects the current leader has failed, it starts(initiator) an election
- Election message is sent to successor through the ring, with initiator Id has `msg.Id`.
- At each node: 
- If `p.Id` == `msg.Id` -> msg.Id = p.Id -> Elected, send Elected message one lap around the ring.
- Else If `p.Id` > `msg.Id` -> msg.Id = p.Id

Worst Complexity and max time: `3 * N - 1`

That is `N-1` if initiator is succesor of new leader, plus N, for leader to see it's own ID come around 
+ N for the "elected" message to go around.

Multiple initiators is ok -> highest Id picked

Failures:

In case of failure, such as for the would be leader, the message could go around forever -> Liveness Violated !

Can't really solve even with failure detection because this is basically the conscencus problem.

## Chuby
By Google, locking system, used in BigTable, Megastore etc ...

Uses a set of replicas with an Elected Leader(master) at all time (per group)

- Potential leader try to get votes
- Each server vote once
- Server with majority of votes becomes leader, informs others.

Safe (voting quorum guarantees single quorum) and eventualy live.

- After an election, no other election for a short while
- Leader may remain leader
- If leader fails, new election takes place.


## ZooKeeper
- Used to provide safe access to config & small files
- Uses Paxos variant called Zab
- Keeps a leader elected at all times

- Each server generates a new sequence id 
- Save id in zookeeper FS (atomically) + uses 2 phase commit to insure unique ids, majority of ACK.
- Highest saved Id is Leader

Failure detection:

- Each process(p) montitors regularely the next higher Id (q)
- If p detects that q failed, and 1 was the leader, p becomes the new leader


## Bully Algorithm
- All processes know others Id's
- When a process (p) finds the coordinator has failed
- If p know it's the highest Id, sets itself the Leader and sends a coordinator msg to others
- Otherwise sends an election msg to processes with higher Id than itself
- If no answer before timeout, become leader, tell lower Id's (coordinator msg)
- Else if response received, wait for a coordinator message (if timesout, restart an election)

- When a process receives an Election message it replies OK, and starts it's own election

Worst case : N-1 * N/2 - When lowest Id detects the failure.

Liveness not guaranteed