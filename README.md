# junk-code-generator
Single header utility for generating junk code at compile time using template metaprogramming

Usage:
```cpp
#include "junk_code_generator.hpp"

int main(int argc, char** argv) {
  generator<16>::generate_junk(); // generate junk

  int x = 10;
  int y = 20;
  int z;
  generate<70>::generate_junk(); // generate more junk

  std::cin >> z;
  generator<100>::generate_junk(); // generate even more junk

  if (z == (x + y)) {
    std::cout << "correct!" << std::endl;
  } else {
    std::cout << "better luck next time" << std::endl;
  }

  return 0;
}

```
