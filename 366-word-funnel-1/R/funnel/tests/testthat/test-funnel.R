context("Funnel")

test_that("R funnel works", {
  r_funnel("leave", "eave")     |> expect_true()
  r_funnel("reset", "rest")     |> expect_true()
  r_funnel("dragoon", "dragon") |> expect_true()
  r_funnel("eave", "leave")     |> expect_false()
  r_funnel("sleet", "lets")     |> expect_false()
  r_funnel("skiff", "ski")      |> expect_false()
})

test_that("Rcpp funnel works", {
  cpp_funnel("leave", "eave")     |> expect_true()
  cpp_funnel("reset", "rest")     |> expect_true()
  cpp_funnel("dragoon", "dragon") |> expect_true()
  cpp_funnel("eave", "leave")     |> expect_false()
  cpp_funnel("sleet", "lets")     |> expect_false()
  cpp_funnel("skiff", "ski")      |> expect_false()
})

context("Bonus")

test_that("Bonus works", {
  set_s <- set_search(enable1)
  bonus("dragoon", set_s) |> expect_identical("dragon")
  bonus("boats", set_s) |>
    setequal(c("oats", "bats", "bots", "boas", "boat")) |>
    expect_true()
  bonus("affidavit", set_s) |> expect_identical(character(0L))
})

test_that("Bonus 2 works", {
  rubric <- c(
    "boats", "moats", "peats", "teats", "beasts", "brands", "chards",
    "charts", "clamps", "coasts", "cramps", "grains", "shoots", "skites",
    "spates", "spicks", "spikes", "spines", "tramps", "writes", "yearns",
    "drivers", "plaints", "waivers", "grippers", "rousters", "grabblers",
    "twanglers")
  enable1 |> set_search() |> bonus2() |> setequal(rubric) |> expect_true()
})

context("Search functions")

test_that("Binary search works", {
  contains <- binary_search(c("cat", "cow", "donkey"))
  contains("cat") |> expect_true()
  contains("cow") |> expect_true()
  contains("donkey") |> expect_true()
  contains("bird") |> expect_false()

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
