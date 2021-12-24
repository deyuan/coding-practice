// Copyright (c) 2018 Deyuan Guo. All rights reserved.
// This file is subject to the terms and conditions defined
// in file 'LICENSE' in this source code package.

#include <iostream>
#include <iomanip>
#include <limits>
#include <typeinfo>
#include <string>
#include <cstdint>
#include <climits>
#include <cfloat>
#include <cwchar>

// <limits> numeric_limits
template <typename T>
void ShowDataTypeInfo(const std::string &name) {
  std::cout << std::setw(20) << name
      << std::setw(8) << typeid(T).name()
      << std::setw(8) << sizeof(T)
      << std::setw(22) << std::numeric_limits<T>::min()
      << std::setw(22) << std::numeric_limits<T>::max()
      << std::endl;
}

// <limits> numeric_limits
template <typename T>
void ShowCharTypeInfo(const std::string &name) {
  // Convert min/max of char type to int, otherwise it shows garbled text
  std::cout << std::setw(20) << name
      << std::setw(8) << typeid(T).name()
      << std::setw(8) << sizeof(T)
      << std::setw(22) << static_cast<int>(std::numeric_limits<T>::min())
      << std::setw(22) << static_cast<int>(std::numeric_limits<T>::max())
      << std::endl;
}

void PrimitiveDataTypes() {
  // Header
  std::cout << std::setw(20) << "Type"
      << std::setw(8) << "TypeId"
      << std::setw(8) << "Size"
      << std::setw(22) << "Min"
      << std::setw(22) << "Max"
      << std::endl;
  std::cout << std::endl;

  // Boolean type
  ShowDataTypeInfo<bool>("bool");

  // Character types
  ShowCharTypeInfo<char>("char");
  ShowCharTypeInfo<signed char>("signed char");
  ShowCharTypeInfo<unsigned char>("unsigned char");

  ShowDataTypeInfo<char16_t>("char16_t");  // c++11 fundamental
  ShowDataTypeInfo<char32_t>("char32_t");  // c++11 fundamental
  ShowDataTypeInfo<wchar_t>("wchar_t");

  // Integer types: signedness and size can be combined in any order;
  //                int/signed is optional
  // Recommend to use int16_t and int64_t instead of short, long and long long
  ShowDataTypeInfo<short>("short");
  ShowDataTypeInfo<int>("int");
  ShowDataTypeInfo<long>("long");
  ShowDataTypeInfo<long long>("long long");  // c++11

  ShowDataTypeInfo<unsigned short>("unsigned short");
  ShowDataTypeInfo<unsigned int>("unsigned int");
  ShowDataTypeInfo<unsigned long>("unsigned long");
  ShowDataTypeInfo<unsigned long long>("unsigned long long");  // c++11

  // Floating point types
  ShowDataTypeInfo<float>("float");
  ShowDataTypeInfo<double>("double");
  ShowDataTypeInfo<long double>("long double");

  // Pointer types
  ShowDataTypeInfo<void *>("void *");
  ShowDataTypeInfo<int *>("int *");

  // Misc
  ShowDataTypeInfo<size_t>("size_t");
  ShowDataTypeInfo<wint_t>("wint_t");  // <cwchar> hold wchar_t

  std::cout << std::endl;

  // <cstdint> c++11: Fixed width integer types
  ShowCharTypeInfo<int8_t>("int8_t");  // signed char
  ShowDataTypeInfo<int16_t>("int16_t");
  ShowDataTypeInfo<int32_t>("int32_t");
  ShowDataTypeInfo<int64_t>("int64_t");

  ShowCharTypeInfo<int_fast8_t>("int_fast8_t");  // signed char
  ShowDataTypeInfo<int_fast16_t>("int_fast16_t");
  ShowDataTypeInfo<int_fast32_t>("int_fast32_t");
  ShowDataTypeInfo<int_fast64_t>("int_fast64_t");

  ShowCharTypeInfo<int_least8_t>("int_least8_t");  // signed char
  ShowDataTypeInfo<int_least16_t>("int_least16_t");
  ShowDataTypeInfo<int_least32_t>("int_least32_t");
  ShowDataTypeInfo<int_least64_t>("int_least64_t");

  ShowDataTypeInfo<intmax_t>("intmax_t");
  ShowDataTypeInfo<intptr_t>("intptr_t");

  ShowCharTypeInfo<uint8_t>("uint8_t");  // unsigned char
  ShowDataTypeInfo<uint16_t>("uint16_t");
  ShowDataTypeInfo<uint32_t>("uint32_t");
  ShowDataTypeInfo<uint64_t>("uint64_t");

  ShowCharTypeInfo<uint_fast8_t>("uint_fast8_t");  // unsigned char
  ShowDataTypeInfo<uint_fast16_t>("uint_fast16_t");
  ShowDataTypeInfo<uint_fast32_t>("uint_fast32_t");
  ShowDataTypeInfo<uint_fast64_t>("uint_fast64_t");

  ShowCharTypeInfo<uint_least8_t>("uint_least8_t");  // unsigned char
  ShowDataTypeInfo<uint_least16_t>("uint_least16_t");
  ShowDataTypeInfo<uint_least32_t>("uint_least32_t");
  ShowDataTypeInfo<uint_least64_t>("uint_least64_t");

  ShowDataTypeInfo<uintmax_t>("uintmax_t");
  ShowDataTypeInfo<uintptr_t>("uintptr_t");

  std::cout << std::endl << "Range macros:" << std::endl;

  // <climits>
  std::cout << std::setw(15) << "CHAR_MIN"   << std::setw(22) << CHAR_MIN
            << std::setw(15) << "CHAR_MAX"   << std::setw(22) << CHAR_MAX
            << std::endl;
  std::cout << std::setw(15) << "SCHAR_MIN"  << std::setw(22) << SCHAR_MIN
            << std::setw(15) << "SCHAR_MAX"  << std::setw(22) << SCHAR_MAX
            << std::endl;
  std::cout << std::setw(15) << "--"         << std::setw(22) << 0
            << std::setw(15) << "UCHAR_MAX"  << std::setw(22) << UCHAR_MAX
            << std::endl;
  std::cout << std::setw(15) << "SHRT_MIN"   << std::setw(22) << SHRT_MIN
            << std::setw(15) << "SHRT_MAX"   << std::setw(22) << SHRT_MAX
            << std::endl;
  std::cout << std::setw(15) << "--"         << std::setw(22) << 0
            << std::setw(15) << "USHRT_MAX"  << std::setw(22) << USHRT_MAX
            << std::endl;
  std::cout << std::setw(15) << "INT_MIN"    << std::setw(22) << INT_MIN
            << std::setw(15) << "INT_MAX"    << std::setw(22) << INT_MAX
            << std::endl;
  std::cout << std::setw(15) << "--"         << std::setw(22) << 0
            << std::setw(15) << "UINT_MAX"   << std::setw(22) << UINT_MAX
            << std::endl;
  std::cout << std::setw(15) << "LONG_MIN"   << std::setw(22) << LONG_MIN
            << std::setw(15) << "LONG_MAX"   << std::setw(22) << LONG_MAX
            << std::endl;
  std::cout << std::setw(15) << "--"         << std::setw(22) << 0
            << std::setw(15) << "ULONG_MAX"  << std::setw(22) << ULONG_MAX
            << std::endl;
  std::cout << std::setw(15) << "LLONG_MIN"  << std::setw(22) << LLONG_MIN
            << std::setw(15) << "LLONG_MAX"  << std::setw(22) << LLONG_MAX
            << std::endl;
  std::cout << std::setw(15) << "--"         << std::setw(22) << 0
            << std::setw(15) << "ULLONG_MAX" << std::setw(22) << ULLONG_MAX
            << std::endl;

  // <cfloat>
  std::cout << std::setw(15) << "FLT_MIN"    << std::setw(22) << FLT_MIN
            << std::setw(15) << "FLT_MAX"    << std::setw(22) << FLT_MAX
            << std::endl;
  std::cout << std::setw(15) << "DBL_MIN"    << std::setw(22) << DBL_MIN
            << std::setw(15) << "DBL_MAX"    << std::setw(22) << DBL_MAX
            << std::endl;
  std::cout << std::setw(15) << "LDBL_MIN"   << std::setw(22) << LDBL_MIN
            << std::setw(15) << "LDBL_MAX"   << std::setw(22) << LDBL_MAX
            << std::endl;
}

int main() {
  PrimitiveDataTypes();
  return 0;
}

