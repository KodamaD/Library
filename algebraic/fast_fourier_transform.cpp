
#include <vector>
#include <cmath>
#include <utility>

namespace fast_fourier_transform {
  using dbl = double;
  constexpr dbl pi = acosl(-1.0L);

  struct complex {
    dbl re, im;
    complex(dbl re_ = 0, dbl im_ = 0): re(re_), im(im_) { }
    inline complex operator + (const complex &rhs) const { 
      return complex(re + rhs.re, im + rhs.im); 
    }
    inline complex operator - (const complex &rhs) const { 
      return complex(re - rhs.re, im - rhs.im); 
    }
    inline complex operator * (const complex &rhs) const { 
      return complex(re * rhs.re - im * rhs.im, re * rhs.im + im * rhs.re); 
    }
    inline complex conjugate() const { 
      return complex(re, -im); 
    }
  };

  int size;
  std::vector<complex> root;
  void reserve(int size_) {
    size = 1;
    while (size < size_) {
      size <<= 1;
    }
    root.assign(size, complex());
    for (int i = 0; i < size; ++i) {
      dbl angle = pi * 2.0L / size * i;
      root[i] = complex(cosl(angle), sinl(angle));
    }
  }

  void discrete_fourier_transform(std::vector<complex> &F) {
    for (int i = 0, j = 1; j + 1 < size; ++j) {
      int k = size >> 1;
      while (k > (i ^= k)) {
        k >>= 1;
      }
      if (i < j) {
        std::swap(F[i], F[j]);
      }
    }
    int idx;
    complex first, second;
    for (int len = 1, bit = (size >> 1); len < size; len <<= 1, bit >>= 1) {
      for (int k = 0; k < size; k += (len << 1)) {
        idx = 0;
        for (int i = 0; i < len; ++i) {
          first = F[i + k];
          second = F[(i + k) ^ len];
          F[i + k] = root[0] * first + root[idx] * second;
          F[(i + k) ^ len] = root[0] * first + root[idx + (size >> 1)] * second;
          idx += bit;
        }
      }
    }
  }

  void inverse_discrete_fourier_transform(std::vector<complex> &F) {
    for (int i = 0, j = 1; j + 1 < size; ++j) {
      int k = size >> 1;
      while (k > (i ^= k)) {
        k >>= 1;
      }
      if (i < j) {
        std::swap(F[i], F[j]);
      }
    }
    int idx;
    complex first, second;
    for (int len = 1, bit = (size >> 1); len < size; len <<= 1, bit >>= 1) {
      for (int k = 0; k < size; k += (len << 1)) {
        idx = 0;
        for (int i = 0; i < len; ++i) {
          first = F[i + k];
          second = F[(i + k) ^ len];
          F[i + k] = root[0].conjugate() * first + root[idx].conjugate() * second;
          F[(i + k) ^ len] = root[0].conjugate() * first + root[idx + (size >> 1)].conjugate() * second;
          idx += bit;
        }
      }
    }
  }

  template <class T>
  std::vector<T> convolve(const std::vector<T> &A, const std::vector<T> &B) {
    int res_size = A.size() + B.size() - 1;
    reserve(res_size);
    std::vector<complex> C(size), D(size);
    for (int i = 0; i < A.size(); ++i) {
      C[i].re = static_cast<dbl>(A[i]);
    }
    for (int i = 0; i < B.size(); ++i) {
      D[i].re = static_cast<dbl>(B[i]);
    }
    discrete_fourier_transform(C);
    discrete_fourier_transform(D);
    for (int i = 0; i < size; ++i) {
      C[i] = C[i] * D[i];
    }
    inverse_discrete_fourier_transform(C);
    std::vector<T> res(res_size);
    for (int i = 0; i < res_size; ++i) {
      res[i] = static_cast<T>(C[i].re / size + 0.5L);
    }
    return res;
    return std::vector<T>();
  }

};

int main() {
  return 0;
}