#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
StringVector make_all_seqs_13() {
  int n = 0x002000;
  StringVector out(n);

  for ( int i = 0; i < n; i++ )
  {
    for ( int j = 0; j < 13; j++ )
    {
      out[i] += ( i >> j ) & 1 ? "." : "-";
    }
  }

  return out;
}

/*** R
seqs <- make_all_seqs_13()

head(seqs)
tail(seqs)
length(seqs)
*/
