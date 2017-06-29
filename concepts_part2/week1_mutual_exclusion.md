# Mutual Exclusion
Atomic access to a resource, in a distributed env

## Central server
- Have a leader
- Leader keeps queue and a single token to access the resource
- Only one process may have the token at a time 
- Process request the token and waits until it's available
- Process releases the token back to the leader.

Safety, Liveness and Fifo ordering guaranteed

Leader is master point of failure

## Ring based
- One node at a time has the token
- the token is passed around the ring

Ie: A node must wait it's turn to get the token and use it.

Less bottleneck than a central server (not a single point of failure), but up to 0(n) delay waiting turn.

## Ricart-Agrawala's Algorithm
- Uses casuality and multicast

- p wants to access the resource, "wanted" state.
- p multicasts a request to all other processes (with Lamport TS), waits for all to reply
- Requests are granted in casual order (lamport TS), ties(casually concurrent events) are broken by process id (lower first)
- q maybe queue p's request if currently in "held" state, replies once done
- p change state to "held"
- p chnages state to "released once done"

Safe both and ordered. 0(1) delay but 0(N) bandwidth.

## Maekawa's Algorithm 
- Each process (p) is part of a voting set (V)
- Intersection of 2 voting sets must not be empty (~ quorum)
- Number of voting sets (k) >= sqrt(N)
- Each process belongs to (m) voting sets = sqrt(N) -> k*m matrix

- Each process request permission from it's voting set only
- Only one process per voting set has the permission 
- Works similarely to Ricart-Agrawala otherwise.

Safety but NOT liveness, may deadlock. Deadlock free variants exists.

 0(1) delay but 0(sqrt(N)) bandwidth.


