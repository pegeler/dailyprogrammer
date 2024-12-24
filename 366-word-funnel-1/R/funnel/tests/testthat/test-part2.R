context("Part 2")

data(enable1)
set_s <- set_search(enable1)
word_set <- initialize_set(enable1)

test_that("R funnel works", {
  r_funnel2("gnash", set_s) |> expect_equal(4L)
  r_funnel2("princesses", set_s) |> expect_equal(9L)
  r_funnel2("turntables", set_s) |> expect_equal(5L)
  r_funnel2("implosive", set_s) |> expect_equal(1L)
  r_funnel2("programmer", set_s) |> expect_equal(2L)
})



test_that("Rcpp funnel works", {
  cpp_funnel2("gnash", word_set) |> expect_equal(4L)
  cpp_funnel2("princesses", word_set) |> expect_equal(9L)
  cpp_funnel2("turntables", word_set) |> expect_equal(5L)
  cpp_funnel2("implosive", word_set) |> expect_equal(1L)
  cpp_funnel2("programmer", word_set) |> expect_equal(2L)
})

test_that("Bonus works", {
  long_words <- enable1[nchar(enable1) > 10]
  long_words[vapply(long_words, cpp_funnel2, integer(1), word_set) == 10] |>
    expect_equal("complecting")

  # This is faster because of early exit.
  pt2_bonus(enable1, word_set) |> expect_equal("complecting")
})

test_that("Bonus 2 works", {
})
