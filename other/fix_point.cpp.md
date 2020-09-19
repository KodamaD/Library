---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: algebraic/fact_prime_faster.cpp
    title: Fast Factorization
  - icon: ':x:'
    path: graph/dinic.cpp
    title: Dinic
  - icon: ':x:'
    path: graph/scc.cpp
    title: Strongly Connected Components
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/scc.test.cpp
    title: test/scc.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/enumerate_factors_faster.test.cpp
    title: test/enumerate_factors_faster.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/enumerate_divisors_faster.test.cpp
    title: test/enumerate_divisors_faster.test.cpp
  - icon: ':x:'
    path: test/dinic.test.cpp
    title: test/dinic.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':question:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Lambda Recursion
    links: []
  bundledCode: "#line 2 \"other/fix_point.cpp\"\n\n#include <utility>\n\ntemplate\
    \ <class Func>\nstruct fix_point_impl: private Func {\n  explicit constexpr fix_point_impl(Func\
    \ &&func): Func(std::forward<Func>(func)) { }\n  template <class... Args>\n  constexpr\
    \ decltype(auto) operator () (Args &&... args) const {\n    return Func::operator()(*this,\
    \ std::forward<Args>(args)...);\n  }\n};\n\ntemplate <class Func>\nconstexpr decltype(auto)\
    \ fix_point(Func &&func) {\n  return fix_point_impl<Func>(std::forward<Func>(func));\n\
    }\n\n/**\n * @title Lambda Recursion\n */\n"
  code: "#pragma once\n\n#include <utility>\n\ntemplate <class Func>\nstruct fix_point_impl:\
    \ private Func {\n  explicit constexpr fix_point_impl(Func &&func): Func(std::forward<Func>(func))\
    \ { }\n  template <class... Args>\n  constexpr decltype(auto) operator () (Args\
    \ &&... args) const {\n    return Func::operator()(*this, std::forward<Args>(args)...);\n\
    \  }\n};\n\ntemplate <class Func>\nconstexpr decltype(auto) fix_point(Func &&func)\
    \ {\n  return fix_point_impl<Func>(std::forward<Func>(func));\n}\n\n/**\n * @title\
    \ Lambda Recursion\n */"
  dependsOn: []
  isVerificationFile: false
  path: other/fix_point.cpp
  requiredBy:
  - algebraic/fact_prime_faster.cpp
  - graph/dinic.cpp
  - graph/scc.cpp
  timestamp: '2020-08-03 12:07:15+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/scc.test.cpp
  - test/enumerate_factors_faster.test.cpp
  - test/enumerate_divisors_faster.test.cpp
  - test/dinic.test.cpp
documentation_of: other/fix_point.cpp
layout: document
redirect_from:
- /library/other/fix_point.cpp
- /library/other/fix_point.cpp.html
title: Lambda Recursion
---