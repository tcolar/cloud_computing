#!/usr/bin/env python

import sys

map = {}
for line in sys.stdin:
	airport = line.split()[0]
	if airport in map: 
		map[airport]+=1
	else:
		map[airport]=1

for k, v in map.items():
	print("{} {}".format(k,v))
