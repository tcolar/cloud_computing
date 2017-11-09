#!/usr/bin/env python
 
import sys
import csv
 
for fields in csv.reader(iter(sys.stdin.readline, '')):
    origin = fields[11]
    dest = fields[17]
    delay = fields[25]
    if delay == 'DepDelay':
	continue
    if len(dest)!=0 and len(origin)!=0 and len(delay)!=0:
    	print("{}_{} {}".format(origin, dest, delay))
