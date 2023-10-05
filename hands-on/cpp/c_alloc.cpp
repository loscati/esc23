#include <cstdlib>
#include <iostream>

void do_something_with(int* p, int size);

int main()
{
  // allocate memory for 1000 int's
  int const SIZE = 1000;
  auto p = static_cast<int*>(std::malloc(SIZE * sizeof(int)));
  do_something_with(p, SIZE);
  std::free(p);
}

void do_something_with(int* p, int size)
{
  std::fill(p, p + size, 42);
}