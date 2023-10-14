#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
383 Necklace Matching -- Bonus 2

There is exactly one set of four words in the enable1 word list that
all describe the same necklace. Find the four words.

Got the idea to _canonicalize_ from `skeeto`, who did it in Golang.
"""
import sys
from collections import defaultdict


def canonicalize(s):
    strlen = len(s)
    t = s * 2
    for i in range(1, strlen):
        if s > (rotated := t[i:(i + strlen)]):
            s = rotated
    return s


def find_matches(words):
    matches = defaultdict(list)
    for word in words:
        if len(canonical := canonicalize(word)) >= 4:
            matches[canonical].append(word)
    return matches


def bonus2(filename=None):
    filename = filename or 'enable1.txt'
    with open(filename, 'rt') as fh:
        matches = find_matches(x.strip() for x in fh)
    print(next(filter(lambda x: len(x) == 4, matches.values())))


if __name__ == '__main__':
    bonus2(sys.argv[1])
