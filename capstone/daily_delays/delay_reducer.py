#!/usr/bin/env python

import sys

map = {}
counts = {}
days = ['Monday','Tuesday','Wednesday','Thursday','Friday','Saturday','Sunday']

for line in sys.stdin:
	day, delay = line.split()
	if day in map:
		map[day]+=float(delay)
	else:
		map[day]=float(delay)
	if day in counts:
		counts[day]+=1
	else:
		counts[day]=1

for k, v in map.items():
	print("{0} {1:.2f}".format(days[int(k)-1],v/counts[k]))
