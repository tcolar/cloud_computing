#!/usr/bin/env python
 
import sys
import csv
import os
 
for fields in csv.reader(iter(sys.stdin.readline, '')):
    date = fields[5]       
    carrier = fields[8]
    flight_num = fields[10]
    origin = fields[11]
    dest = fields[17]
    dep_time = fields[23]
    delay = fields[36]
    if delay == 'ArrDelay':
	    continue
    if len(date)==0 or len(carrier)==0 or len(flight_num)==0 or len(origin)==0 or len(dest)==0 or len(dep_time)==0 or len(delay)==0:
        continue

    # Map the flighhts by:
    # - AM/PM : Departing or Returning flight ?
    # - date(dep)
    # - Origin
    # - Destination
    if int(dep_time) < 1200:
        half = "AM"
    else:
        half = "PM"
    key = "{}_{}_{}_{}".format(half, date, origin, dest)
    print("{} {},{},{},{},{},{},{},{}".format(key, half, origin, dest, carrier, flight_num, date, dep_time, delay))
