#!/bin/bash

# uint64_t
test $(ap 13) == "1" || echo "error at $LINENO"
test $(ap 1234) == "2" || echo "error at $LINENO"
test $(ap 9876) == "2" || echo "error at $LINENO"
test $(ap 199) == "3" || echo "error at $LINENO"

# __uint128_t
test $(ap-big 13) == "1" || echo "error at $LINENO"
test $(ap-big 1234) == "2" || echo "error at $LINENO"
test $(ap-big 9876) == "2" || echo "error at $LINENO"
test $(ap-big 199) == "3" || echo "error at $LINENO"
test $(ap-big 19999999999999999999999) == "4" || echo "error at $LINENO"
