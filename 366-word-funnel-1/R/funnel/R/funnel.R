#' Word funnel
#' @param x The base word
#' @param y The candidate word
#' @returns A logical indicating if `x` can go into `y`
#' @name funnel
#' @export
r_funnel <- function(x, y) {
  # If nchar is not n - 1 then it is definitely wrong
  if (nchar(x) != nchar(y) + 1) return(FALSE)

  # Fragment each word into character vector
  strings <- strsplit(c(x,y), "")

  # Remove each character one by one and find out the resulting vector matches y
  any(
    vapply(
      seq_along(strings[[1]]),
      \(i) all(strings[[1]][-i] == strings[[2]]),
      logical(1L)
    )
  )
}
