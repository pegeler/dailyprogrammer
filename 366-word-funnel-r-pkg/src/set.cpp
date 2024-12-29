#include <Rcpp.h>
#include <unordered_set>
#include <string>
#include <vector>

using namespace Rcpp;

//' Create an External Pointer to a C++ Unordered Set
//'
//' @param s The character vector to be used in the set.
//' @export
// [[Rcpp::export]]
XPtr<std::unordered_set<std::string>> initialize_set(const std::vector<std::string> &s) {
  using set_t = std::unordered_set<std::string>;
  set_t *set = new set_t(s.begin(), s.end());
  return XPtr<set_t>(set, true);
}

// [[Rcpp::export]]
bool set_contains(
    const std::string &word,
    const XPtr<std::unordered_set<std::string>> &table
) {
  return table->count(word) == 1;
}

/*** R
set <- initialize_set(c("cat", "cow", "donkey"))
set_contains("cat", set)
set_contains("cow", set)
set_contains("donkey", set)
set_contains("bird", set)
*/
