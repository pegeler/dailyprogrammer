#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Sep 13 00:15:02 2020

@author: pablo
"""
from itertools import combinations
import multiprocessing as mp
import requests

with requests.get('''https://raw.githubusercontent.com/dolph/dictionary/master/enable1.txt''') as r:
    WORDS = set(r.content.decode().splitlines(False))

def funnel2(word):
    max_depth = 1
    candidates = set()
    for i in range(len(word)):
        candidates.add(word[:i] + word[(i+1):])
    candidates &= WORDS
    for word in candidates:
        max_depth = max(funnel2(word) + 1, max_depth)
    return max_depth

assert(funnel2("gnash") == 4)
assert(funnel2("princesses") == 9)
assert(funnel2("turntables") == 5)
assert(funnel2("implosive") == 1)
assert(funnel2("programmer") == 2)

# =============================================================================
# Bonus 1
# =============================================================================
for x in WORDS:
    if len(x) > 10 and funnel2(x) == 10:
        print(x)
        break

## complecting

# =============================================================================
# Bonus 2
# =============================================================================

def bonus2(word, depth=1):
    max_depth = depth
    candidates = set()
    for i in range(2, len(word)):
        for j in combinations(word, i):
            candidates.add(''.join(j))
    candidates &= WORDS
    for word in candidates:
        if len(word) + depth > 10:
            max_depth = max(bonus2(word, depth + 1), max_depth)
    return max_depth

assert(bonus2("preformationists") == 12)

def bonus2_check(word):
    if bonus2(word) == 12:
        return word

found = 0
pool = mp.Pool(mp.cpu_count())
for i in pool.imap_unordered(bonus2_check, [w for w in WORDS if len(w) > 12]):
    if i:
        print(i)
        found += 1
        if found == 6:
            pool.terminate()
            break
pool.close()

## preformationists
## unrepresentativenesses
## noncooperationists
## establishmentarianisms
## nonrepresentationalisms
## contradictorinesses
