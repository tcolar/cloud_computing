#!/usr/bin/env python

import sys

map = {}

for line in sys.stdin:
	idx = line.index(" ")
	k = line[:idx-1]
	v = line[idx+1:].strip("\n")
	delay = float(v.split(',')[7])
	if k in map:
		# If we have multiple flights between two destinations (same half day),
		# We only want the one with the best(least) arrival delay
		entry = map[k]
		if delay < float(entry.split(',')[7]):
			map[k] = v
	else:
		map[k] = v

for k, v in map.items():
	print(v)
