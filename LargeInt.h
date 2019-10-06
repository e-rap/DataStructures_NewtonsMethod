#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

const size_t default_chunk_size = 9; ///< maximum number of digits for multiplication of
                                     ///< two decimal numbers

///
/// Data type for operations with unsigned integer numbers greater than 64bits
///
class uintLarge_t
{
public:
  using IntType = int64_t;

  /// Default constructor, empty initial value
  uintLarge_t();

  /// Constructs a LargeInt 
  uintLarge_t(const std::string& value);

  /// Adds two large unsigned integers together
  static uintLarge_t add(const uintLarge_t& lhs, const uintLarge_t& rhs);

  ///
  /// Subtracts two large unsigned integers together
  ///
  /// lhs must greator than or equal to rhs
  ///
  static uintLarge_t subtract(const uintLarge_t& lhs, const uintLarge_t& rhs);

  ///
  /// Multiplies two large unsigned integers together
  ///
  /// Utilizes karatsuba's algorithm
  ///
  static uintLarge_t multiply(const uintLarge_t& lhs, const uintLarge_t& rhs);

  /// Divides two large unsigned integers together
  static uintLarge_t divide(const uintLarge_t& numerator, const uintLarge_t& denominator, size_t digits_of_precision);

  /// Calculates the sqrt of a large unsigned integer
  static uintLarge_t sqrt(const uintLarge_t& input, size_t digits_of_precision);

  /// Returns the value of the large unsigned integer as a string
  std::string get_string_value() const;

  // Operator Overloads for arithmetic operations

  uintLarge_t operator +(const uintLarge_t& other);
  uintLarge_t operator -(const uintLarge_t& other);
  uintLarge_t operator *(const uintLarge_t& other);

private:


  /// Multiplies a large integer number by 10, num_times times.
  static uintLarge_t multiply_by_10(const uintLarge_t& input, const size_t num_times);

  /// Makes the size of large unsigned integers equal by appending zeros to the smaller number
  static void match_size(uintLarge_t& first, uintLarge_t& second);

  /// Recusrive implmenetation of the karatasuba multiplication
  static uintLarge_t karatasuba_multiply(const uintLarge_t& lhs, const uintLarge_t& rhs, const size_t chunk_size = default_chunk_size);

  ///
  /// Returns the integer value of a digit within the large unsigned integer
  ///
  /// The 0th index is the most significant digit
  ///
  int get_digit_value(size_t index) const;

  /// Sets the integer value of a digit within the large unsigned integer
  ///
  /// The 0th index is the most significant digit. Value must be between 0-9.
  void set_digit_value(int value, size_t index);

  ///
  /// Splits up large unsigned int half for the karatasuba algorithm
  ///
  /// The first entry of the pair is the upper half and the second
  /// Entry of the pair is the lower half
  ///
  std::pair<uintLarge_t, uintLarge_t> cut_in_half() const;



  std::string value;
};

