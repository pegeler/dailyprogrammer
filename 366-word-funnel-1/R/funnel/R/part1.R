#' Part 1 Word funnel
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

#' Part 1 Bonus Question
#'
#' Create a list of all funnel words that exist in a dictionary.
#'
#' @param x The word used to create funnel words.
#' @param search_func A function to check to see if a candidate word is in the
#'    a dictionary.
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
#' @param search_func A function to check to see if a candidate word is in the
#'    a dictionary.
#' @export
pt1_bonus2 <- function(search_func) {
  qualifying_words <- enable1[nchar(enable1) >= 5L]
  candidates <- lapply(qualifying_words, pt1_bonus, search_func)
  matches <- lengths(candidates) == 5L
  qualifying_words[matches]
}
