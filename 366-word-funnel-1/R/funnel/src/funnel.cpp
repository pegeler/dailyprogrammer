#include <Rcpp.h>
#include <string>
#include <algorithm>
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

//' @rdname funnel2
//' @export
// [[Rcpp::export]]
int cpp_funnel2(const std::string &x, const XPtr<std::unordered_set<std::string>> wordset) {
  int depth = 1;
  for (size_t i = 0, len = x.size(); i < len; i++) {
    std::string s = x.substr(0, i) + x.substr(i + 1, len - i);
    if (wordset->count(s) == 1) {
      depth = std::max(depth, cpp_funnel2(s, wordset) + 1);
    }
  }
  return depth;
}

/*** R
data(enable1)
word_set <- initialize_set(enable1)
cpp_funnel2("gnash", word_set)
*/
