#include <iostream>
#include <iomanip>
#include <chrono>
#include <oneapi/tbb.h>
#include <oneapi/tbb/info.h>
#include <oneapi/tbb/parallel_for.h>
#include <oneapi/tbb/task_arena.h>
#include <atomic>

int main()
{

  const unsigned int numElements = 100000000; // Set the number of elements to 100 million
  int num_threads = oneapi::tbb::info::default_concurrency(); // Get the number of threads to use

  std::vector<int> input; // Create a vector to hold the input data
  input.reserve(numElements); // Reserve space for the input data
  std::random_device rd;   // A seed source for the random number engine
  std::mt19937 engine(1);  // Mersenne Twister engine seeded with rd()
  std::uniform_int_distribution<> uniformDist(-5, 5); // Create a uniform distribution over the range [-5, 5]
  for (unsigned int i = 0; i < numElements; ++i)
    input.emplace_back(uniformDist(engine)); // Fill the input vector with random numbers

  long long int sum = 0; // Initialize the sum to 0
  std::atomic_ref<long long int> sumAtomic(sum); // Create an atomic reference to the sum variable

  auto start = std::chrono::steady_clock::now(); // Get the start time

  oneapi::tbb::parallel_for(
      oneapi::tbb::blocked_range(input.begin(), input.end()), [&](auto &range) { // Parallel loop over the range [0, num_steps)
        auto local_sum = 0.; // Initialize the local sum to 0
        for (auto& element : range) { // Loop over the current range
          local_sum += element; // Add the current element to the local sum
        }
        // You could have also used std::accumulate to calculate the local sum:
        // local_sum = std::accumulate(range.begin(), range.end(), 0);

        // Let's now update the global sum using an atomic operation
        sumAtomic += local_sum;
      }
  ); 


  auto stop = std::chrono::steady_clock::now(); // Get the stop time

  std::chrono::duration<double> dur = stop - start; // Calculate the duration
  std::cout << dur.count() << " seconds" << std::endl; // Print the duration
  std::cout << "sum: " << sumAtomic << std::endl; // Print the sum

}
