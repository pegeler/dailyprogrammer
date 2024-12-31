#include <Rcpp.h>
#include <primes.h>

#include <algorithm>
#include <iterator>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace Rcpp;

//' @rdname funnel
//' @export
// [[Rcpp::export]]
bool cpp_funnel(const std::string &a, const std::string &b) {
  size_t b_len = b.size();
  if (a.size() != b_len + 1) return false;

  bool skipped = false;

  for(size_t i=0, j=0; j < b_len;) {
    if (a[i] != b[j]) {
      if (skipped) return false;
      skipped = true;
      i++;
    }
    else i++, j++;
  }

  return true;
}

std::unordered_set<std::string> make_all_funnel_words(const std::string &s) {
  if (s.size() < 2)
    return {};

  std::unordered_set<std::string> set(s.size());
  for (size_t i = 0, len = s.size(); i < len; i++) {
    set.insert(s.substr(0, i) + s.substr(i + 1, len - i));
  }

  return set;
}

//' @param wordset The enable1 list as an external pointer to a C++ unordered set.
//' @rdname funnel2
//' @export
// [[Rcpp::export]]
int cpp_funnel2(
    const std::string &x,
    const XPtr<std::unordered_set<std::string>> &wordset
) {
  int depth = 1;
  for (const auto &s : make_all_funnel_words(x))
    if (wordset->count(s) == 1)
      depth = std::max(depth, cpp_funnel2(s, wordset) + 1);
  return depth;
}

static inline size_t get_number_of_buckets(int word_len, size_t prev_size) {
  IntegerVector expected_size{word_len * static_cast<int>(prev_size)};
  return primes::next_prime(expected_size * 2).at(0);
}

std::vector<std::string> make_all_funnel_words_any_depth(
  const std::string &s,
  const std::unordered_set<std::string> *wordset,
  int depth
) {
  int word_len = s.size() - 1;
  std::vector<std::string> final;
  auto prev = make_all_funnel_words(s);
  auto pred = [wordset](const std::string &s){return wordset->count(s) == 1;};

  while (word_len > 1 && depth + word_len > 10) {
    size_t buckets = get_number_of_buckets(--word_len, prev.size());
    std::unordered_set<std::string> curr(buckets);
    for (const auto &word : prev) {
      auto tmp = make_all_funnel_words(word);
      std::move(tmp.begin(), tmp.end(), std::inserter(curr, curr.end()));
    }
    std::copy_if(prev.begin(), prev.end(), std::back_inserter(final), pred);
    prev = std::move(curr);
  }
  return final;
}

int pt2_bonus2_loop(
    const std::string &x,
    const std::unordered_set<std::string> *wordset,
    int depth = 1
) {
  int max_depth = depth;
  for (const auto &word : make_all_funnel_words_any_depth(x, wordset, depth))
    max_depth = std::max(max_depth, pt2_bonus2_loop(word, wordset, depth + 1));
  return max_depth;
}

//' Part 2 Bonus 2
//'
//' Find if the depth of a word funnel is 12 when more than one letter can be
//' skipped in a single step.
//'
//' @param x The word to test.
//' @param wordset The list of valid words as an external pointer to a C++
//'   unordered set.
//' @export
// [[Rcpp::export]]
bool pt2_bonus2(
    const std::string &x,
    const XPtr<std::unordered_set<std::string>> &wordset
) {
  return pt2_bonus2_loop(x, wordset.checked_get()) == 12;
}

/*** R
if (!exists("word_set")) {
  data(enable1)
  word_set <- initialize_set(enable1)
}
pt2_bonus2("preformationists", word_set)
*/
