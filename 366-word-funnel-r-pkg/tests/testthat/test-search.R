context("Search functions")

test_that("Binary search works", {
  contains <- binary_search(c("cat", "cow", "donkey"))
  contains("cat") |> expect_true()
  contains("cow") |> expect_true()
  contains("donkey") |> expect_true()
  contains("bird") |> expect_false()
  contains("dog") |> expect_false()
  contains("elephant") |> expect_false()

  contains <- binary_search(c("cat"))
  contains("cat") |> expect_true()
  contains("cow") |> expect_false()
})

test_that("Set search works", {
  contains <- set_search(c("cat", "cow", "donkey"))
  contains("cat") |> expect_true()
  contains("cow") |> expect_true()
  contains("donkey") |> expect_true()
  contains("bird") |> expect_false()
})

test_that("Hashtab search works", {
  contains <- hashtab_search(c("cat", "cow", "donkey"))
  contains("cat") |> expect_true()
  contains("cow") |> expect_true()
  contains("donkey") |> expect_true()
  contains("bird") |> expect_false()
})
