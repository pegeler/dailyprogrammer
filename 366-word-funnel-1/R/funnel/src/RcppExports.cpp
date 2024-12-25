// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// cpp_funnel
bool cpp_funnel(const std::string& a, const std::string& b);
RcppExport SEXP _funnel_cpp_funnel(SEXP aSEXP, SEXP bSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type a(aSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type b(bSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_funnel(a, b));
    return rcpp_result_gen;
END_RCPP
}
// cpp_funnel2
int cpp_funnel2(const std::string& x, const XPtr<std::unordered_set<std::string>> wordset);
RcppExport SEXP _funnel_cpp_funnel2(SEXP xSEXP, SEXP wordsetSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const XPtr<std::unordered_set<std::string>> >::type wordset(wordsetSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_funnel2(x, wordset));
    return rcpp_result_gen;
END_RCPP
}
// pt2_bonus2
bool pt2_bonus2(const std::string& x, const XPtr<std::unordered_set<std::string>> wordset);
RcppExport SEXP _funnel_pt2_bonus2(SEXP xSEXP, SEXP wordsetSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const XPtr<std::unordered_set<std::string>> >::type wordset(wordsetSEXP);
    rcpp_result_gen = Rcpp::wrap(pt2_bonus2(x, wordset));
    return rcpp_result_gen;
END_RCPP
}
// initialize_set
XPtr<std::unordered_set<std::string>> initialize_set(const std::vector<std::string>& s);
RcppExport SEXP _funnel_initialize_set(SEXP sSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<std::string>& >::type s(sSEXP);
    rcpp_result_gen = Rcpp::wrap(initialize_set(s));
    return rcpp_result_gen;
END_RCPP
}
// set_contains
bool set_contains(const std::string& word, XPtr<std::unordered_set<std::string>> table);
RcppExport SEXP _funnel_set_contains(SEXP wordSEXP, SEXP tableSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type word(wordSEXP);
    Rcpp::traits::input_parameter< XPtr<std::unordered_set<std::string>> >::type table(tableSEXP);
    rcpp_result_gen = Rcpp::wrap(set_contains(word, table));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_funnel_cpp_funnel", (DL_FUNC) &_funnel_cpp_funnel, 2},
    {"_funnel_cpp_funnel2", (DL_FUNC) &_funnel_cpp_funnel2, 2},
    {"_funnel_pt2_bonus2", (DL_FUNC) &_funnel_pt2_bonus2, 2},
    {"_funnel_initialize_set", (DL_FUNC) &_funnel_initialize_set, 1},
    {"_funnel_set_contains", (DL_FUNC) &_funnel_set_contains, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_funnel(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
