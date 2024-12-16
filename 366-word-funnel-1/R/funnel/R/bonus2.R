#' Bonus 2
#' @export
bonus2 <- function(search_func) {
  qualifying_words <- enable1[nchar(enable1) >= 5L]
  candidates <- lapply(qualifying_words, bonus, search_func)
  matches <- lengths(candidates) == 5L
  qualifying_words[matches]
}
