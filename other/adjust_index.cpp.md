---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: graph/network.cpp
    title: Network
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/push_relabel.test.cpp
    title: test/push_relabel.test.cpp
  - icon: ':x:'
    path: test/scc.test.cpp
    title: test/scc.test.cpp
  - icon: ':x:'
    path: test/dinic.test.cpp
    title: test/dinic.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    document_title: Index Adjustment
    links: []
  bundledCode: "#line 2 \"other/adjust_index.cpp\"\n\n#include <cstddef>\n\nclass\
    \ adjust_index {\nprivate:\n  const size_t M_stuff, M_size;\n\npublic:\n  explicit\
    \ adjust_index(const size_t stuff, const size_t size): \n    M_stuff(stuff), M_size(size)\
    \ \n  { }\n\n  size_t operator [] (const size_t index) const {\n    return to_vertex(index);\n\
    \  }\n  size_t to_index(const size_t fixed) const {\n    assert(fixed >= M_stuff);\n\
    \    assert(fixed < M_size + M_stuff);\n    return fixed - M_stuff;\n  }\n  size_t\
    \ size() const {\n    return M_size;\n  }\n};\n\n/**\n * @title Index Adjustment\n\
    \ */\n"
  code: "#pragma once\n\n#include <cstddef>\n\nclass adjust_index {\nprivate:\n  const\
    \ size_t M_stuff, M_size;\n\npublic:\n  explicit adjust_index(const size_t stuff,\
    \ const size_t size): \n    M_stuff(stuff), M_size(size) \n  { }\n\n  size_t operator\
    \ [] (const size_t index) const {\n    return to_vertex(index);\n  }\n  size_t\
    \ to_index(const size_t fixed) const {\n    assert(fixed >= M_stuff);\n    assert(fixed\
    \ < M_size + M_stuff);\n    return fixed - M_stuff;\n  }\n  size_t size() const\
    \ {\n    return M_size;\n  }\n};\n\n/**\n * @title Index Adjustment\n */"
  dependsOn: []
  isVerificationFile: false
  path: other/adjust_index.cpp
  requiredBy:
  - graph/network.cpp
  timestamp: '2020-09-19 12:22:26+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/push_relabel.test.cpp
  - test/scc.test.cpp
  - test/dinic.test.cpp
documentation_of: other/adjust_index.cpp
layout: document
redirect_from:
- /library/other/adjust_index.cpp
- /library/other/adjust_index.cpp.html
title: Index Adjustment
---