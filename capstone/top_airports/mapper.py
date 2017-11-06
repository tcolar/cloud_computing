#!/usr/bin/env python
 
import sys
import csv
 
for fields in csv.reader(iter(sys.stdin.readline, '')):
    origin = fields[6]
    dest = fields[14]
    print(origin)
    print("{} 1".format(dest))
