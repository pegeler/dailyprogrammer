#!/usr/bin/env python3
from __future__ import print_function
import sys
from collections import Counter


dice = Counter()

for line in sys.stdin:
    val = int(line.strip())
    dice[val] += val

print(dice.most_common(1)[0][1])

