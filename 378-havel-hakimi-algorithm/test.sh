#!/bin/bash

test $(hh 5 3 0 2 6 2 0 7 2 5) == "false" || echo "error"
test $(hh 4 2 0 1 5 0) == "false" || echo "error"
test $(hh 3 1 2 3 1 0) == "true" || echo "error"
test $(hh 16 9 9 15 9 7 9 11 17 11 4 9 12 14 14 12 17 0 3 16) == "true" || echo "error"
test $(hh 14 10 17 13 4 8 6 7 13 13 17 18 8 17 2 14 6 4 7 12) == "true" || echo "error"
test $(hh 15 18 6 13 12 4 4 14 1 6 18 2 6 16 0 9 10 7 12 3) == "false" || echo "error"
test $(hh 6 0 10 10 10 5 8 3 0 14 16 2 13 1 2 13 6 15 5 1) == "false" || echo "error"
test $(hh 2 2 0) == "false" || echo "error"
test $(hh 3 2 1) == "false" || echo "error"
test $(hh 1 1) == "true" || echo "error"
test $(hh 1) == "false" || echo "error"
test $(hh "") == "true" || echo "error"
