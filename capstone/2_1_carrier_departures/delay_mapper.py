#!/usr/bin/env python
 
import sys
import csv
 
for fields in csv.reader(iter(sys.stdin.readline, '')):
    carrier = fields[8]
    origin = fields[11]
    delay = fields[25]
    if delay == 'DepDelay':
	continue
    if len(carrier)!=0 and len(origin)!=0 and len(delay)!=0:
    	print("{}_{} {}".format(origin, carrier, delay))
