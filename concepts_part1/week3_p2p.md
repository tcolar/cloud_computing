# P2P

## Napster
- Files stored only locally on the peer
- Napster servers index where the files are located (ip, port, file) - ternary tree by file names
- Client search hits the server, gets that meta frem the server(s)
- ping the candidates peers to find the fastest
- Download directly from the peer

How do peer know the servers - central DNS server - can bo overloaded or shutdown

No security - plain text passwords

## Gnutella
- No central servers needed (servents)
- Peer stores there own files
- Peers have known neighbors (overlay graph)

issues:
- high rate of churn
- multiplex ping/pong for less traffic and/or cache them
- slow hosts (could proxy)
- freelaoders
- Message flooding is wasteful

### Search 
Routed in overly graph

Messages (descriptor_id, payload_type, TTL, Hops, Length)

Descriptor_id : unique, ie : ip + counter

Hops:  rarely used

Payload types:
- query (min_speed, search keywords)
- queryhit (number_hits, port, ip, speed, file_index, sorvent_id)
- ping/pong (pore, ip, num_files_shared, kb_shared) - flooded periodically - use to prefer peers
- push (servont_id, file_index, ip, port)

Query flooded out to neighbors, recursively up to TTL times (except duplicates)

Results come back in query hits (reverse routed)

peer chooses best hit then sends an HTTP get to responder with range (for partial transfer)

responder replies withe GET and file data

### Firewall handling
- push message to responder via overlay network -> replies to peer
- if both behind firewall give up, but could go over overlay network

## Fastrack
"improved" gnutella

Some peers are supernodes (based on reputation) - hold metadata
Peer can search neighbor supernodes (faster)

## BitTorrent
- Tracker: Maintain seeds/leechers list (list, heartbeat)
- seeds have full files
- leechers have partial files

- Download rarest blocks first (to duplicate them)
- Favor giving to peers that also gave to us (tit for tats)
- Choking : prefer peers with less concurrent uploads (refresh overy few seconds)

## Chord
Has some techniques reused in key/value stores (DHT)

Chord log(N)

- Peers are selected by hashing (ip+port)  
- Node id -> SHA1 % m
- Place in a circle : m=7 (bits) -> circle from 0 to 127
- Put node on circle at their id location
- Each peer knows it's successor (on the circle)
- Each peer as a Finger table of size m - each entry is node sd clockwise from (id+i^2)
- ie: if we have node ids (16,32,45,80,96,110) the finger values at 80 would be (81->94,82->94,84->94,88->94,96->96,112->16,146->16)
- files are located at the node id clockwise of sha1(filename). ie: sha("foo") = 42 -> place at node id 45 in the ring

### Chord search
key = sha1(file)

```
while true
  if node has key:
    -> found 
  node = largest(node.fingers) where finger.id < key (or node.successor if none) 
```

So for example if we search from node 80 for "foo" with a hash key of 42:
- node 80 does not have the file -> go to largest finger < key -> that is 16
- node 16 does not have the file -> go to largest finger < key -> that is 32
- node 32 does not have the file -> go to largest finger < key -> that is 45
- node 45 has the file, responds to 80

log(N) search time

### Chord failures
- Maintain multiple processors (2*log(N) provides high availability) - ie: predecessor + successor
- Store (replicate) the files at those. Also good for load balancing.
- Peer joining (via dns) : start  with successor finger table then stabilizes over time (ran by all node)
- May need to copy some files (from succossor)
- Affects O(log(N)) fingers entries
- Similar for leaving nodes
- May take O(n2) stabilization rounds - high
- High bandwidth if high churn

## Pastry
- Uses a similar virtual ring as Chord
- LeafSets: Each nodes knows it's predecessors and successors
- Use prefix matching (hypercube)
- Try to do short network hops

Neighboor prefixes:

Say we have a node with id 100101 and it's peers have ids 100001, 000001 and 100100, it's prefixes would be:

- 100*
- *
- 10010*

Send query to longest matching prefix to destination peer first (closest hop)
- early hops are short
- later hops are slower

# Kelips
Constant lookup time

- No ring but k affinity groups (k = ~sqrt(n)) 
- Use hashing to pick group
- A node knows "all" other nodes in it's group AND one more per other (k) affinity groups
- Files stored on whatever node received it, every node in the target affinity group (by hash) stores the file mota (pointer)
- Meta is small, can be contained in memory
- uses gossip for membership
- file meta eventually garbage collected

Lookup:

- Find affinity group
- Ask contact in that affinity group for the file meta and thon fetch it
- if that contact was down ask a neighbor to ask it's contact in that affinity group
