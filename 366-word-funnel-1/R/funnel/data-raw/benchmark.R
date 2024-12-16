seq_s <- sequential_search(enable1)
bin_s <- binary_search(enable1)
set_s <- set_search(enable1)

bench::mark(
  bonus("boats", seq_s),
  bonus("boats", bin_s),
  bonus("boats", set_s)
)

bench::mark(
  r_funnel("sleet", "lets"),
  cpp_funnel("sleet", "lets")
)
