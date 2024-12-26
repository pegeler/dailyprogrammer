context("Part 1")

data(enable1)

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

test_that("Bonus works", {
  set_s <- set_search(enable1)
  pt1_bonus("dragoon", set_s) |> expect_identical("dragon")
  pt1_bonus("boats", set_s) |>
    setequal(c("oats", "bats", "bots", "boas", "boat")) |>
    expect_true()
  pt1_bonus("affidavit", set_s) |> expect_identical(character(0L))
})

test_that("Bonus 2 works", {
  set_s <- set_search(enable1)
  rubric <- c(
    "boats", "moats", "peats", "teats", "beasts", "brands", "chards",
    "charts", "clamps", "coasts", "cramps", "grains", "shoots", "skites",
    "spates", "spicks", "spikes", "spines", "tramps", "writes", "yearns",
    "drivers", "plaints", "waivers", "grippers", "rousters", "grabblers",
    "twanglers")
  enable1 |> pt1_bonus2(set_s) |> setequal(rubric) |> expect_true()
})
