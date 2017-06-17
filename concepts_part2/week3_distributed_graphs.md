# Distributed Graphs

ie: Google Pregel

Graph is a network of vertex(nodes) and edges

## Graph processing
ie: Shortest path, matching, etc ...

- Works in iterations, from vertex to vertex
- Each node updates tho value and sends it to its neighbors

## Bulk synchronous parallel model
- Assign each vertex to one server (Hash or Locality based)
- Each server get a subset of vertices
- Each iteration: Gather(values) / Apply(compute) / Scatter(send)

Pregel uses:
- A master server that maintains a list of workers and monitors them, provides a UIi
- Workers : processes vertices, communicates with other workers
- Uses a distributed FS, ie: GFS, BigTable
- Temp data is stored locally

### Pregel fault tolerance
- checkpointing
- failure detection
- Recovery
 
