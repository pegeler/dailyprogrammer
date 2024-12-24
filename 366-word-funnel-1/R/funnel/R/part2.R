#' Part 2 Word Funnel
#'
#' Find the maximum depth of a word funnel.
#'
#' @param x The word to test
#' @param search_func A function to check to see if a word is valid.
#' @name funnel2
#' @export
r_funnel2 <- function(x, search_func) {
  loop <- function(x, search_func, depth = 1L)
    x |>
      pt1_bonus(search_func) |>
      vapply(loop, integer(1), search_func, depth = depth + 1L) |>
      max(depth)
  loop(x, search_func)
}
