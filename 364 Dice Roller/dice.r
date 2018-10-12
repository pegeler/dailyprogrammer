# [2018-06-18] Challenge #364 [Easy] Create a Dice Roller
# https://www.reddit.com/r/dailyprogrammer/comments/8s0cy1/20180618_challenge_364_easy_create_a_dice_roller/?st=jn2p4lyj&sh=d364b630


# Original challenge ------------------------------------------------------

# Print method to get desired output
print.dice <- function(x, ...) {
  cat(sum(x), ":", x)
}

# Define function
dice <- function(r) {
  i <- strsplit(r, "d", TRUE)[[1]]
  v <- sample.int(i[2], i[1], TRUE)
  structure(v, class = "dice")
}

# Test inputs
dice("5d12")
dice("6d4")
dice("1d2")
dice("1d8")
dice("3d6")
dice("4d20")
dice("100d100")


# Infix operator ----------------------------------------------------------

`%d%` <- function(n,m) structure(sample.int(m, n, TRUE), class = "dice")

3 %d% 6
1 %d% 4
10 %d% 2

# Now we can re-define `dice()` with infix operator.
dice <- function(r) {
  i <- strsplit(r, "d", TRUE)[[1]]
  i[1] %d% i[2]
}


dice("5d12")
dice("6d4")
dice("1d2")
dice("1d8")
dice("3d6")
dice("4d20")
dice("100d100")
