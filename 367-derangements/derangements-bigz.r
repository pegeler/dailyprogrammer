library(gmp)

D <- function(n) {
  x <- as.bigz(0)
  y <- as.bigz(1)
  while (n > 1) {
    op <- if (n %% 2 == 1) `-` else `+`
    x <- op(x, y)
    y <- y * n
    n <- n - 1L
  }
  x
}
