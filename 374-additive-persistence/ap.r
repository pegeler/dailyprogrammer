#!/usr/bin/env Rscript
# inspired by g00glen00b

sum_digits <- function(x, a = 0)
  if (x == 0) a else sum_digits(x %/% 10, a + x %% 10)
ap <- function(x, c = 0)
  if (x < 10) c else ap(sum_digits(x), c + 1)

library(testthat)

expect_equal(ap(13), 1)
expect_equal(ap(1234), 2)
expect_equal(ap(9876), 2)
expect_equal(ap(199), 3)
