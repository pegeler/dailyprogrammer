#include <Rcpp.h>
#include <unordered_set>
#include <string>
#include <vector>

using namespace Rcpp;

//' Create an external pointer to a C++ unordered set
//'
//' @param s The character vector to be used in the set.
//' @export
// [[Rcpp::export]]
XPtr<std::unordered_set<std::string>> initialize_set(const std::vector<std::string> &s) {
  std::unordered_set<std::string>* uset =
    new std::unordered_set<std::string>(s.begin(), s.end());
  XPtr<std::unordered_set<std::string>> xptr(uset, true);
  return xptr;
}

// [[Rcpp::export]]
bool set_contains(const std::string &word, XPtr<std::unordered_set<std::string>> table) {
  return table->count(word) == 1;
}

/*** R
set <- initialize_set(c("cat", "cow", "donkey"))
set_contains("cat", set)
set_contains("cow", set)
set_contains("donkey", set)
set_contains("bird", set)
*/
