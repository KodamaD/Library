---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: Heavy-Light Decomposition

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/heavy_light_decomposition.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-12 13:43:20+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/heavy_light_decomposition.test.cpp.html">test/heavy_light_decomposition.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <cstddef>
#include <vector>
#include <utility>

class heavy_light_decomposition {
public:
  using size_type = size_t;

private:
  std::vector<std::vector<size_type>> M_graph;
  std::vector<size_type> M_size, M_parent, M_head;
  size_type M_index;

  void M_calc_subtree(size_type u, size_type p) {
    M_size[u] = 1;
    for (auto v: M_graph[u]) {
      if (v != p) {
        M_calc_subtree(v, u);
        M_size[u] += M_size[v];
      }
    }
  }

  void M_decompose(size_type u, size_type p, size_type h) {
    label[u] = M_index;
    M_head[u] = h;
    M_parent[u] = p;
    ++M_index;
    size_type max = 0, heavy = -1;
    for (auto v: M_graph[u]) {
      if (v != p) {
        if (max < M_size[v]) {
          max = M_size[v];
          heavy = v;
        }
      }
    }
    if (heavy == size_type(-1)) return;
    M_decompose(heavy, u, h);
    for (auto v: M_graph[u]) {
      if (v != p && v != heavy) {
        M_decompose(v, u, v);
      }
    }
  }

public:
  std::vector<size_type> label;

  heavy_light_decomposition() { }
  explicit heavy_light_decomposition(size_type size) { initialize(size); }

  void initialize(size_type size) {
    clear();
    M_index = 0;
    M_graph.assign(size, { });
    M_size.assign(size, 0);
    M_parent.assign(size, 0);
    M_head.assign(size, 0);
    label.assign(size, 0);
  }
  void construct(size_type root = 0) {
    M_calc_subtree(root, -1);
    M_decompose(root, -1, root);
  }
  void add_edge(size_type u, size_type v) {
    M_graph[u].push_back(v);
    M_graph[v].push_back(u);
  }

  template <class Func> 
  void each_edge(size_type u, size_type v, const Func &func) const {
    while (true) {
      if (label[u] > label[v]) {
        std::swap(u, v);
      }
      if (M_head[u] == M_head[v]) {
        if (label[u] + 1 <= label[v]) {
          func(label[u] + 1, label[v]);
        }
        return;
      }
      func(label[M_head[v]], label[v]);
      v = M_parent[M_head[v]];
    }
  }

  template <class Func> 
  void each_vertex(size_type u, size_type v, const Func &func) const {
    while (true) {
      if (label[u] > label[v]) {
        std::swap(u, v);
      }
      if (M_head[u] == M_head[v]) {
        func(label[u], label[v]);
        return;
      }
      func(label[M_head[v]], label[v]);
      v = M_parent[M_head[v]];
    }
  }

  size_type lca(size_type u, size_type v) const {
    if (label[u] > label[v]) {
      std::swap(u, v);
    }
    while (label[u] <= label[v]) {
      if (M_head[u] == M_head[v]) {
        return u;
      }
      v = M_parent[M_head[v]];
    }
    return v;
  }

  size_type size() const {
    return M_graph.size();
  }
  bool empty() const {
    return M_graph.empty();
  }
  void clear() {
    M_index = 0;
    M_graph.clear();
    M_graph.shrink_to_fit();
    M_size.clear();
    M_size.shrink_to_fit();
    M_parent.clear();
    M_parent.shrink_to_fit();
    M_head.clear();
    M_head.shrink_to_fit();
    label.clear();
    label.shrink_to_fit();
  }

};

/**
 * @title Heavy-Light Decomposition
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/heavy_light_decomposition.cpp"

#include <cstddef>
#include <vector>
#include <utility>

class heavy_light_decomposition {
public:
  using size_type = size_t;

private:
  std::vector<std::vector<size_type>> M_graph;
  std::vector<size_type> M_size, M_parent, M_head;
  size_type M_index;

  void M_calc_subtree(size_type u, size_type p) {
    M_size[u] = 1;
    for (auto v: M_graph[u]) {
      if (v != p) {
        M_calc_subtree(v, u);
        M_size[u] += M_size[v];
      }
    }
  }

  void M_decompose(size_type u, size_type p, size_type h) {
    label[u] = M_index;
    M_head[u] = h;
    M_parent[u] = p;
    ++M_index;
    size_type max = 0, heavy = -1;
    for (auto v: M_graph[u]) {
      if (v != p) {
        if (max < M_size[v]) {
          max = M_size[v];
          heavy = v;
        }
      }
    }
    if (heavy == size_type(-1)) return;
    M_decompose(heavy, u, h);
    for (auto v: M_graph[u]) {
      if (v != p && v != heavy) {
        M_decompose(v, u, v);
      }
    }
  }

public:
  std::vector<size_type> label;

  heavy_light_decomposition() { }
  explicit heavy_light_decomposition(size_type size) { initialize(size); }

  void initialize(size_type size) {
    clear();
    M_index = 0;
    M_graph.assign(size, { });
    M_size.assign(size, 0);
    M_parent.assign(size, 0);
    M_head.assign(size, 0);
    label.assign(size, 0);
  }
  void construct(size_type root = 0) {
    M_calc_subtree(root, -1);
    M_decompose(root, -1, root);
  }
  void add_edge(size_type u, size_type v) {
    M_graph[u].push_back(v);
    M_graph[v].push_back(u);
  }

  template <class Func> 
  void each_edge(size_type u, size_type v, const Func &func) const {
    while (true) {
      if (label[u] > label[v]) {
        std::swap(u, v);
      }
      if (M_head[u] == M_head[v]) {
        if (label[u] + 1 <= label[v]) {
          func(label[u] + 1, label[v]);
        }
        return;
      }
      func(label[M_head[v]], label[v]);
      v = M_parent[M_head[v]];
    }
  }

  template <class Func> 
  void each_vertex(size_type u, size_type v, const Func &func) const {
    while (true) {
      if (label[u] > label[v]) {
        std::swap(u, v);
      }
      if (M_head[u] == M_head[v]) {
        func(label[u], label[v]);
        return;
      }
      func(label[M_head[v]], label[v]);
      v = M_parent[M_head[v]];
    }
  }

  size_type lca(size_type u, size_type v) const {
    if (label[u] > label[v]) {
      std::swap(u, v);
    }
    while (label[u] <= label[v]) {
      if (M_head[u] == M_head[v]) {
        return u;
      }
      v = M_parent[M_head[v]];
    }
    return v;
  }

  size_type size() const {
    return M_graph.size();
  }
  bool empty() const {
    return M_graph.empty();
  }
  void clear() {
    M_index = 0;
    M_graph.clear();
    M_graph.shrink_to_fit();
    M_size.clear();
    M_size.shrink_to_fit();
    M_parent.clear();
    M_parent.shrink_to_fit();
    M_head.clear();
    M_head.shrink_to_fit();
    label.clear();
    label.shrink_to_fit();
  }

};

/**
 * @title Heavy-Light Decomposition
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
