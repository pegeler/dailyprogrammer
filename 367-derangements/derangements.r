#!/usr/bin/env Rscript

# Estimate D_n with error < 1/(n+1)
D_n <- function(n) factorial(n)/exp(1)

# Golf!
D=function(n)factorial(n)*sum(rep(c(1,-1),l=n+1)/sapply(0:n,factorial))

# 71 bytes. Gives precise answer (not estimate).

library(testthat)
expect_equal(D(1), 0)
expect_equal(D(2), 1)
expect_equal(D(3), 2)
expect_equal(D(4), 9)
expect_equal(D(5), 44)
