# Paxos

## Consensus
Impossibility of Concensus in a distribute asynchronous system, so reliability never quite 100% (99.9999...)

Goal is to have all processes decide on the same value.

Common traits:
- Reliable multicast
- Membership / Failure detection
- Leader Eelection

Can be solved ina truly Suynchronous system.

Can **NOT** be solved in an asynchronous system, within a time bound.

## In synchronous systems
Processes can crash-stop, messages can be delayed, clock drift,process step time is bounded.

Can be solved within time bound.

## Paxos (simplified)
FLP proof: Can't differentiate a fully failed process from a very very slow one.

Does not solve consensus but provides Safety(consensus not vioalted) and eventual Liveness(consensus should hopefully happens eventually).

Used in ZooKeeper, Cubby etc ...

Paxos has ballot rounds:

- A unique ballot ID identifies the round
- If a new round comes in, move to it, drop old one.
- Timeouts on rounds.

A round consists of:

- Election: A leader is elected
- Bill : A values is proposed, ACK expected
- Law : Leader multicasts the value(Bill)

### Election
- Potential Leader (unelected) choses a unique BalotId (higher than any seen so far).
- Sends it to all processes
- Processes wait then reply to highest BalotId (and log it to disk for crash recovery purposes). Includes Value 'v' if it was decided in a revious round.
- If Potential Leader sees a higher BallotId, it can NOT be the leader
- If Potential leader receives a Majority (Qorum) of OK, then becomes the leader (elected).
- In case no Quorum is reached, just start another round.

### Bill
- Leader proposes a value 'v' - If a 'v' value was received from another process (decided in a previous round), use that.
- Recipients log in on disk (for crash recovery), respond OK. 

Note: Once the majority of recipients have OK'ed, the conscensus as in effect been reached even though the
leader has not made it into Law and sent it yet.

### Law
- One Leader received Qorum of OK's, let all the other processes know it's now the law. (v value) decided
- Recipients receive the value and persist it to disk.