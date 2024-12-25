#include <Rcpp.h>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

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

//' @rdname funnel2
//' @export
// [[Rcpp::export]]
int cpp_funnel2(
    const std::string &x,
    const XPtr<std::unordered_set<std::string>> wordset
) {
  int depth = 1;
  for (const auto &s : make_all_funnel_words(x))
    if (wordset->count(s) == 1)
      depth = std::max(depth, cpp_funnel2(s, wordset) + 1);
  return depth;
}

std::unordered_map<size_t, std::unordered_set<std::string>>
generate_candidates(
  const std::string &s,
  const XPtr<std::unordered_set<std::string>> wordset,
  int depth
) {
  int word_len = s.size() - 1;
  std::unordered_map<size_t, std::unordered_set<std::string>> candidates;
  candidates[word_len] = make_all_funnel_words(s);
  while (word_len > 1 && depth + word_len > 10) {
    for (const auto &word : candidates[word_len--]) {
      auto tmp = make_all_funnel_words(word);
      candidates[word_len].insert(tmp.begin(), tmp.end());
    }
  }
  return candidates;
}

//' Part 2 Bonus 2
//'
//' Find the depth of a word funnel when more than one letter can be skipped in
//' a single step.
//'
//' @param x The word to test.
//' @param wordset The list of valid words as an external pointer to a C++
//'   unordered set.
//' @export
// [[Rcpp::export]]
int pt2_bonus2(
    const std::string &x,
    const XPtr<std::unordered_set<std::string>> wordset,
    int depth = 1
) {
  int max_depth = depth;
  for (const auto &[l, words] : generate_candidates(x, wordset, depth))
    for (const auto &word : words)
      if (wordset->count(word) == 1)
        max_depth = std::max(max_depth, pt2_bonus2(word, wordset, depth + 1));
  return max_depth;
}

/*** R
if (!exists("word_set")) {
  data(enable1)
  word_set <- initialize_set(enable1)
}
pt2_bonus2("preformationists", word_set)
*/
