#' Bonus 2
#'
#' Find all words in the `enable1` dictionary that contains 5 legal funnel words.
#'
#' @param search_func A function to check to see if a candidate word is in the
#'    a dictionary.
#' @export
bonus2 <- function(search_func) {
  qualifying_words <- enable1[nchar(enable1) >= 5L]
  candidates <- lapply(qualifying_words, bonus, search_func)
  matches <- lengths(candidates) == 5L
  qualifying_words[matches]
}
