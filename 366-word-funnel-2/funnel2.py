#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Sep 13 00:15:02 2020

@author: pablo
"""
from functools import cache
from functools import wraps
from itertools import combinations
from time import perf_counter
import multiprocessing as mp

import requests


def get_words() -> set[str]:
    url = 'https://raw.githubusercontent.com/dolph/dictionary/master/enable1.txt'
    with requests.get(url) as r:
        return set(r.content.decode().splitlines(False))


WORDS = get_words()


@cache
def funnel2(word: str) -> int:
    max_depth = 1
    candidates = {word[:i] + word[(i+1):] for i in range(len(word))} & WORDS
    for candidate in candidates:
        max_depth = max(funnel2(candidate) + 1, max_depth)
    return max_depth


assert funnel2("gnash") == 4
assert funnel2("princesses") == 9
assert funnel2("turntables") == 5
assert funnel2("implosive") == 1
assert funnel2("programmer") == 2


@cache
def funnel2_chain(word: str) -> list[str]:
    """
    Like `funnel2`, but rather than reporting the maximum depth, it returns
    the funneled words as a list.
    """
    test, keep = [], []
    candidates = {word[:i] + word[(i+1):] for i in range(len(word))} & WORDS
    for candidate in candidates:
        if len(test := funnel2_chain(candidate)) > len(keep):
            keep = test
    return [word, *keep]


assert len(funnel2_chain("gnash")) == 4
assert len(funnel2_chain("princesses")) == 9
assert len(funnel2_chain("turntables")) == 5
assert len(funnel2_chain("implosive")) == 1
assert len(funnel2_chain("programmer")) == 2


# =============================================================================
# Bonus 1
# =============================================================================


def time_it(func):

    @wraps(func)
    def wrapper(*args, **kwargs):
        start_time = perf_counter()
        res = func(*args, **kwargs)
        print(f'Runtime was {perf_counter() - start_time} s')
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


@cache
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


def _check(word):
    if bonus2(word) == 12:
        return word
    return None


@time_it
def run_bonus2_parallel():
    found = []
    words = (w for w in WORDS if len(w) > 12)
    with mp.Pool(mp.cpu_count()) as pool:
        for word in pool.imap_unordered(_check, words):
            if word is None:
                continue
            found.append(word)
            if len(found) == 6:
                return found


@time_it
def run_bonus2():
    found = []
    words = (w for w in WORDS if len(w) > 12)
    for word in words:
        if bonus2(word) == 12:
            found.append(word)
            if len(found) == 6:
                return found


print(run_bonus2())
## preformationists
## unrepresentativenesses
## noncooperationists
## establishmentarianisms
## nonrepresentationalisms
## contradictorinesses
## Runtime was 95.466674s
