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

#' Part 2 Bonus
#'
#' Find the word that has a funnel depth of 10
#'
#' @param words The enable1 list as a character vector.
#' @param wordset The enable1 list as an external pointer to a C++ unordered set.
#' @export
pt2_bonus <- function(words, wordset)
    for (word in words)
      if (nchar(word) > 10L && cpp_funnel2(word, wordset) == 10L)
        return(word)
