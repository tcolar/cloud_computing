## Gossip

Gooal : Reliable multicast
Nodes may crash, packets may be lost, tons of nodes
all-to-all : slow O(N)
tree : difficult to maintain, potantially O(n)

Can send gossip over UDP (loss ok)
Each node sends to b random nodes every few seconds (infection)

### Push gossip 
Randomly push to n nodes
If many messages, gossip random subset or use priority mechanism

### Pull gossip
Randomly pull from n nodes

### Analysis
- lightweight : only contact few nodes at a time
- spreads fast : log(N)0
- fault tolerant (random paths), could fail only very early (very unlikely)

Second half of Pull Gossip is faster than push : O(log(log(N)))
O(N) load on routers -> impreve by preffering own rack 9/10

## Implementations
EC2, S3, Cassandra etc ...

NNTP example (continous gossip wave)



