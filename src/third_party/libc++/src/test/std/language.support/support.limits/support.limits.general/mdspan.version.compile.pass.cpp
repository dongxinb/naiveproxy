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

// <mdspan>

// Test the feature test macros defined by <mdspan>

/*  Constant                         Value
    __cpp_lib_freestanding_mdspan    202311L [C++26]
    __cpp_lib_mdspan                 202207L [C++23]
    __cpp_lib_submdspan              202306L [C++26]
*/

#include <mdspan>
#include "test_macros.h"

#if TEST_STD_VER < 14

# ifdef __cpp_lib_freestanding_mdspan
#   error "__cpp_lib_freestanding_mdspan should not be defined before c++26"
# endif

# ifdef __cpp_lib_mdspan
#   error "__cpp_lib_mdspan should not be defined before c++23"
# endif

# ifdef __cpp_lib_submdspan
#   error "__cpp_lib_submdspan should not be defined before c++26"
# endif

#elif TEST_STD_VER == 14

# ifdef __cpp_lib_freestanding_mdspan
#   error "__cpp_lib_freestanding_mdspan should not be defined before c++26"
# endif

# ifdef __cpp_lib_mdspan
#   error "__cpp_lib_mdspan should not be defined before c++23"
# endif

# ifdef __cpp_lib_submdspan
#   error "__cpp_lib_submdspan should not be defined before c++26"
# endif

#elif TEST_STD_VER == 17

# ifdef __cpp_lib_freestanding_mdspan
#   error "__cpp_lib_freestanding_mdspan should not be defined before c++26"
# endif

# ifdef __cpp_lib_mdspan
#   error "__cpp_lib_mdspan should not be defined before c++23"
# endif

# ifdef __cpp_lib_submdspan
#   error "__cpp_lib_submdspan should not be defined before c++26"
# endif

#elif TEST_STD_VER == 20

# ifdef __cpp_lib_freestanding_mdspan
#   error "__cpp_lib_freestanding_mdspan should not be defined before c++26"
# endif

# ifdef __cpp_lib_mdspan
#   error "__cpp_lib_mdspan should not be defined before c++23"
# endif

# ifdef __cpp_lib_submdspan
#   error "__cpp_lib_submdspan should not be defined before c++26"
# endif

#elif TEST_STD_VER == 23

# ifdef __cpp_lib_freestanding_mdspan
#   error "__cpp_lib_freestanding_mdspan should not be defined before c++26"
# endif

# ifndef __cpp_lib_mdspan
#   error "__cpp_lib_mdspan should be defined in c++23"
# endif
# if __cpp_lib_mdspan != 202207L
#   error "__cpp_lib_mdspan should have the value 202207L in c++23"
# endif

# ifdef __cpp_lib_submdspan
#   error "__cpp_lib_submdspan should not be defined before c++26"
# endif

#elif TEST_STD_VER > 23

# if !defined(_LIBCPP_VERSION)
#   ifndef __cpp_lib_freestanding_mdspan
#     error "__cpp_lib_freestanding_mdspan should be defined in c++26"
#   endif
#   if __cpp_lib_freestanding_mdspan != 202311L
#     error "__cpp_lib_freestanding_mdspan should have the value 202311L in c++26"
#   endif
# else // _LIBCPP_VERSION
#   ifdef __cpp_lib_freestanding_mdspan
#     error "__cpp_lib_freestanding_mdspan should not be defined because it is unimplemented in libc++!"
#   endif
# endif

# ifndef __cpp_lib_mdspan
#   error "__cpp_lib_mdspan should be defined in c++26"
# endif
# if __cpp_lib_mdspan != 202207L
#   error "__cpp_lib_mdspan should have the value 202207L in c++26"
# endif

# if !defined(_LIBCPP_VERSION)
#   ifndef __cpp_lib_submdspan
#     error "__cpp_lib_submdspan should be defined in c++26"
#   endif
#   if __cpp_lib_submdspan != 202306L
#     error "__cpp_lib_submdspan should have the value 202306L in c++26"
#   endif
# else // _LIBCPP_VERSION
#   ifdef __cpp_lib_submdspan
#     error "__cpp_lib_submdspan should not be defined because it is unimplemented in libc++!"
#   endif
# endif

#endif // TEST_STD_VER > 23

