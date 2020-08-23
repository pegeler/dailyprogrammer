hh <- function(x) {
  x <- x[x > 0L]
  if (length(x) ==  0L)
    return(TRUE)
  x <- sort(x, decreasing = TRUE)
  n <- x[1]
  x <- x[-1]
  if (n > length(x))
    return(FALSE)

  x[seq_len(n)] <- x[seq_len(n)] - 1L
  hh(x)
}

library(testthat)
expect_false(hh(c(5, 3, 0, 2, 6, 2, 0, 7, 2, 5)))
expect_false(hh(c(4, 2, 0, 1, 5, 0)))
expect_true(hh(c(3, 1, 2, 3, 1, 0)))
expect_true(hh(c(16, 9, 9, 15, 9, 7, 9, 11, 17, 11, 4, 9, 12, 14, 14, 12, 17, 0, 3, 16)))
expect_true(hh(c(14, 10, 17, 13, 4, 8, 6, 7, 13, 13, 17, 18, 8, 17, 2, 14, 6, 4, 7, 12)))
expect_false(hh(c(15, 18, 6, 13, 12, 4, 4, 14, 1, 6, 18, 2, 6, 16, 0, 9, 10, 7, 12, 3)))
expect_false(hh(c(6, 0, 10, 10, 10, 5, 8, 3, 0, 14, 16, 2, 13, 1, 2, 13, 6, 15, 5, 1)))
expect_false(hh(c(2, 2, 0)))
expect_false(hh(c(3, 2, 1)))
expect_true(hh(c(1, 1)))
expect_false(hh(c(1)))
expect_true(hh(c()))

