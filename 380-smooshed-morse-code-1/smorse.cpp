#include <Rcpp.h>

// [[Rcpp::export]]
Rcpp::StringVector smorse_cpp(Rcpp::StringVector words, Rcpp::StringVector code)
{
  int n = words.size();
  Rcpp::StringVector out(n);
  out.names() = words;

  for ( int i = 0; i < n; i++ )
  {
    for ( int j = 0; j < words[i].size(); j++ )
    {
      int c = words[i][j] - 0x61;
      if ( c >= 0 && c < 26 )
        out[i] += code(c);
      else
        Rcpp::stop("Character out of bounds: '%s'", words[i][j]);
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
