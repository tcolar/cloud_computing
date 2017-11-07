#!/usr/bin/env python
 
import sys
import csv
 
for fields in csv.reader(iter(sys.stdin.readline, '')):
    origin = fields[11]
    if origin == 'Origin':
	continue
    dest = fields[17]
    print("{} 1".format(origin))
    print("{} 1".format(dest))
