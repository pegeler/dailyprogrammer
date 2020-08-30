ducci <- function(x) {
  len <- length(x)
  diffs <- function(x) abs(c(diff(x), x[len] - x[1]))
  match <- function(x, y) any(sapply(y, function(i) all(x == i)))
  step <- 1
  prev <- vector("list", 1000L)
  repeat {
    cat(format(x, width = 5), "\n")
    prev[[step]] <- x
    x <- diffs(x)
    step <- step + 1
    if (all(x == 0) || match(x, prev[seq_len(step-1)]))
      break
    else if (step == 1000)
      stop("Max iterations reached")
  }
  cat(format(x, width = 5), "\n")
  cat(step, "steps\n")
  invisible(step)
}

library(testthat)

expect_equal(ducci(c(0,653,1854,4063)), 24)
expect_equal(ducci(c(1, 5, 7, 9, 9)), 23)
expect_equal(ducci(c(1, 2, 1, 2, 1, 0)), 3)
expect_equal(ducci(c(10, 12, 41, 62, 31, 50)), 22)
expect_equal(ducci(c(10, 12, 41, 62, 31)), 30)
