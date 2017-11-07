#!/usr/bin/env python
 
import sys
import csv
 
for fields in csv.reader(iter(sys.stdin.readline, '')):
    day = fields[4]
    delay = fields[36]
    if delay == 'ArrDelay':
	continue
    if len(day)!=0 and len(delay)!=0:
    	print("{} {}".format(day, delay))
