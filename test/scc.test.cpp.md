---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: graph/network.cpp
    title: Network
  - icon: ':x:'
    path: other/adjust_index.cpp
    title: Index Adjustment
  - icon: ':x:'
    path: graph/scc.cpp
    title: Strongly Connected Components
  - icon: ':question:'
    path: other/fix_point.cpp
    title: Lambda Recursion
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/scc
    links:
    - https://judge.yosupo.jp/problem/scc
  bundledCode: "#line 1 \"test/scc.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/scc\"\
    \n\n#line 2 \"graph/network.cpp\"\n\n#line 2 \"other/adjust_index.cpp\"\n\n#include\
    \ <cstddef>\n\nclass adjust_index {\nprivate:\n  const size_t M_stuff, M_size;\n\
    \npublic:\n  explicit adjust_index(const size_t stuff, const size_t size): \n\
    \    M_stuff(stuff), M_size(size) \n  { }\n\n  size_t operator [] (const size_t\
    \ index) const {\n    return to_vertex(index);\n  }\n  size_t to_index(const size_t\
    \ fixed) const {\n    assert(fixed >= M_stuff);\n    assert(fixed < M_size + M_stuff);\n\
    \    return fixed - M_stuff;\n  }\n  size_t size() const {\n    return M_size;\n\
    \  }\n};\n\n/**\n * @title Index Adjustment\n */\n#line 4 \"graph/network.cpp\"\
    \n\n#line 6 \"graph/network.cpp\"\n#include <cstdint>\n#include <vector>\n#include\
    \ <numeric>\n#include <utility>\n#include <type_traits>\n#include <cassert>\n\n\
    template <class Edge>\nclass network {\npublic:\n  using vertex_type = typename\
    \ Edge::vertex_type;\n  using edge_type   = Edge;\n  using size_type   = size_t;\n\
    \nprotected:\n  std::vector<std::vector<edge_type>> M_graph;\n\npublic:\n  network()\
    \ = default;\n\n  template <bool ReturnsIndex = true>\n  typename std::enable_if<ReturnsIndex,\
    \ vertex_type>::type add_vertex() {\n    vertex_type res = M_graph.size();\n \
    \   M_graph.push_back({ });\n    return res;\n  }\n  template <bool ReturnsIndex\
    \ = true>\n  typename std::enable_if<!ReturnsIndex, void>::type add_vertex() {\n\
    \    M_graph.push_back({ });\n  }\n\n  template <bool ReturnsIndices = true>\n\
    \  typename std::enable_if<ReturnsIndices, adjust_index>::type \n  add_vertices(const\
    \ size_type size) {\n    size_type cur = M_graph.size();\n    M_graph.resize(cur\
    \ + size);\n    return adjust_index(cur, size);\n  }\n  template <bool ReturnsIndices\
    \ = true>\n  typename std::enable_if<!ReturnsIndices, void>::type \n  add_vertices(const\
    \ size_type size) {\n    size_type cur = M_graph.size();\n    M_graph.resize(cur\
    \ + size);\n  }\n  \n  void add_edge(const edge_type &edge) {\n    M_graph[edge.source].push_back(edge);\n\
    \  }\n  template <class... Args>\n  void emplace_edge(const vertex_type src, Args&&...\
    \ args) {\n    M_graph[src].emplace_back(src, std::forward<Args>(args)...);\n\
    \  }\n\n  std::vector<edge_type> &operator [] (const vertex_type vert) {\n   \
    \ assert(vert < size());\n    return M_graph[vert];\n  }\n  const std::vector<edge_type>\
    \ &operator [] (const vertex_type vert) const {\n    assert(vert < size());\n\
    \    return M_graph[vert];\n  }\n\n  size_type size() const {\n    return M_graph.size();\n\
    \  }\n  bool empty() const {\n    return M_graph.empty();\n  }\n  void clear()\
    \ {\n    M_graph.clear();\n    M_graph.shrink_to_fit();\n  }\n};\n\nclass base_edge\
    \ {\npublic:\n  using vertex_type = uint32_t;\n\n  const vertex_type source, dest;\n\
    \  explicit base_edge(const vertex_type source, const vertex_type dest): \n  \
    \  source(source), dest(dest) \n  { }\n\n  base_edge reverse() const {\n    return\
    \ base_edge(dest, source);\n  }\n};\n\ntemplate <class Flow>\nclass flow_edge:\
    \ public base_edge {\npublic:\n  using vertex_type = typename base_edge::vertex_type;\n\
    \  using flow_type   = Flow;\n\n  flow_type flow;\n  const flow_type capacity;\n\
    \  explicit flow_edge(const base_edge &edge, const flow_type capacity):\n    base_edge(edge),\
    \ flow(0), capacity(capacity)\n  { }\n\n  explicit flow_edge(const base_edge &edge,\
    \ const flow_type flow, const flow_type capacity):\n    base_edge(edge), flow(flow),\
    \ capacity(capacity)\n  { }\n  explicit flow_edge(const vertex_type source, const\
    \ vertex_type dest, const flow_type capacity):\n    base_edge(source, dest), flow(0),\
    \ capacity(capacity)\n  { }\n  explicit flow_edge(const vertex_type source, const\
    \ vertex_type dest, const flow_type flow, const flow_type capacity):\n    base_edge(source,\
    \ dest), flow(flow), capacity(capacity)\n  { }\n  flow_edge reverse() const {\n\
    \    return flow_edge(static_cast<base_edge>(*this).reverse(), capacity - flow,\
    \ capacity);\n  }\n};\n\n/**\n * @title Network\n */\n#line 2 \"graph/scc.cpp\"\
    \n\n#line 2 \"other/fix_point.cpp\"\n\n#line 4 \"other/fix_point.cpp\"\n\ntemplate\
    \ <class Func>\nstruct fix_point_impl: private Func {\n  explicit constexpr fix_point_impl(Func\
    \ &&func): Func(std::forward<Func>(func)) { }\n  template <class... Args>\n  constexpr\
    \ decltype(auto) operator () (Args &&... args) const {\n    return Func::operator()(*this,\
    \ std::forward<Args>(args)...);\n  }\n};\n\ntemplate <class Func>\nconstexpr decltype(auto)\
    \ fix_point(Func &&func) {\n  return fix_point_impl<Func>(std::forward<Func>(func));\n\
    }\n\n/**\n * @title Lambda Recursion\n */\n#line 4 \"graph/scc.cpp\"\n\n#line\
    \ 6 \"graph/scc.cpp\"\n#include <stack>\n\ntemplate <class Network>\nclass strongly_connected_components\
    \ {\npublic:\n  using network_type = Network;\n  using vertex_type  = typename\
    \ Network::vertex_type;\n  using edge_type    = typename Network::edge_type;\n\
    \  using size_type    = typename Network::size_type;\n\nprivate:\n  std::vector<std::vector<vertex_type>>\
    \ graph;\n  std::vector<std::vector<vertex_type>> revgraph;\n\npublic:\n  explicit\
    \ strongly_connected_components(const network_type &net) {\n    graph.resize(net.size());\n\
    \    revgraph.resize(net.size());\n    for (size_type src = 0; src < net.size();\
    \ ++src) {\n      for (const auto &edge: net[src]) {\n        graph[src].push_back(edge.dest);\n\
    \        revgraph[edge.dest].push_back(src);\n      }\n    }\n  }\n\n  std::vector<std::vector<vertex_type>>\
    \ decompose() const {\n    std::vector<bool> visited(graph.size());\n    std::stack<vertex_type>\
    \ topological;\n    const auto sort = fix_point([&](auto dfs, const vertex_type\
    \ u) -> void {\n      if (visited[u]) return;\n      visited[u] = true;\n    \
    \  for (const auto v: graph[u]) {\n        dfs(v);\n      }\n      topological.push(u);\n\
    \    });\n    for (vertex_type src = 0; src < graph.size(); ++src) {\n      sort(src);\n\
    \    }\n    std::vector<std::vector<vertex_type>> group;\n    const auto decompose\
    \ = fix_point([&](const auto dfs, const vertex_type u) -> void {\n      if (visited[u])\
    \ return;\n      visited[u] = true;\n      group.back().push_back(u);\n      for\
    \ (const auto v: revgraph[u]) {\n        dfs(v);\n      }\n    });\n    std::fill(visited.begin(),\
    \ visited.end(), false);\n    while (!topological.empty()) {\n      const auto\
    \ u = topological.top();\n      topological.pop();\n      if (!visited[u]) {\n\
    \        group.push_back({ });\n        decompose(u);\n      }\n    }\n    return\
    \ group;\n  }\n};\n\n/**\n * @title Strongly Connected Components\n */\n#line\
    \ 5 \"test/scc.test.cpp\"\n\n#line 7 \"test/scc.test.cpp\"\n#include <iostream>\n\
    \nint main() {\n  size_t N, M;\n  std::cin >> N >> M;\n  network<base_edge> net;\n\
    \  net.add_vertices<false>(N);\n  for (size_t i = 0; i < M; ++i) {\n    size_t\
    \ a, b;\n    std::cin >> a >> b;\n    net.emplace_edge(a, b);\n  }\n  const auto\
    \ group = strongly_connected_components(net).decompose();\n  std::cout << group.size()\
    \ << '\\n';\n  for (const auto &vec: group) {\n    std::cout << vec.size();\n\
    \    for (const auto u: vec) {\n      std::cout << ' ' << u;\n    }\n    std::cout\
    \ << '\\n';\n  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/scc\"\n\n#include \"../graph/network.cpp\"\
    \n#include \"../graph/scc.cpp\"\n\n#include <cstddef>\n#include <iostream>\n\n\
    int main() {\n  size_t N, M;\n  std::cin >> N >> M;\n  network<base_edge> net;\n\
    \  net.add_vertices<false>(N);\n  for (size_t i = 0; i < M; ++i) {\n    size_t\
    \ a, b;\n    std::cin >> a >> b;\n    net.emplace_edge(a, b);\n  }\n  const auto\
    \ group = strongly_connected_components(net).decompose();\n  std::cout << group.size()\
    \ << '\\n';\n  for (const auto &vec: group) {\n    std::cout << vec.size();\n\
    \    for (const auto u: vec) {\n      std::cout << ' ' << u;\n    }\n    std::cout\
    \ << '\\n';\n  }\n  return 0;\n}\n"
  dependsOn:
  - graph/network.cpp
  - other/adjust_index.cpp
  - graph/scc.cpp
  - other/fix_point.cpp
  isVerificationFile: true
  path: test/scc.test.cpp
  requiredBy: []
  timestamp: '2020-09-19 12:22:26+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/scc.test.cpp
layout: document
redirect_from:
- /verify/test/scc.test.cpp
- /verify/test/scc.test.cpp.html
title: test/scc.test.cpp
---