//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// WARNING: This test was generated by generate_feature_test_macro_components.py
// and should not be edited manually.
//
// clang-format off

// <variant>

// Test the feature test macros defined by <variant>

/*  Constant                          Value
    __cpp_lib_freestanding_variant    202311L [C++26]
    __cpp_lib_variant                 202102L [C++17]
*/

#include <variant>
#include "test_macros.h"

#if TEST_STD_VER < 14

# ifdef __cpp_lib_freestanding_variant
#   error "__cpp_lib_freestanding_variant should not be defined before c++26"
# endif

# ifdef __cpp_lib_variant
#   error "__cpp_lib_variant should not be defined before c++17"
# endif

#elif TEST_STD_VER == 14

# ifdef __cpp_lib_freestanding_variant
#   error "__cpp_lib_freestanding_variant should not be defined before c++26"
# endif

# ifdef __cpp_lib_variant
#   error "__cpp_lib_variant should not be defined before c++17"
# endif

#elif TEST_STD_VER == 17

# ifdef __cpp_lib_freestanding_variant
#   error "__cpp_lib_freestanding_variant should not be defined before c++26"
# endif

# ifndef __cpp_lib_variant
#   error "__cpp_lib_variant should be defined in c++17"
# endif
# if __cpp_lib_variant != 202102L
#   error "__cpp_lib_variant should have the value 202102L in c++17"
# endif

#elif TEST_STD_VER == 20

# ifdef __cpp_lib_freestanding_variant
#   error "__cpp_lib_freestanding_variant should not be defined before c++26"
# endif

# ifndef __cpp_lib_variant
#   error "__cpp_lib_variant should be defined in c++20"
# endif
# if __cpp_lib_variant != 202102L
#   error "__cpp_lib_variant should have the value 202102L in c++20"
# endif

#elif TEST_STD_VER == 23

# ifdef __cpp_lib_freestanding_variant
#   error "__cpp_lib_freestanding_variant should not be defined before c++26"
# endif

# ifndef __cpp_lib_variant
#   error "__cpp_lib_variant should be defined in c++23"
# endif
# if __cpp_lib_variant != 202102L
#   error "__cpp_lib_variant should have the value 202102L in c++23"
# endif

#elif TEST_STD_VER > 23

# if !defined(_LIBCPP_VERSION)
#   ifndef __cpp_lib_freestanding_variant
#     error "__cpp_lib_freestanding_variant should be defined in c++26"
#   endif
#   if __cpp_lib_freestanding_variant != 202311L
#     error "__cpp_lib_freestanding_variant should have the value 202311L in c++26"
#   endif
# else // _LIBCPP_VERSION
#   ifdef __cpp_lib_freestanding_variant
#     error "__cpp_lib_freestanding_variant should not be defined because it is unimplemented in libc++!"
#   endif
# endif

# ifndef __cpp_lib_variant
#   error "__cpp_lib_variant should be defined in c++26"
# endif
# if __cpp_lib_variant != 202102L
#   error "__cpp_lib_variant should have the value 202102L in c++26"
# endif

#endif // TEST_STD_VER > 23

