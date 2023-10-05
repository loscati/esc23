#include <memory>

char* some_api();

int main()
{
  auto* p = some_api();

  // free(p);
  // delete p;
  // delete [] p;
}


#include <cstring>

char* some_api() {
  static char s[] = "Hello, world!";
  return strstr(s, "orl");
}
