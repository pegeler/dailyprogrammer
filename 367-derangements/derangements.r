#!/usr/bin/env Rscript

# Estimate D_n with error < 1/(n+1)
D_n <- function(n) factorial(n)/exp(1)

# Golf!
f=factorial;D=function(n)f(n)*sum(rep(c(1,-1),l=n+1)/sapply(0:n,f))

# 71 bytes. Gives precise answer (not estimate).
# REVISED: 67 bytes.

library(testthat)
expect_equal(D(1), 0)
expect_equal(D(2), 1)
expect_equal(D(3), 2)
expect_equal(D(4), 9)
expect_equal(D(5), 44)
