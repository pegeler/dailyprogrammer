#include <Rcpp.h>

// [[Rcpp::export]]
Rcpp::StringVector smorse_cpp(Rcpp::StringVector words, Rcpp::StringVector code)
{
  int n = words.size();
  Rcpp::StringVector out(n);
  out.names() = words;

  for ( int i = 0; i < n; i++ ) {
    for ( int j = 0; j < words[i].size(); j++ ) {
      int c;
      if ( (c = words[i][j]) >= 'a' && c <= 'z' )
        out[i] += code[c - 'a'];
      else
        Rcpp::stop("'%c' is not a lower case alphabetic character", c);
    }
  }

  return out;
}

/*** R
morse <- c(".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
           ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
           "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..")
smorse_cpp("abc", morse)
*/
