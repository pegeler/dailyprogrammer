#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
383 Necklace Matching -- Bonus 2
Got the idea to _canonicalize_ from `skeeto`, who did it in Golang.
"""
from __future__ import print_function
from sys import argv


def canonicalize(s):
    strlen = len(s)
    t = s*2
    for i in range(1,strlen):
        if s > t[i:(i+strlen)]:
            s = t[i:(i+strlen)]
    return s


matches = dict()
for line in open(argv[1], 'rt'):
    l = line.strip()
    canonical = canonicalize(l)
    if len(canonical) >= 4:
        try:
            matches[canonical].append(l)
        except KeyError:
            matches.update({canonical: [l]})

for v in matches.values():
    if len(v) == 4:
        print(v)
        break
