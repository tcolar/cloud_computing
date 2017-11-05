#!/usr/bin/env python

import sys

map = {}
for airport in sys.stdin.read().splitlines():
	if airport in map: 
		map[airport]+=1
	else:
		map[airport]=1

for k, v in map.items():
	print("{} {}".format(k,v))
