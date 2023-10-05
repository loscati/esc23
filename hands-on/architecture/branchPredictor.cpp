// adapted from http://www.bnikolic.co.uk/blog/hpc-perf-branchprediction.html
#include <algorithm>
#include <iostream>
#include <vector>
#include <random>


int main()
{
  bool sorted = true;
  // generate data
  const size_t arraySize = 32768;
  std::vector<int> test(arraySize);
  std::vector<int> data(arraySize);

  std::mt19937 engine;
  std::uniform_int_distribution<> uniformDist(0,256);

  for (unsigned c = 0; c < arraySize; ++c) {
    test[c] = uniformDist(engine);
    data[c] = uniformDist(engine);
  }

  if (sorted)
    std::sort(test.begin(), test.end());

  long long sum = 0;

  for (unsigned i = 0; i < 10000; ++i) {
    sum = 0;
    for (unsigned c = 0; c < arraySize; ++c) {
      if (test[c] >= 128)
        sum += data[c];
    }
    
  }

  std::cout <<"sum " << sum <<  " sorted: " << (sorted? "yes" : "no") << std::endl;

  return 0;
}
