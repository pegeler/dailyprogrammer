#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
380 Smooshed morse code 2

Created on Tue Sep 15 01:54:31 2020

@author: pegeler
"""
import string


MORSE = ".- -... -.-. -.. . ..-. --. .... .. .--- -.- .-.. -- -. --- .--. --.- .-. ... - ..- ...- .-- -..- -.-- --..".split()
MTOC = {m: c for m, c in zip(MORSE, string.ascii_lowercase)} # decode
CTOM = {c: m for m, c in zip(MORSE, string.ascii_lowercase)} # encode


# Challenge from #1
def smorse(string):
    out = ''
    for c in string:
        out += CTOM.get(c)
    return out


def max_len(x):
    return max(map(len, x))


def min_len(x):
    return min(map(len, x))


def smalpha(string, codes=MTOC):
    out = list()
    max_ = max_len(codes)
    i = 0
    s = ''
    while i < max_ and i < len(string):
        s += string[i]
        letter = codes.get(s)
        if letter:
            if i == len(string) - 1:
                out.append(letter)
            else:
                new_codes = codes.copy()
                del new_codes[CTOM.get(letter)]
                branches = smalpha(string[(i+1):], new_codes)
                out.extend(letter + branch for branch in branches)
        i += 1
    return out


assert("wirnbfzehatqlojpgcvusyxkmd" in smalpha(".--...-.-.-.....-.--........----.-.-..---.---.--.--.-.-....-..-...-.---..--.----.."))
assert("wzjlepdsvothqfxkbgrmyicuna" in smalpha(".----...---.-....--.-........-----....--.-..-.-..--.--...--..-.---.--..-.-...--..-"))
assert("uvfsqmjazxthbidyrkcwegponl" in smalpha("..-...-..-....--.---.---.---..-..--....-.....-..-.--.-.-.--.-..--.--..--.----..-.."))

# =============================================================================
# BONUS 1
# =============================================================================
from datetime import datetime
import requests


def time_it(func):
    def wrapper(*args, **kwargs):
        start_time = datetime.now()
        res = func(*args, **kwargs)
        end_time = datetime.now()
        print("Runtime was {}s".format((end_time - start_time).total_seconds()))
        return res
    return wrapper


@time_it
def bonus1(strings):
    if isinstance(strings, list):
        for s in strings:
            smalpha(s)
    else:
        smalpha(strings)


r = requests.get("https://gist.githubusercontent.com/cosmologicon/415be8987a24a3abd07ba1dddc3cf389/raw/9da341fe303a6f3f4922411ffdf7eba5aa3e2191/smorse2-bonus1.in")
check_codes = r.content.decode().splitlines(False)

bonus1(check_codes)
