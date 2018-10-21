# Challenge 361: Tally program
# https://www.reddit.com/r/dailyprogrammer/comments/8jcffg/20180514_challenge_361_easy_tally_program/?st=jn5l3npn&sh=36844cbd

# Sample input
#   abcde
#   dbbaCEDbdAacCEAadcB
#
# Output
#   a:1, b:1, c:1, d:1, e:1
#   b:2, d:2, a:1, c:0, e:-2

challenge_input <- "EbAAdbBEaBaaBBdAccbeebaec"

sample <- c("abcde", "dbbaCEDbdAacCEAadcB")

# Custom Print Function ---------------------------------------------------

print.tally <- function(x, ...) {
  cat(paste0(names(x), ":", x), sep = ", ")
}

# Using sapply with anonymous function ------------------------------------

tally <- function(x, n_players = 5) {
  x_s <- strsplit(x,character(0))[[1]]

  scores <-
    vapply(
      seq_len(n_players),
      function(i) sum(x_s == letters[i]) - sum(x_s == LETTERS[i]),
      integer(1L)
    )

  rank_order <- order(scores, decreasing = TRUE)

  structure(
    scores[rank_order],
    names = letters[rank_order],
    class = "tally"
  )
}

tally(sample[1])
tally(sample[2])
tally(challenge_input)
## c:3, d:2, a:1, e:1, b:0

# Using table -------------------------------------------------------------

# This is much slower and harder to read but is still valid.

tally <- function(x, n_players = 5) {
  x_s <- c(
    strsplit(x,character(0))[[1]],
    letters[seq_len(n_players)], # Forcing empty entries
    LETTERS[seq_len(n_players)]  #   "      "      "
  )

  diffs <- diff(rev(table(x_s)))

  scores <- sort(diffs[names(diffs) %in% letters], decreasing = TRUE)

  structure(as.vector(scores), names = names(scores), class = "tally")
}

tally(sample[1])
tally(sample[2])
tally(challenge_input)
