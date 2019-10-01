#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

const size_t default_chunk_size = 9; ///< maximum number of digits for multiplication of
                                     ///< two decimal numbers

const size_t base = 10;

///
/// Handles arithmetic operations for large integers
///
class LargeInt
{
public:
  using IntType = int64_t;

  LargeInt();
  LargeInt(const std::string& value);
  void add(const LargeInt& rhs);
  void subtract(const LargeInt& rhs);
  void multiply(const LargeInt& rhs);
  void divide(const LargeInt& denominator);
  void sqrt();
  std::string get_value() const;

  void karatasuba_multiply(const LargeInt& rhs, const size_t chunk_size = default_chunk_size);

  // TODO: Move to Private
  /// splits up large int number in chunks of size chunk_size from least significant to most significant
  std::vector<IntType> extract_chunks(const size_t chunk_size = default_chunk_size) const;

private:
  void multiply_by_10(const size_t num_times);

  std::string value;
};

