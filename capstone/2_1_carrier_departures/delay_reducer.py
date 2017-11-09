#!/usr/bin/env python

import sys

map = {}
counts = {}

for line in sys.stdin:
	k, delay = line.split()
	if k in map:
		map[k]+=float(delay)
	else:
		map[k]=float(delay)
	if k in counts:
		counts[k]+=1
	else:
		counts[k]=1

for k, v in map.items():
	print("{0} {1:.2f}".format(k,v/counts[k]))
