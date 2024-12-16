#' Search Functions
#'
#' Create a closure that will search a dictionary for the presence of a word.
#' @param table A character vector of dictionary words.
#' @name search_func
NULL

#' @rdname search_func
#' @export
sequential_search <- function(table) function(word) word %in% table

#' @rdname search_func
#' @export
binary_search <- function(table) {
  table <- sort(table)
  function(word) {
    lb <- 1L
    ub <- length(table)

    while (lb != ub) {
      mid <- sum(c(ub, lb) - 1L) %/% 2L + 1L
      # message("lb: ", lb, ", ub: ", ub, ", mid: ", mid)
      if (word == table[mid]) {
        return(TRUE)
      } else if (word > table[mid]) {
        lb <- mid + 1L
      } else {
        ub <- mid - 1L
      }
    }

    word == table[lb]
  }
}

#' @rdname search_func
#' @export
set_search <- function(table) {
  table <- initialize_set(table)
  function(word) set_contains(word, table)
}

# contains <- binary_search(c("cat", "cow", "donkey"))
# contains("cat")
# contains("cow")
# contains("donkey")
# contains("bird")
