#include <atomic>
#include <chrono>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
int main() {
  const unsigned int numElements = 100000000;

  std::vector<int> input;
  input.reserve(numElements);

  std::random_device rd;   // a seed source for the random number engine
  std::mt19937 engine(1);  // mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> uniformDist(-5, 5);
  for (unsigned int i = 0; i < numElements; ++i)
    input.emplace_back(uniformDist(engine));

  long long int sum = 0;


  auto start = std::chrono::steady_clock::now();
  for (unsigned int i = 0; i < numElements; ++i)
    sum += input[i];

  std::chrono::duration<double> dur = std::chrono::steady_clock::now() - start;
  std::cout << "Time spent in reduction: " << dur.count() << " seconds"
            << std::endl;
  std::cout << "Sum result: " << sum << std::endl;
  return 0;
}
