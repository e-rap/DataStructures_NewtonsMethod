#include <algorithm>
#include <iostream>
#include <cmath>
#include "LargeInt.h"


LargeInt::LargeInt()
  : value{}
{
}

LargeInt::LargeInt(const std::string& value)
  : value{ value }
{
}

void LargeInt::add(const LargeInt& rhs)
{
  size_t length = (this->value.length() >= rhs.value.length()) ? this->value.length() : rhs.value.length();
  int carry{ 0 };

  auto left_iter = this->value.crbegin();
  auto right_iter = rhs.value.crbegin();

  LargeInt output{};

  for (size_t i{ 0 }; i < length; ++i)
  {
    int left_val{ 0 };
    int right_val{ 0 };
    if (left_iter != this->value.crend())
    {
      left_val = std::stoi(std::string{ *left_iter });
      left_iter++;
    }
    if (right_iter != rhs.value.crend())
    {
      right_val = std::stoi(std::string{ *right_iter });
      right_iter++;
    }

    left_val += carry + right_val;

    if (left_val > 9)
    {
      carry = 1;
      output.value += std::to_string(left_val)[1];
    }
    else
    {
      carry = 0;
      output.value += std::to_string(left_val);
    }
  }

  // final carry
  if (carry != 0)
  {
    output.value += "1";
  }

  std::reverse(output.value.begin(), output.value.end());
  this->value = output.value;
}

void LargeInt::subtract(const LargeInt& rhs)
{
  // TODO: Complete Definition
}

void LargeInt::multiply(const LargeInt& rhs)
{
  karatasuba_multiply(rhs);
}

void LargeInt::divide(const LargeInt& denominator)
{
  // TODO: Complete Definition
}

void LargeInt::sqrt()
{
  // TODO: Complete Definition
}

std::string LargeInt::get_value() const
{
  return value;
}

void LargeInt::karatasuba_multiply(const LargeInt& rhs, const size_t chunk_size)
{
  std::vector<IntType> lhs_chunks{ this->extract_chunks(chunk_size) };
  std::vector<IntType> rhs_chunks{ rhs.extract_chunks(chunk_size) };
  std::vector<IntType> calculation{};

  size_t length = (lhs_chunks.size() >= rhs_chunks.size()) ? lhs_chunks.size() : rhs_chunks.size();

  auto left_iter = lhs_chunks.begin();
  auto right_iter = rhs_chunks.begin();

  for (size_t i{ 0 }; i < length - 1; i += 2)
  {
    IntType left_lower{ 0 };
    IntType left_upper{ 0 };
    if (left_iter != lhs_chunks.end())
    {
      left_lower = *left_iter;
    }
    if ((left_iter + 1) != lhs_chunks.end())
    {
      left_upper = *(left_iter + 1);
      left_iter += 2;
    }

    IntType right_lower{ 0 };
    IntType right_upper{ 0 };
    if (right_iter != rhs_chunks.end())
    {
      right_lower = *right_iter;
    } 
    if ((right_iter + 1) != rhs_chunks.end())
    {
      right_upper = *(right_iter + 1);
      right_iter += 2;
    }

    IntType z2{ left_upper * right_upper };
    IntType z0{ left_lower * right_lower };
    IntType z1 = (left_upper + left_lower) * (right_upper + right_lower) - z2 - z0;
    calculation.push_back(z2 * std::pow(std::pow(base, chunk_size), 2) + z1 * std::pow(base, chunk_size) + z0);
  }
  LargeInt output{ "0" };
  size_t counter{ 0 };
  for (auto number : calculation)
  {
    LargeInt largeNum{ std::to_string(number) };
    largeNum.multiply_by_10(counter*counter);
    output.add(largeNum);
    counter += 2;
  }
  this->value = output.value;
}

std::vector<LargeInt::IntType> LargeInt::extract_chunks(size_t chunk_size) const
{
  std::vector<IntType> chunk_vector;
  size_t index{ 0 };
  size_t remainder = value.length() % chunk_size;
  if (remainder != 0)
  {
    chunk_vector.push_back(std::stoll(value.substr(index, remainder)));
    index += remainder;
  }
  while (index < value.length())
  {
    chunk_vector.push_back(std::stoll(value.substr(index, chunk_size)));
    index += chunk_size;
  }
  std::reverse(chunk_vector.begin(), chunk_vector.end());
  return chunk_vector;
}

void LargeInt::multiply_by_10(const size_t num_times)
{
  LargeInt output{};
  output.value = this->value;

  for (size_t i{ 0 }; i < num_times; ++i)
  {
    output.value.append("0");
  }
  this->value = output.value;
}
