# https://www.reddit.com/r/dailyprogrammer/comments/cmd1hb/20190805_challenge_380_easy_smooshed_morse_code_1/

# Load in code
morse <- scan("380-smooshed-morse-code-1/morse", what = "character", quiet = TRUE)

# Define function
smorse <- function(word) {
  chars <- strsplit(word, character(0), TRUE)[[1]]
  paste(morse[match(chars, letters)], collapse = "")
}

# Get output
sapply(c("sos", "daily", "programmer", "bits", "three"), smorse)


# golf version ------------------------------------------------------------

m <- morse

# Assuming I get `m` for free...
s=function(w)paste(m[match(el(strsplit(w,"")),letters)],collapse="") # 68 bytes

identical(s("sos"), smorse("sos"))
## [1] TRUE

# ** Bonus ** -------------------------------------------------------------

if ( !file.exists("enable1.rda") ) {
  enable1_url <- 'https://raw.githubusercontent.com/dolph/dictionary/master/enable1.txt'
  enable1 <- readLines(enable1_url)
  save(enable1, file = "enable1.rda")
} else {
  load("enable1.rda")
}

words <- sapply(enable1, smorse)

words_split <- strsplit(words, character(0), TRUE)

# For these challenges, use the `enable1` word list. It contains 172,823 words.
# If you encode them all, you would get a total of 2,499,157 dots and 1,565,081
# dashes.

# Dots
Reduce(function(x,y) x + sum(y == "."), words_split, 0)
## [1] 2499157

# Dashes
Reduce(function(x,y) x + sum(y == "-"), words_split, 0)
## [1] 1565081

# Bonus 1 -----------------------------------------------------------------
# The sequence -...-....-.--. is the code for four different words (needing,
# nervate, niding, tiling). Find the only sequence that's the code for 13
# different words.
word_freqs <- table(words)

seq_13 <- names(word_freqs[word_freqs == 13])

words[words == seq_13]
##          babe          bans         bates          bath          begs         deans
## "-....--...." "-....--...." "-....--...." "-....--...." "-....--...." "-....--...."
##         death          digs         dimes          duns         neeps          nips
## "-....--...." "-....--...." "-....--...." "-....--...." "-....--...." "-....--...."
##         tsadi
## "-....--...."

# Bonus 2 -----------------------------------------------------------------
# 'autotomous' encodes to .-..--------------..-..., which has 14 dashes in a
# row. Find the only word that has 15 dashes in a row.

grep("-{15}", words, value = TRUE)
##                bottommost
## "-...---------------...-"

# Bonus 3 -----------------------------------------------------------------
# Call a word perfectly balanced if its code has the same number of dots as
# dashes. 'counterdemonstrations' is one of two 21-letter words that's perfectly
# balanced. Find the other one.

candidates_21 <- words_split[nchar(names(words)) == 21]

names(
  candidates_21[
    vapply(
      candidates_21,
      function(x) sum(x == ".") == sum(x == "-"),
      logical(1)
    )
  ]
)
## [1] "counterdemonstrations" "overcommercialization"

# Bonus 4 -----------------------------------------------------------------
# 'protectorate' is 12 letters long and encodes to .--..-.----.-.-.----.-..--.,
# which is a palindrome (i.e. the string is the same when reversed). Find the
# only 13-letter word that encodes to a palindrome.

candidates_13 <- words_split[nchar(names(words)) == 13]

candidates_13[
  vapply(
    candidates_13,
    function(x) identical(x,x[rev(seq_along(x))]),
    logical(1)
  )
]

words[names(words) == "intransigence"]
##                  intransigence
## "..-.-.-..--......--..-.-.-.."

# Bonus 5 -----------------------------------------------------------------
# --.---.---.-- is one of five 13-character sequences that does not appear in
# the encoding of any word. Find the other four.

words_13 <- words[nchar(words) >= 13L]

all_seqs_13 <- vapply(
  0:(2**13 - 1),
  function(n) paste(ifelse(rev(intToBits(n)[1:13]), ".", "-"), collapse = ""),
  character(1)
)

all_seqs_13[
  vapply(
    all_seqs_13,
    function(i) !any(grepl(i, words_13, fixed = TRUE)),
    logical(1)
  )
]

## [1] "---.----.----" "---.---.-----" "---.---.---.-" "--.---.------" "--.---.---.--"

# Bonus 5 Parallel ----------------------------------------------------------
# install.packages("doParallel")
library(doParallel)

cluster <- makeCluster(detectCores() - 1L)

registerDoParallel(cluster)

par.time <- system.time({
  out <- foreach(
    i = 0:(2**13 - 1),
    .combine = "c",
    .inorder = FALSE,
    .multicombine = TRUE
  ) %dopar% {
    s <- paste(ifelse(rev(intToBits(i)[1:13]), ".", "-"), collapse = "")
    if ( !any(grepl(s, words_13, fixed = TRUE)) ) s
  }
})

stopCluster(cluster)

out

par.time
