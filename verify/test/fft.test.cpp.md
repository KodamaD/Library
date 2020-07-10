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


# :heavy_check_mark: test/fft.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/fft.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-05 19:22:30+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_F">https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_F</a>


## Depends on

* :heavy_check_mark: <a href="../../library/algebraic/fft.cpp.html">Fast Fourier Transform</a>
* :heavy_check_mark: <a href="../../library/other/bit_operation.cpp.html">other/bit_operation.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_F"

#include "../algebraic/fft.cpp"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <utility>
#include <cstdint>
#include <cstdlib>

int main() {
  std::string A, B;
  std::cin >> A >> B;
  bool negative = false;
  auto fix = [&](std::string &&S) -> std::vector<uint32_t> {
    if (S == "0") {
      std::cout << "0\n";
      std::exit(EXIT_SUCCESS);
    }
    std::reverse(S.begin(), S.end());
    if (S.back() == '-') {
      negative ^= 1;
      S.pop_back();
    }
    std::vector<uint32_t> res(S.size());
    std::transform(S.begin(), S.end(), res.begin(), [&](auto c) {
      return c - '0';
    });
    return res;
  };
  fast_fourier_transform<double> fft;
  auto C = fft.convolve(fix(std::move(A)), fix(std::move(B)));
  std::vector<char> ans;
  ans.reserve(C.size());
  uint32_t sum = 0;
  for (auto x: C) {
    sum += x;
    ans.push_back((sum % 10) + '0');
    sum /= 10;
  }
  while (sum > 0) {
    ans.push_back((sum % 10) + '0');
    sum /= 10;
  }
  if (negative) {
    ans.push_back('-');
  }
  std::reverse(ans.begin(), ans.end());
  for (auto x: ans) {
    std::cout << x;
  }
  std::cout << '\n';
  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/fft.test.cpp"

#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_F"

#line 2 "algebraic/fft.cpp"

#line 2 "other/bit_operation.cpp"

#include <cstddef>
#include <cstdint>

constexpr size_t count_zero_right(const uint64_t x) {
  return x == 0 ? 64 : __builtin_ctzll(x);
}

constexpr size_t count_zero_left(const uint64_t x) {
  return x == 0 ? 64 : __builtin_clzll(x);
}

constexpr size_t bit_width(const uint64_t x) { 
  return 64 - count_zero_left(x);
}

constexpr uint64_t most_significant_bit(const uint64_t x) {
  return x == 0 ? 0 : uint64_t(1) << (bit_width(x) - 1);
}

constexpr uint64_t least_significant_bit(const uint64_t x) {
  return x & (-x);
}

constexpr uint64_t next_power_of_two(const uint64_t x) {
  return x == 0 ? 0 : most_significant_bit(2 * x - 1);
}

constexpr uint32_t bit_reverse_32(uint32_t x) {
  constexpr uint32_t b16 = 0b00000000000000001111111111111111;
  constexpr uint32_t  b8 = 0b00000000111111110000000011111111;
  constexpr uint32_t  b4 = 0b00001111000011110000111100001111;
  constexpr uint32_t  b2 = 0b00110011001100110011001100110011;
  constexpr uint32_t  b1 = 0b01010101010101010101010101010101;
  x = ((x >> 16) & b16) | ((x & b16) << 16);
  x = ((x >>  8) &  b8) | ((x &  b8) <<  8);
  x = ((x >>  4) &  b4) | ((x &  b4) <<  4);
  x = ((x >>  2) &  b2) | ((x &  b2) <<  2);
  x = ((x >>  1) &  b1) | ((x &  b1) <<  1);
  return x;
}
#line 4 "algebraic/fft.cpp"
#include <cmath>
#line 6 "algebraic/fft.cpp"
#include <vector>
#include <utility>

template <class T>
class fast_fourier_transform {
public:
  using value_type = T;
  using size_type = size_t;
  static constexpr value_type pi = std::acos(value_type(-1.0));

  struct complex_type {
    value_type re, im;
    constexpr complex_type(value_type re_ = 0, value_type im_ = 0): re(re_), im(im_) { }
    constexpr complex_type operator + (const complex_type &rhs) const { 
      return complex_type(re + rhs.re, im + rhs.im); 
    }
    constexpr complex_type operator - (const complex_type &rhs) const { 
      return complex_type(re - rhs.re, im - rhs.im); 
    }
    constexpr complex_type operator * (const complex_type &rhs) const { 
      return complex_type(re * rhs.re - im * rhs.im, re * rhs.im + im * rhs.re); 
    }
  };

private:
  size_type M_size;
  std::vector<complex_type> M_root;

public:
  void reserve(size_type size) {
    M_size = next_power_of_two(size);
    M_root.assign(M_size + 1, complex_type());
    for (size_type i = 0; i <= M_size; ++i) {
      value_type angle = pi * value_type(2.0) / M_size * i;
      M_root[i].re = std::cos(angle);
      M_root[i].im = std::sin(angle);
    }
  }

  void transform(std::vector<complex_type> &F) const {
    size_type logn = count_zero_right(M_size);
    for (size_type i = 0; i < M_size; ++i) {
      size_type j = bit_reverse_32(i) >> (32 - logn);
      if (i < j) {
        std::swap(F[i], F[j]);
      }
    }
    size_type idx;
    complex_type first, second;
    for (size_type len = 1, bit = M_size >> 1; len < M_size; len <<= 1, bit >>= 1) {
      for (size_type k = 0; k < M_size; k += (len << 1)) {
        idx = 0;
        for (size_type i = 0; i < len; ++i) {
          first = F[i + k], second = F[(i + k) ^ len];
          F[i + k] = M_root[0] * first + M_root[idx] * second;
          F[(i + k) ^ len] = M_root[0] * first + M_root[idx + (M_size >> 1)] * second;
          idx += bit;
        }
      }
    }
  }

  void inv_transform(std::vector<complex_type> &F) const {
    size_type logn = count_zero_right(M_size);
    for (size_type i = 0; i < M_size; ++i) {
      size_type j = bit_reverse_32(i) >> (32 - logn);
      if (i < j) {
        std::swap(F[i], F[j]);
      }
    }
    size_type idx;
    complex_type first, second;
    for (size_type len = 1, bit = M_size >> 1; len < M_size; len <<= 1, bit >>= 1) {
      for (size_type k = 0; k < M_size; k += (len << 1)) {
        idx = M_size;
        for (size_type i = 0; i < len; ++i) {
          first = F[i + k], second = F[(i + k) ^ len];
          F[i + k] = M_root[0] * first + M_root[idx] * second;
          F[(i + k) ^ len] = M_root[0] * first + M_root[idx - (M_size >> 1)] * second;
          idx -= bit;
        }
      }
    }
  }

  template <class U>
  std::vector<U> convolve(const std::vector<U> &A, const std::vector<U> &B) {
    size_type res_size = A.size() + B.size() - 1;
    reserve(res_size);
    std::vector<complex_type> C(M_size), D(M_size);
    for (size_type i = 0; i < A.size(); ++i) {
      C[i].re = static_cast<value_type>(A[i]);
    }
    for (size_type i = 0; i < B.size(); ++i) {
      D[i].re = static_cast<value_type>(B[i]);
    }
    transform(C);
    transform(D);
    for (size_type i = 0; i < M_size; ++i) {
      C[i] = C[i] * D[i];
    }
    inv_transform(C);
    std::vector<U> res(res_size);
    for (size_type i = 0; i < res_size; ++i) {
      res[i] = static_cast<U>(C[i].re / M_size + value_type(0.5));
    }
    return res;
  }

};

/**
 * @title Fast Fourier Transform
 */
#line 5 "test/fft.test.cpp"

#line 7 "test/fft.test.cpp"
#include <string>
#include <iostream>
#include <algorithm>
#line 12 "test/fft.test.cpp"
#include <cstdlib>

int main() {
  std::string A, B;
  std::cin >> A >> B;
  bool negative = false;
  auto fix = [&](std::string &&S) -> std::vector<uint32_t> {
    if (S == "0") {
      std::cout << "0\n";
      std::exit(EXIT_SUCCESS);
    }
    std::reverse(S.begin(), S.end());
    if (S.back() == '-') {
      negative ^= 1;
      S.pop_back();
    }
    std::vector<uint32_t> res(S.size());
    std::transform(S.begin(), S.end(), res.begin(), [&](auto c) {
      return c - '0';
    });
    return res;
  };
  fast_fourier_transform<double> fft;
  auto C = fft.convolve(fix(std::move(A)), fix(std::move(B)));
  std::vector<char> ans;
  ans.reserve(C.size());
  uint32_t sum = 0;
  for (auto x: C) {
    sum += x;
    ans.push_back((sum % 10) + '0');
    sum /= 10;
  }
  while (sum > 0) {
    ans.push_back((sum % 10) + '0');
    sum /= 10;
  }
  if (negative) {
    ans.push_back('-');
  }
  std::reverse(ans.begin(), ans.end());
  for (auto x: ans) {
    std::cout << x;
  }
  std::cout << '\n';
  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
