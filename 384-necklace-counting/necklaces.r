library(primes) # >= 1.2.0
library(testthat)

necklaces <- function(k, n) {
  factors <- prime_factors(n)[[1]]
  a <- vapply(
    seq_along(factors),
    function(i) as.integer(prod(factors[seq_len(i)])),
    integer(1)
  )
  b <- n / a
  sum(c(phi(a) * k ** b, phi(b[a != b]) * k ** a[a != b])) / n
}

expect_equal(necklaces(2, 12), 352L)
expect_equal(necklaces(3, 7), 315L)
expect_equal(necklaces(9, 4), 1665L)
expect_equal(necklaces(21, 3), 3101L)
expect_equal(necklaces(99, 2), 4950L)
