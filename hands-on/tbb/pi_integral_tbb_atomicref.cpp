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
  double sum = 0.; // Initialize sum to 0
  unsigned int num_steps = 1 << 22; // Set the number of steps to 2^22
  auto pi = 0.0; // Initialize pi to 0
  double step = 1./(double) num_steps; // Calculate the step size
  int num_threads = oneapi::tbb::info::default_concurrency(); // Get the number of threads to use
  auto start = std::chrono::steady_clock::now(); // Get the start time

  std::atomic_ref<double> sum_ref(sum); // Create an atomic reference to the sum variable

  oneapi::tbb::parallel_for(
      oneapi::tbb::blocked_range<size_t>(0, num_steps), [&](auto &r) { // Parallel loop over the range [0, num_steps)
        auto local_sum = 0.; // Initialize the local sum to 0
        for (auto i = r.begin(); i < r.end(); ++i) { // Loop over the current range
            auto x = (i+0.5)*step; // Calculate x
            local_sum += 4./(1.+x*x); // Add the current term to the local sum
        }
        sum_ref += local_sum;
      });


  auto stop = std::chrono::steady_clock::now(); // Get the stop time

  std::chrono::duration<double> dur= stop - start; // Calculate the duration
  std::cout << dur.count() << " seconds" << std::endl; // Print the duration
  pi = step * sum; // Calculate pi

  std::cout << "result: " <<  std::setprecision (15) << pi << std::endl; // Print the result
}