#pragma once

#include <cstdint>
#include <vector>
#include <utility>

class heavy_light_decomposition {
public:
  using size_type = int32_t;

private:
  std::vector<std::vector<size_type>> M_graph;
  std::vector<size_type> M_size, M_paernt, M_head;
  size_type M_index;

  void M_calc_subtree(size_type u, size_type p) {
    M_size[u] = 1;
    for (size_type v: M_graph[u]) {
      if (v != p) {
        M_calc_subtree(v, u);
        M_size[u] += M_size[v];
      }
    }
  }

  void M_decompose(size_type u, size_type p, size_type h) {
    label[u] = M_index;
    M_head[u] = h;
    M_paernt[u] = p;
    ++M_index;
    size_type max = -1, heavy = -1;
    for (size_type v : M_graph[u]) {
      if (v != p) {
        if (max < M_size[v]) {
          max = M_size[v];
          heavy = v;
        }
      }
    }
    if (heavy == -1) {
      return;
    }
    M_decompose(heavy, u, h);
    for (size_type v : M_graph[u]) {
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
    M_graph.assign(size, { });
    M_size.assign(size, 0);
    M_paernt.assign(size, 0);
    M_head.assign(size, 0);
    label.assign(size, 0);
  }

  void add_edge(size_type u, size_type v) {
    M_graph[u].push_back(v);
    M_graph[v].push_back(u);
  }

  void build(size_type root = 0) {
    M_index = 0;
    M_calc_subtree(root, -1);
    M_decompose(root, -1, root);
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
      v = M_paernt[M_head[v]];
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
      v = M_paernt[M_head[v]];
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
      v = M_paernt[M_head[v]];
    }
    return v;
  }

};
