enable1_url <- 'https://raw.githubusercontent.com/dolph/dictionary/master/enable1.txt'
enable1 <- readLines(enable1_url)
usethis::use_data(enable1, overwrite = TRUE)
