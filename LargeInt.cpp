#include <algorithm>
#include <iostream>
#include <cmath>
#include "LargeInt.h"


uintLarge_t::uintLarge_t()
  : value{}
{
}

uintLarge_t::uintLarge_t(const std::string& value)
  : value{ value }
{
}

uintLarge_t uintLarge_t::add(const uintLarge_t& lhs, const uintLarge_t& rhs)
{
  uintLarge_t output{};
  uintLarge_t temp_lhs{ lhs };
  uintLarge_t temp_rhs{ rhs };
  match_size(temp_lhs, temp_rhs);
  match_size(output, temp_rhs);

  int carry{ 0 };
  for (size_t j{ 0 }; j < temp_lhs.value.size(); ++j)
  {
    size_t i{ (temp_lhs.value.size() - 1) - j };
    int left_val{ temp_lhs.get_digit_value(i) };
    int right_val{ temp_rhs.get_digit_value(i) };

    left_val += carry + right_val;
    carry = 0;

    if (left_val > 9)
    {
      carry = 1;
      left_val -= 10;
    }
    output.set_digit_value(left_val, i);
  }
  // final carry bit
  if (carry != 0)
  {
    output.value.insert(0, 1, '1');
  }
  return output;
}

uintLarge_t uintLarge_t::subtract(const uintLarge_t& lhs, const uintLarge_t& rhs)
{
  uintLarge_t output{};
  uintLarge_t temp_lhs{ lhs };
  uintLarge_t temp_rhs{ rhs };
  match_size(temp_lhs, temp_rhs);
  match_size(output, temp_rhs);
  for (size_t j{ 0 }; j < temp_lhs.value.size(); ++j)
  {
    size_t i{ (temp_lhs.value.size() - 1) - j };
    int left_value{ temp_lhs.get_digit_value(i) };
    int right_value{ temp_rhs.get_digit_value(i) };
    int result = left_value - right_value;
    if (result < 0)
    {
      size_t k = 1;
      while (temp_lhs.get_digit_value(i - k) == 0)
      {
        temp_lhs.set_digit_value(9, i - k);
        ++k;
      }
      temp_lhs.set_digit_value(temp_lhs.get_digit_value(i - k) - 1, i - k);
      result = result + 10;
    }
    output.set_digit_value(result, i);
  }
  return output;
}

uintLarge_t uintLarge_t::multiply(const uintLarge_t& lhs, const uintLarge_t& rhs)
{
  return karatasuba_multiply(lhs, rhs);
}

uintLarge_t uintLarge_t::divide(const uintLarge_t& numerator, const uintLarge_t& denominator, size_t digits_of_precision)
{
  // TODO: Complete
  return uintLarge_t();
}

uintLarge_t uintLarge_t::sqrt(const uintLarge_t& input, size_t digits_of_precision)
{
  // TODO: Complete
  return uintLarge_t();
}

std::string uintLarge_t::get_string_value() const
{
  std::string output_value = this->value;
  if (output_value.empty())
  {
    output_value = std::string{ "0" };
  }
  else
  {
    output_value.erase(0, std::min(output_value.find_first_not_of('0'), output_value.size() - 1));
  }
  return output_value;
}

uintLarge_t uintLarge_t::operator+(const uintLarge_t& other)
{
  return add(*this, other);
}

uintLarge_t uintLarge_t::operator-(const uintLarge_t& other)
{
  return subtract(*this, other);
}

uintLarge_t uintLarge_t::operator*(const uintLarge_t& other)
{
  return multiply(*this, other);
}

uintLarge_t uintLarge_t::karatasuba_multiply(const uintLarge_t& lhs, const uintLarge_t& rhs, const size_t chunk_size)
{
  uintLarge_t ret_value{};
  uintLarge_t temp_lhs{ lhs };
  uintLarge_t temp_rhs{ rhs };
  match_size(temp_lhs, temp_rhs);

  if (temp_lhs.value.size() > chunk_size)
  {
    // cut each input number into two halfs
    auto [left_upper, left_lower] = temp_lhs.cut_in_half();
    auto [right_upper, right_lower] = temp_rhs.cut_in_half();

    // perform karatasuba multiplication recurively
    uintLarge_t z2{ left_upper * right_upper };
    uintLarge_t z0{ left_lower * right_lower };
    uintLarge_t z1{ (left_lower + left_upper) * (right_lower + right_upper) - z2 - z0 };

    size_t shift_size = left_lower.value.size();
    ret_value = add(add(multiply_by_10(multiply_by_10(z2, shift_size), shift_size), multiply_by_10(z1, shift_size)), z0);
  }
  else
  {
    // Perform normal multiplation (less than default_chunk_size)
    IntType lhs{ std::stoll(temp_lhs.value) };
    IntType rhs{ std::stoll(temp_rhs.value) };
    ret_value = uintLarge_t(std::to_string(lhs * rhs));
  }
  return ret_value;
}

int uintLarge_t::get_digit_value(size_t index) const
{
  return std::stoi(std::string{ this->value[index] });
}
void uintLarge_t::set_digit_value(int value, size_t index)
{
  std::string str_val = std::to_string(value);
  this->value[index] = str_val[str_val.size() - 1];
}

std::pair<uintLarge_t, uintLarge_t> uintLarge_t::cut_in_half() const
{
  std::pair<uintLarge_t, uintLarge_t> output{};
  size_t half_size = value.length() / 2;
  if (half_size > default_chunk_size * 2)
  {
    uintLarge_t upper{ value.substr(0,half_size) };
    uintLarge_t lower{ value.substr(half_size, value.length()) };
    output = std::make_pair(upper, lower);
  }
  else
  {
    uintLarge_t upper{ value.substr(0,value.length() - default_chunk_size) };
    uintLarge_t lower{ value.substr(value.length() - default_chunk_size) };
    output = std::make_pair(upper, lower);
  }
  return output;
}

// TODO: remove if not used
uintLarge_t uintLarge_t::multiply_by_10(const uintLarge_t& input, const size_t num_times)
{
  uintLarge_t temp_input = input;
  for (size_t i{ 0 }; i < num_times; ++i)
  {
    temp_input.value.append("0");
  }
  return temp_input;
}

void uintLarge_t::match_size(uintLarge_t& first, uintLarge_t& second)
{
  if (first.value.size() > second.value.size())
  {
    size_t delta = first.value.size() - second.value.size();
    second.value.insert(0, delta, '0');
  }
  else if (first.value.size() < second.value.size())
  {
    size_t delta = second.value.size() - first.value.size();
    first.value.insert(0, delta, '0');
  }
  else
  {
    // Do nothing
  }
}
