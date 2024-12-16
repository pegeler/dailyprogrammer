#' Bonus Question
#'
#' Create a list of all funnel words that exist in a dictionary.
#'
#' @param x The word used to create funnel words.
#' @param search_func A function to check to see if a candidate word is in the
#'    a dictionary.
#' @export
bonus <- function(x, search_func) {
  # First create all candidate words that would fit the rule
  candidates <- vapply(
    seq_len(nchar(x)),
    \(i, x) paste(x[-i], collapse = ""),
    character(1),
    strsplit(x, character(0L))[[1]]
  ) |> unique()

  # Subset legal words based on candidates
  candidates[vapply(candidates, search_func, logical(1))]
}
