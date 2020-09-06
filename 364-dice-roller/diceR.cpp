#include <Rcpp.h>
#include <string>
#include <cstdio>

//' @rdname dice
//' @export
// [[Rcpp::export]]
Rcpp::IntegerVector fast_roll(std::string r) {
  int n, faces;
  if (sscanf(r.c_str(), "%dd%d", &n, &faces) != 2
        || r.find('d') != r.rfind('d')
        || r.find_first_not_of("0123456789d") != std::string::npos)
    Rcpp::stop("Malformed request");
  return Rcpp::sample(faces, n);
}
