# [2018-06-18] Challenge #364 [Easy] Create a Dice Roller
# https://www.reddit.com/r/dailyprogrammer/comments/8s0cy1/20180618_challenge_364_easy_create_a_dice_roller/?st=jn2p4lyj&sh=d364b630

dice <- function(roll) {
  input  <- as.integer(strsplit(roll, "d")[[1]])
  values <- as.integer(runif(input[1], 0L, input[2]) + 1)

  cat(sum(values), ":", values)

  invisible(values)
}

dice("3d6")
