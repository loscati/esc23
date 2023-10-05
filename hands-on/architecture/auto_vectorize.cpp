#pragma GCC optimize("O2", "unroll-loops", "omit-frame-pointer", "inline",     \
                     "tree-vectorize") // Optimization flags
#pragma GCC option("arch=native", "tune=native", "no-zero-upper") // Enable AVX
#pragma GCC target("avx")                                         // Enable AVX
#include <chrono>
#include <iostream>
#include <vector>

int main() {
  const int N = 200000;     // Array Size
  const int nTests = 20000; // Number of tests
  std::vector<float> a(N), b(N), c(N), result(N);
  auto now = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < N; ++i) // Data initialization
  {
    a[i] = ((float)i) + 12.2f;
    b[i] = -21.50f * ((float)i) + 0.9383f;
    c[i] = 120.33f * ((float)i) + 9.1172f;
  }
  for (int i = 0; i < nTests; ++i) {
    for (int j = 0; j < N; ++j) {
      result[j] = a[j] - b[j] + c[j] + 42 * (float)i;
    }
  }
  auto end_time = std::chrono::duration_cast<std::chrono::duration<double>>(
                      std::chrono::high_resolution_clock::now() - now)
                      .count();
  std::cout << "Time spent: " << end_time << "s" << std::endl;
  return 0;
}