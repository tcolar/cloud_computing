# Time and Ordering

Clock skew, clock drift

## Christian's algorithm
P.time = t+(RTT+min2-min1)/2 (error is bounded)

The longer your round-trip time is, the more is going to be your error

## NTP
Server Tree (root is very accurate)

offset = (tr1-tr2+ts2-tr1)/2

Still have a non zero error

## Lamport Timestamps
"Causality" timestamps.

- Sending and Reciving are both events
- Causal ~= happens before
- Each process uses a counter as it's timestamp (starts at 0)
- The counter is incremented on each Send event, and the event carries that new value(v)
- On a Receive the receiving process sets it's counter to max(counter, event.v)+1
- If no Cuasal path -> concurrent events

```
P1 ---[1]---2------5--[6]--[7]-->
             \    /
P2 ---[1]-----3--4----[5]------->
```

## Vector clocks
Used in some key stores, ie: RIAK

Uses more space than Lamport Timestamps but can detect concurrent events.

- Each Process(P) keeps a Vector of Lamport Timestamps of all processes.
- Each timestamp in the vector is P's latest known timestamp for that process
- On send event P increases it's own Timestamp (at V(i)), the event carries that vector
- On receiving an event on P(i) (from P(j)): V(i)++; foeach x!=i : V(x) = max(V(x), event.v(x))

```
P1 -[a]---d--[f]-i---j----->
           \    /    \
P2 ----c----e--h------\---->
      /                \
P3 --b------[g]---------k-->

a [1,0,0]
b [0,0,1]
c [0,1,1]
d [2,0,0]
e [2,2,1]
f [3,0,0]
g [0,0,2]
h [2,3,1]
i [4,3,1]
j [5,3,1]
k [5,3,3]
```

- Causal if all the elements of one vector <= all elements of the other vector.
- Concurrent if some elements of the vector are > and some < to the other vector. 