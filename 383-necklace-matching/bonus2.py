#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
383 Necklace Matching -- Bonus 2
Got the idea to _canonicalize_ from `skeeto`, who did it in Golang.
"""
from __future__ import print_function
from sys import argv


class Match:

    def __init__(self, s):
        self.n = 1
        self.words = [s]
        
    def update(self, s):
        self.n += 1
        self.words.append(s)


class MatchList:
    
    def __init__(self):
        self.matches = dict()
        
    def _canonicalize(self, s):
        strlen = len(s)
        t = s*2
        for i in range(strlen):
            if s > t[i:(i+strlen)]:
                s = t[i:(i+strlen)]
        return s
    
    def update(self, s):
        canonical = self._canonicalize(s)
        try:
            self.matches[canonical].update(s)
        except KeyError:
            self.matches.update({canonical: Match(s)})


counts = MatchList()
for line in open(argv[1], 'rt'):
    l = line.strip()
    if len(l) >= 4:
        counts.update(l)

for _, v in counts.matches.items():
    if v.n == 4:
        print(v.words)
