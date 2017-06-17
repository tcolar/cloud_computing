# Stream Processing
- Large ammount of data
- Need to be processed in real time

## Storm
- Libraries for many languages
- Widly used

Components:
- Tuples (key/value)
- Streams (Sequence of tuples)
- Spouts (Generates the tuple stream(s) from input data)
- Bolts (Processes stream(s) and output some other(filtered) stream(s))
- Topologies (Connect bolts, ie: pass stream to bolt)

Bolts can be filters, joins, transform etc ....

Grouping strategies can be used: shuffled, fields, all (all bolts get all tuples)

Cluster:
- Master node - Runs the Nimbus daemon :  distribute code, assign tasks, monitors
- Worker nodes - Runs on a server, nuns a supervisor, listen for work for its's machines
- Zookeeper - coordinates Nimbus and supervisor

- A tuple is failed if not fully processed within a timeout
- Each tuple : Emit, Ack or Fail
