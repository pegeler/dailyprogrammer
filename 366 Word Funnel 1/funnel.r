# Challenge 366: Word Funnel
# https://www.reddit.com/r/dailyprogrammer/comments/98ufvz/20180820_challenge_366_easy_word_funnel_1/?st=jmk1revo&sh=aa881add

# Funnel ------------------------------------------------------------------
funnel <- function(x, y) {

  # If nchar is not n - 1 then it is definitely wrong
  if (nchar(x) != nchar(y) + 1) return(FALSE)

  # Fragment each word into character vector
  strings <- strsplit(c(x,y), "")

  # Remove each character one by one and find out the resulting vector matches y
  any(
    vapply(
      seq_along(strings[[1]]),
      function(i) all(strings[[1]][-i] == strings[[2]]),
      logical(1L)
    )
  )

}

funnel("leave", "eave")     # => true
funnel("reset", "rest")     # => true
funnel("dragoon", "dragon") # => true
funnel("eave", "leave")     # => false
funnel("sleet", "lets")     # => false
funnel("skiff", "ski")      # => false


# Bonus -------------------------------------------------------------------

enable1_url <- 'https://raw.githubusercontent.com/dolph/dictionary/master/enable1.txt'

enable1 <- readLines(enable1_url)

bonus <- function(x, words = enable1) {

  # First create all candidate words that would fit the rule
  candidates <-
    sapply(
      seq_len(nchar(x)),
      function(i, x) paste(x[-i], collapse = ""),
      strsplit(x, character(0L))[[1]]
    )

  # Subset legal words based on candidates
  words[words %in% candidates]

}

bonus("dragoon")            # => ["dragon"]
bonus("boats")              # => ["oats", "bats", "bots", "boas", "boat"]
bonus("affidavit")          # => []


# Bonus 2 -----------------------------------------------------------------

bonus2 <- function(x, words) {

  out <- lapply(x, bonus, words)

  matches <- lengths(out) == 5L

  setNames(out[matches], x[matches])

}

enable1_split <- split(enable1, nchar(enable1))
lengths_to_check <- setdiff(as.integer(names(enable1_split)), c(0:4, 27:28))
all(diff(lengths_to_check) == 1L) # To ensure contiguous range

library(foreach)
library(doParallel)

clust <- makeCluster(min(5L, detectCores() - 1L))
registerDoParallel(clust)

final <- foreach(i = lengths_to_check, .combine = "c", .inorder = FALSE) %dopar% {
  bonus2(enable1_split[[as.character(i)]], enable1_split[[as.character(i - 1L)]])
}

stopCluster(clust)

str(final) # List of 28

# Checks ------------------------------------------------------------------

library(testthat)
library(dplyr)

# Funnel
funnel("leave", "eave")     %>% expect_true
funnel("reset", "rest")     %>% expect_true
funnel("dragoon", "dragon") %>% expect_true
funnel("eave", "leave")     %>% expect_false
funnel("sleet", "lets")     %>% expect_false
funnel("skiff", "ski")      %>% expect_false

# Bonus
bonus("dragoon")            %>% expect_identical("dragon")
bonus("boats") %>% sort     %>% expect_identical(sort(c("oats", "bats", "bots", "boas", "boat")))
bonus("affidavit")          %>% expect_identical(character(0L))

# Bonus 2
rubric <- c(
  "boats", "moats", "peats", "teats", "beasts", "brands", "chards",
  "charts", "clamps", "coasts", "cramps", "grains", "shoots", "skites",
  "spates", "spicks", "spikes", "spines", "tramps", "writes", "yearns",
  "drivers", "plaints", "waivers", "grippers", "rousters", "grabblers",
  "twanglers")
final %>% names %>% sort    %>% expect_identical(sort(rubric))
final %>% length            %>% expect_identical(28L)
