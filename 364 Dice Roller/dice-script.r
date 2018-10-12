#!/usr/bin/env Rscript

# Function definitions ----------------------------------------------------
print.dice <- function(x, ...) {
  cat(sum(x), ":", x)
}

dice <- function(r) {
  i <- strsplit(r, "d", TRUE)[[1]]
  v <- sample.int(i[2], i[1], TRUE)
  structure(v, class = "dice")
}

get_user_input <- function(prompt) {
  if (interactive()) {
    readline(prompt)
  } else {
    cat("\n", prompt, sep = "")
    readLines("stdin", n = 1L)
  }
}


# Welcome message ---------------------------------------------------------

cat(rep("-", getOption("width") - 2), "\n", sep = "")
rfiglet::figlet("Dice Roller")
cat(rep("-", getOption("width") - 2), "\n", sep = "")

cat(
  "Enter the desired dice roll in the form of 'NdM', where, \n",
  "    N: Number of dice to roll",
  "    M: Number of sides to each die",
  "\nType 'quit' to quit.", sep = "\n"
)


# Main loop ---------------------------------------------------------------

repeat {

  input <- tolower(get_user_input("What's your next roll? "))

  if (input == "quit") {
    break
  } else if (!grepl("[0-9]+d[0-9]+", input)) {
    cat(
      "\nSorry, your request did not take the form of 'NdM'. Please try again.\n",
      "Type 'quit' to end the program.\n", sep = ""
    )
  } else {
    print(dice(input))
  }

}

cat("Thanks for playing!\n")
