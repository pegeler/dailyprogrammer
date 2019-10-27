#include <Rcpp.h>
#include <string>

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::export]]
std::string smorse_cpp(std::string word, Rcpp::StringVector morse)
{
  std::string out;
  for ( char c : word ) // requires c++11
    out += morse(c - 0x61);
  return out;
}

/*** R
morse <- c(".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
           ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
           "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..")
smorse_cpp("abc", morse)
*/
