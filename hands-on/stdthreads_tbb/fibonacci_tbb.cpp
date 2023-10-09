#include <iostream>
#include <oneapi/tbb.h>
#include <oneapi/tbb/task_group.h>


int Fib(int n) {
  if (n < 2) {
    return n;
  } else {
    int x, y;
    oneapi::tbb::task_group g;
    g.run([&] { x = Fib(n - 1); }); // spawn a task
    g.run([&] { y = Fib(n - 2); }); // spawn another task
    g.wait();                       // wait for both tasks to complete
    return x + y;
  }
}

int main() {
  std::cout << Fib(32) << std::endl;
  return 0;
}