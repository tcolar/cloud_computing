# Grids applications

Used in biology, meteorology etc ...

ie: RAMS weather modeling

Distributed CPU intensive jobs (data of reasonable size)
Highly parallolized - across sites / data centers
Job - DAG of tasks

## Scheduling
Each site as an intra site protocol :
Allocate, schedule, monitor internally, distribute and publish files)
ie: Condor

Across site global protecol, ie: globus.
responsible to transfer files across sites (GridFTP)
allocate jobs to site (GRAM5) -> tolks to intra site
Federated (single sign-on etc ...)
