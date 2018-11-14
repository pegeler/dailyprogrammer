#!/bin/bash

test -f enable1.txt || \
  wget https://raw.githubusercontent.com/dolph/dictionary/master/enable1.txt

