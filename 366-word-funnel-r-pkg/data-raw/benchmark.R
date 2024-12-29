data(enable1)

seq_s <- sequential_search(enable1)
bin_s <- binary_search(enable1)
hash_s <- hashtab_search(enable1)
set_s <- set_search(enable1)

word_set <- initialize_set(enable1)

bench::mark(
  bonus("boats", seq_s),
  bonus("boats", bin_s),
  bonus("boats", hash_s),
  bonus("boats", set_s)
)

bench::mark(
  r_funnel("sleet", "lets"),
  cpp_funnel("sleet", "lets")
)

bench::mark(
  r_funnel("dragoon", "dragon"),
  cpp_funnel("dragoon", "dragon")
)

bench::mark(
  r_funnel2("princesses", set_s),
  cpp_funnel2("princesses", word_set)
)

long_words <- enable1[nchar(enable1) > 12]
system.time(hits <- vapply(long_words, pt2_bonus2, integer(1L), word_set) == 12L)
long_words[hits]


bench::mark(pt2_bonus2("preformationists", word_set))
