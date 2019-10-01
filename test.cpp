#include <iostream>
#include <vector>
#include "LargeInt.h"

int main()
{
  LargeInt a = { "1234567890" };
  LargeInt b = { "1234567890" };
  LargeInt result = { "1524157875019052100" };

  a.karatasuba_multiply(b, 9);
  std::cout << a.get_value() << "\n";
  std::cout << result.get_value() << "\n";
  return 0;
}