## Membership

Goal : To build failure detection

overall NNTF = machine MMTF / number of machines

Once a node fail it can only restart with a new id

Each process has a list of all(or most) other non faulty processes (maybe via gossip, DHT , etc...)

list maybe strongly consistent or mostly or partial but we focus on mostly consistent here.

### Failure detection
All nodes run same process over unreliable network

- Completness : When a node fails at least one non faulty process detects it
- Accuracy : No false positives failure detections
- Speed & scaling important.

Can't guarantee 100% complete and accurate (conscensus problem)

So do 100% Completness with high accuracy (may kill a false positive - not actually failing)

Centralized heartbeat (unreliable): Each node sends heartbeat, if not received in time mark as failed.

Ring heartbeat: not safe only one or two neighbors.

All-to-all : high load, complete, but a bad node could mark all others as failed (high false positives)

### gossip membership

- Each process sends heartbeats (to n random nodes) with increasing sequence id and their table. every interval
- Each process maintains a table of other processes heartbeats (process_id : latest_known_heartbeat : local_timestamp_of_last_update)
- When receving a new message, for each entry update local table if msg.heartbeat is higher (newer), use local timestamp
- if a node hasn't updated for longer than timeout then mark it as failed, but only delete it after t_cleanup time (or could get reintroduced)

- Single heartbeat takes O(log(N) to propagate (if enough - O(N) - bandwidth)
- Takes O(N.log(N)) if only O(1) bandwidth
- What if O(k) bandwidth ? what is k ?? still O(log(N)) ? 

- if t.Fail goes up -> less false positive but longer detection time

### probalistic detection (SWIM)
- constant load and detection ttime (istead of N) -> scales well
- completness O(log(N))
- false positive still possible

- process pi use pinging every T period
- send ping to random process pj, wait for ack
- if pi received ack from pj -> done for period (T)
- if pi gets no ack frem pj before timeout -> send indirrect pings to pk via k random processes
- pi expects indirect ack before end of period
- if still no ack -> mark pj

pi state machine for each pj : active -> suspected (may ge back alive) -> failed (disseminate)  use incarnation number for state stability

trick:

whenever you pick a membership element, pick the next membership element in your list, you traverse the membership list onc e per around. 

When you reach the end of the membership list, you reorder and permute the membership list that you have.
-> 2N-1 periods at most local detection

### Dissemination
Infection style -> report membership on al the messages (ping and ack, even indirect) - gossip style

may send only "recent" messages and garbage collect after many time periods -> consistercy level