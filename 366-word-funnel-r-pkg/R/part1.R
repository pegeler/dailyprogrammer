#' Part 1 Word funnel
#' @param a The base word
#' @param b The candidate word
#' @returns A logical indicating if `a` can go into `b`
#' @name funnel
#' @export
r_funnel <- function(a, b) {
  # If nchar is not n - 1 then it is definitely wrong
  if (nchar(a) != nchar(b) + 1) return(FALSE)

  # Fragment each word into character vector
  strings <- strsplit(c(a,b), "")

  # Remove each character one by one and find out the resulting vector matches b
  any(
    vapply(
      seq_along(strings[[1]]),
      \(i) all(strings[[1]][-i] == strings[[2]]),
      logical(1L)
    )
  )
}

#' Part 1 Bonus Question
#'
#' Create a list of all funnel words that exist in a dictionary.
#'
#' @param x The word used to create funnel words.
#' @param search_func A function to check to see if a candidate word is in the
#'    a dictionary.
#' @seealso [search_func]
#' @examples
#' \dontrun{
#' data(enable1)
#' set_search_function <- set_search(enable1)
#' pt1_bonus("dragoon", set_search_function)
#' }
#' @export
pt1_bonus <- function(x, search_func) {
  # First create all candidate words that would fit the rule
  candidates <- x |>
    nchar() |>
    seq_len() |>
    vapply(remove_letter, character(1), strsplit(x, character(0L))[[1]]) |>
    unique()

  # Subset legal words based on candidates
  candidates[vapply(candidates, search_func, logical(1))]
}

#' Part 1 Bonus 2
#'
#' Find all words in the `enable1` dictionary that contains 5 legal funnel words.
#'
#' @param table A character vector of dictionary words. (I. e., `enable1`)
#' @param search_func A function to check to see if a candidate word is in the
#'    a dictionary.
#' @export
pt1_bonus2 <- function(table, search_func) {
  qualifying_words <- table[nchar(table) >= 5L]
  candidates <- lapply(qualifying_words, pt1_bonus, search_func)
  matches <- lengths(candidates) == 5L
  qualifying_words[matches]
}
