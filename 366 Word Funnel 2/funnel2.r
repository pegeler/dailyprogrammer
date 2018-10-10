# Challenge 366: Word Funnel 2
# https://www.reddit.com/r/dailyprogrammer/comments/99d24u/20180822_challenge_366_intermediate_word_funnel_2/?st=jmtz9cz9&sh=670ed704

library(XML)

enable1_url <- 'https://raw.githubusercontent.com/dolph/dictionary/master/enable1.txt'

enable1 <- readLines(enable1_url)

# Funnel2 -----------------------------------------------------------------
remove_letters <- function(i, x) {
  paste(x[-i], collapse = "")
}

get_funnel_words <- function(x, words) {

  candidates <-
    sapply(
      seq_len(nchar(x)),
      remove_letters,
      strsplit(x, character(0L))[[1]]
    )

  words[words %in% candidates]

}

proto_funnel2 <- function(target, wordlist = enable1) {

  wordlist_s <- split(wordlist, nchar(wordlist))

  char_len <- nchar(target)

  for (i in seq_len(char_len - 2L)) {

    r <- lapply(
      unique(do.call("c", if (i == 1) list(target) else r)),
      get_funnel_words,
      wordlist_s[[as.character(char_len - i)]]
    )

    if (!any(lengths(r))) {           # No results: do not increment i
      break
    } else if (char_len - i == 2L) {  # End of word list: increment i and break
      i <- i + 1
      break
    }

  }

  i

}


proto_funnel2("gnash")      # => 4
proto_funnel2("princesses") # => 9
proto_funnel2("turntables") # => 5
proto_funnel2("implosive")  # => 1
proto_funnel2("programmer") # => 2


# Funnel2 word tree generator ---------------------------------------------

addChildWords <- function(parent, words, depth) {
  childWords <- get_funnel_words(xmlGetAttr(parent, "value"), words)

  if (length(childWords))
    lapply(
      childWords,
      function(word)
        newXMLNode(
          "word",
          parent = parent,
          attrs = c(depth = depth, value = word)
        )
    )

  invisible(childWords)
}

generateWordTree <- function(target, wordlist = enable1) {

  char_len <- nchar(target)

  root <- newXMLNode(
    "wordTree",
    newXMLNode("word", attrs = c(depth = 1, value = target))
  )

  for (i in seq_len(char_len - 2L)) {

    current_depth <- getNodeSet(root, sprintf("//word[@depth='%i']", i))

    if (xmlSize(current_depth)) {

      lapply(current_depth, addChildWords, wordlist, i + 1)

    } else {

      break

    }

  }

  root

}

generateWordTree("gnash")      # => 4
generateWordTree("princesses") # => 9
generateWordTree("turntables") # => 5
generateWordTree("implosive")  # => 1
generateWordTree("programmer") # => 2

##

getWordPath <- function(leaf) {

  sapply(xmlAncestors(leaf)[-1], xmlGetAttr, "value")

}

funnel2 <- function(target, wordlist = enable1) {

  result <- generateWordTree(target, wordlist)

  max_depth <- max(xpathSApply(result, "//word", xmlGetAttr, "depth", converter = as.integer))

  leaves <- getNodeSet(result, sprintf("//word[@depth='%i']", max_depth))

  paths <- lapply(leaves, getWordPath)

  structure(
    list(target = target, tree = result, max_depth = max_depth, paths = paths),
    class = "wordFunnel"
  )

}

print.wordFunnel <- function(x, ...) {
    cat(
      "Target word is:      ", x$target, "\n",
      "Maximum path length: ", x$max_depth, "\n\n",
      "Here is a random path of maximum depth:\n  ", sep = "")

    path <- x$paths[[sample(seq_along(x$paths), 1L)]]

    cat(paste(path, collapse = " => "))
}

funnel2("gnash")      # => 4
funnel2("princesses") # => 9
funnel2("turntables") # => 5
funnel2("implosive")  # => 1
funnel2("programmer") # => 2

# Bonus -------------------------------------------------------------------
# This is slow. Around 30 mins. Will look for a faster way.
depths <- sapply(enable1[nchar(enable1) > 10L], proto_funnel2)

depths[depths ==  10L]

# complecting
#          10

funnel2("complecting")

# Bonus 2 -----------------------------------------------------------------
# Redefine `get_funnel_words` to do steps
bonus2_get_funnel_words <- function(x, words = enable1) {

  pairs <- do.call(expand.grid, lapply(seq_len(2L), function(z) seq(0, nchar(x))))
  pairs <- as.matrix(pairs[with(pairs, Var1 < Var2),])

  candidates <- apply(
    pairs,
    1,
    remove_letters,
    strsplit(x, character(0L))[[1]]
    )

  words[words %in% candidates]

}

bonus2_get_funnel_words("gnash")

bonus2_funnel2 <- function(target, wordlist = enable1) {

  char_len <- nchar(target)

  for (i in seq_len(char_len - 2L)) {

    r <- lapply(
      unique(do.call("c", if (i == 1) list(target) else r)),
      bonus2_get_funnel_words,
      wordlist
    )

    if (!any(lengths(r))) {           # No results: do not increment i
      break
    } else if (char_len - i == 2L) {  # End of word list: increment i and break
      i <- i + 1
      break
    }

  }

  i

}


library(foreach)
library(doParallel)

clust <- makeCluster(min(5L, detectCores() - 1L))
registerDoParallel(clust)

enable1_s <- split(enable1, nchar(enable1))

lengths_to_check <- which(as.integer(names(enable1_s)) >= 13)

par_time <- system.time({
  final <- foreach(i = lengths_to_check, .combine = "c", .inorder = FALSE) %dopar% {
    depths <- sapply(enable1_s[[i]], bonus2_funnel2)

    depths[depths ==  12L]

  }
})

stopCluster(clust)

final
#    preformationists contradictorinesses
#                  12                  12


# Checks ------------------------------------------------------------------

library(testthat)
library(dplyr)

# Funnel2

# Bonus

# Bonus 2
