#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Sep 13 00:15:02 2020

@author: pablo
"""
from datetime import datetime
from itertools import combinations
import multiprocessing as mp
import requests

with requests.get('''https://raw.githubusercontent.com/dolph/dictionary/master/enable1.txt''') as r:
    WORDS = set(r.content.decode().splitlines(False))

def funnel2(word):
    max_depth = 1
    candidates = {word[:i] + word[(i+1):] for i in range(len(word))} & WORDS
    for candidate in candidates:
        max_depth = max(funnel2(candidate) + 1, max_depth)
    return max_depth

assert(funnel2("gnash") == 4)
assert(funnel2("princesses") == 9)
assert(funnel2("turntables") == 5)
assert(funnel2("implosive") == 1)
assert(funnel2("programmer") == 2)

# =============================================================================
# Bonus 1
# =============================================================================

def time_it(func):
    def wrapper(*args, **kwargs):
        start_time = datetime.now()
        res = func(*args, **kwargs)
        end_time = datetime.now()
        print("Runtime was {}s".format((end_time - start_time).total_seconds()))
        return res
    return wrapper

@time_it
def bonus1():
    for x in WORDS:
        if len(x) > 10 and funnel2(x) == 10:
            print(x)
            break

bonus1()
## complecting
## Runtime was 0.25806s

# =============================================================================
# Bonus 2
# =============================================================================

def bonus2(word, depth=1):
    max_depth = depth
    candidates = set()
    i = len(word) - 1
    while i > 1 and i + depth > 10:
        candidates.update(
            {''.join(c) for c in combinations(word, i)} & WORDS)
        i -= 1
    for candidate in candidates:
        max_depth = max(bonus2(candidate, depth + 1), max_depth)
    return max_depth

assert bonus2("preformationists") == 12

def bonus2_check(word):
    if bonus2(word) == 12:
        return word

@time_it
def run_bonus2():
    found = 0
    words = (w for w in WORDS if len(w) > 12)
    with mp.Pool(mp.cpu_count()) as pool:
        for i in pool.imap_unordered(bonus2_check, words):
            if i is not None:
                print(i)
                found += 1
                if found == 6:
                    pool.terminate()
                    break

run_bonus2()
## preformationists
## unrepresentativenesses
## noncooperationists
## establishmentarianisms
## nonrepresentationalisms
## contradictorinesses
## Runtime was 95.466674s
