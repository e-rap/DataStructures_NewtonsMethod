#include <iostream>
#include <vector>
#include "LargeInt.h"

int main()
{
  uintLarge_t a{};
  uintLarge_t b{};
  uintLarge_t result{};
  uintLarge_t checked_result{};

  // test a really large multiplication
  a = uintLarge_t{ "2020202020202020202020202020202020202" };
  b = uintLarge_t{ "2020202020202020202020202020202020202" };
  result = a * b;

  // correct value from wolframalpha
  checked_result = uintLarge_t{ "4081216202428323640444852566064687276726864605652484440363228242016120804" };

  std::cout << result.get_string_value() << "\n";
  std::cout << checked_result.get_string_value() << "\n";
  std::cout << "the calculated value is ";
  std::cout << ((result.get_string_value() == checked_result.get_string_value()) ? "correct" : "incorrect") << ".\n";
  return 0;
}