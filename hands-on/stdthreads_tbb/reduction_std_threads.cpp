#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <utility>
#include <vector>
int main() {
  const unsigned int numElements = 100000000;

  std::vector<int> input;
  input.reserve(numElements);
  unsigned int n = 2;
  // std::thread::hardware_concurrency();
  std::vector<std::thread> v;
  std::random_device rd;   // a seed source for the random number engine
  std::mt19937 engine(1);  // mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> uniformDist(-5, 5);
  for (unsigned int i = 0; i < numElements; ++i)
    input.emplace_back(uniformDist(engine));
  // create a mutex
  std::mutex mtx;
  long long int sum = 0;
  std::atomic_ref<long long int> sumAtomic(sum);
  auto f = [&](unsigned long long firstIndex, unsigned long long lastIndex) {
    long long int mySum = 0;
    for (auto it = firstIndex; it < lastIndex; ++it) {
      mySum += input[it];
    }
    // std::lock_guard<std::mutex> lock(mtx);
    // sum+= mySum;
    sumAtomic += mySum;
  };

  auto start = std::chrono::steady_clock::now();
  for (int i = 0; i < n; ++i) {
    auto myFirstIndex = i * numElements / n;
    auto myLastIndex = (i + 1) * numElements / n;
    v.emplace_back(f, myFirstIndex, myLastIndex);
  }

  for (auto &t : v) {
    t.join();
  }
  std::chrono::duration<double> dur = std::chrono::steady_clock::now() - start;
  std::cout << "Time spent in reduction: " << dur.count() << " seconds"
            << std::endl;
  std::cout << "Sum result: " << sum << std::endl;
  return 0;
}
