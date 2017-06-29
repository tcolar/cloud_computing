# Outages:

Can be caused by:
- User error
- Disaster (fire, quake etc...)
- Power outage
- DDOS atttack

User error is the most common(70%) , and then it cascades from there.

Cascading caused by bugs, poor testing, bad documentation, over agressive retries (no backoffs)

AWS outage: User error, traffic shifted to low bandwidth network, Overaggressive EBS replication. Long tail of recovery
