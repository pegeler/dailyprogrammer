#include <Rcpp.h>
#include <primes.h>

#include <algorithm>
#include <iterator>
#include <string>
#include <tuple>
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

/* The following function is busy and offers poor performance compared to what
 * we see in the Python version.
 *
 * Some of the complexity arises from my attempt at optimization by preventing
 * unnecessary copying of objects (hence the uses of `std::move()`). We are
 * shuffling strings into several containers, which can get expensive. Strings
 * are not trivial to move and copy, so I'm careful to tell the compiler when
 * I'm done with the contents of a container in hopes it will do the Right Thing
 * managing memory behind the scenes.
 *
 * Also, since C++ does not offer syntax for set operations such as
 * intersections like we saw in Python, we wait to do the
 * membership-in-`wordset` test until copying the strings to the final output in
 * the `std::copy_if()` call. It may have been more natural for us to express
 * this in a different step of the function or in a different way completely,
 * but the standard library tools available to us directed us toward this tack
 * as a path of least resistance. The features of the tools impact the way in
 * which we solve problems.
 *
 * There is an additional burden of creating our own predicate function for the
 * membership test. Creating a lambda function each time the function is called
 * is not ideal since we've already essentially written the same function when
 * we made `set_contains()`. However, the duplication of code is inevitable
 * because there is probably more overhead computationally and organizationally
 * to make that function useful here. We'd likely want to partially apply
 * `set_contains()` using `std::bind()`. This would create a forwarding call
 * wrapper. We could then pass the resulting callable type into the function
 * rather than passing in the set pointer used as a capture in an _ad hoc_
 * lambda generated as a local variable. There is a cost to passing
 * `std::function` types into functions too, though. The function object would
 * have to be passed by value rather than by reference in this case. Rather than
 * passing in a pointer and generating a lambda function, we might want to
 * create the lambda once and pass it around by reference. This also is not
 * possible. We can't pass a lambda around by reference when there is a capture.
 * So we run into a similar problem that we saw when trying to use `std::bind`
 * on `set_contains()` to generate a `std::function<bool (const std::string&)>`
 * object.
*/
std::vector<std::string> make_all_funnel_words_any_depth(
  const std::string &s,
  const std::unordered_set<std::string> *wordset
) {
  int word_len = s.size() - 1;
  std::vector<std::string> final;
  auto prev = make_all_funnel_words(s);
  auto pred = [wordset](const std::string &s){return wordset->count(s) == 1;};

  while (word_len > 1) {
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
    const std::unordered_set<std::string> *wordset
) {
  static std::unordered_map<std::string, int> memo(wordset->size());

  if (auto s = memo.find(x); s != memo.end())
    return s->second;

  int max_depth = 1;
  for (const auto &word : make_all_funnel_words_any_depth(x, wordset))
    max_depth = std::max(max_depth, pt2_bonus2_loop(word, wordset) + 1);

  memo[x] = max_depth;

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
