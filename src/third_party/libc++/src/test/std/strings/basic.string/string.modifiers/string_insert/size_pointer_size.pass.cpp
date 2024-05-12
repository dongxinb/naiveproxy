//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <string>

// basic_string<charT,traits,Allocator>&
//   insert(size_type pos, const charT* s, size_type n); // constexpr since C++20

#include <string>
#include <stdexcept>
#include <cassert>

#include "test_macros.h"
#include "min_allocator.h"
#include "asan_testing.h"

template <class S>
TEST_CONSTEXPR_CXX20 void
test(S s, typename S::size_type pos, const typename S::value_type* str, typename S::size_type n, S expected) {
  const typename S::size_type old_size = s.size();
  S s0                                 = s;
  if (pos <= old_size) {
    s.insert(pos, str, n);
    LIBCPP_ASSERT(s.__invariants());
    assert(s == expected);
    LIBCPP_ASSERT(is_string_asan_correct(s));
  }
#ifndef TEST_HAS_NO_EXCEPTIONS
  else if (!TEST_IS_CONSTANT_EVALUATED) {
    try {
      s.insert(pos, str, n);
      assert(false);
    } catch (std::out_of_range&) {
      assert(pos > old_size);
      assert(s == s0);
    }
  }
#endif
}

template <class S>
TEST_CONSTEXPR_CXX20 bool test() {
  {
    test(S(""), 0, "", 0, S(""));
    test(S(""), 0, "12345", 0, S(""));
    test(S(""), 0, "12345", 1, S("1"));
    test(S(""), 0, "12345", 2, S("12"));
    test(S(""), 0, "12345", 4, S("1234"));
    test(S(""), 0, "12345", 5, S("12345"));
    test(S(""), 0, "1234567890", 0, S(""));
    test(S(""), 0, "1234567890", 1, S("1"));
    test(S(""), 0, "1234567890", 5, S("12345"));
    test(S(""), 0, "1234567890", 9, S("123456789"));
    test(S(""), 0, "1234567890", 10, S("1234567890"));
    test(S(""), 0, "12345678901234567890", 0, S(""));
    test(S(""), 0, "12345678901234567890", 1, S("1"));
    test(S(""), 0, "12345678901234567890", 10, S("1234567890"));
    test(S(""), 0, "12345678901234567890", 19, S("1234567890123456789"));
    test(S(""), 0, "12345678901234567890", 20, S("12345678901234567890"));
    test(S(""), 1, "", 0, S("can't happen"));
    test(S(""), 1, "12345", 0, S("can't happen"));
    test(S(""), 1, "12345", 1, S("can't happen"));
    test(S(""), 1, "12345", 2, S("can't happen"));
    test(S(""), 1, "12345", 4, S("can't happen"));
    test(S(""), 1, "12345", 5, S("can't happen"));
    test(S(""), 1, "1234567890", 0, S("can't happen"));
    test(S(""), 1, "1234567890", 1, S("can't happen"));
    test(S(""), 1, "1234567890", 5, S("can't happen"));
    test(S(""), 1, "1234567890", 9, S("can't happen"));
    test(S(""), 1, "1234567890", 10, S("can't happen"));
    test(S(""), 1, "12345678901234567890", 0, S("can't happen"));
    test(S(""), 1, "12345678901234567890", 1, S("can't happen"));
    test(S(""), 1, "12345678901234567890", 10, S("can't happen"));
    test(S(""), 1, "12345678901234567890", 19, S("can't happen"));
    test(S(""), 1, "12345678901234567890", 20, S("can't happen"));
    test(S("abcde"), 0, "", 0, S("abcde"));
    test(S("abcde"), 0, "12345", 0, S("abcde"));
    test(S("abcde"), 0, "12345", 1, S("1abcde"));
    test(S("abcde"), 0, "12345", 2, S("12abcde"));
    test(S("abcde"), 0, "12345", 4, S("1234abcde"));
    test(S("abcde"), 0, "12345", 5, S("12345abcde"));
    test(S("abcde"), 0, "1234567890", 0, S("abcde"));
    test(S("abcde"), 0, "1234567890", 1, S("1abcde"));
    test(S("abcde"), 0, "1234567890", 5, S("12345abcde"));
    test(S("abcde"), 0, "1234567890", 9, S("123456789abcde"));
    test(S("abcde"), 0, "1234567890", 10, S("1234567890abcde"));
    test(S("abcde"), 0, "12345678901234567890", 0, S("abcde"));
    test(S("abcde"), 0, "12345678901234567890", 1, S("1abcde"));
    test(S("abcde"), 0, "12345678901234567890", 10, S("1234567890abcde"));
    test(S("abcde"), 0, "12345678901234567890", 19, S("1234567890123456789abcde"));
    test(S("abcde"), 0, "12345678901234567890", 20, S("12345678901234567890abcde"));
    test(S("abcde"), 1, "", 0, S("abcde"));
    test(S("abcde"), 1, "12345", 0, S("abcde"));
    test(S("abcde"), 1, "12345", 1, S("a1bcde"));
    test(S("abcde"), 1, "12345", 2, S("a12bcde"));
    test(S("abcde"), 1, "12345", 4, S("a1234bcde"));
    test(S("abcde"), 1, "12345", 5, S("a12345bcde"));
    test(S("abcde"), 1, "1234567890", 0, S("abcde"));
    test(S("abcde"), 1, "1234567890", 1, S("a1bcde"));
    test(S("abcde"), 1, "1234567890", 5, S("a12345bcde"));
    test(S("abcde"), 1, "1234567890", 9, S("a123456789bcde"));
    test(S("abcde"), 1, "1234567890", 10, S("a1234567890bcde"));
    test(S("abcde"), 1, "12345678901234567890", 0, S("abcde"));
    test(S("abcde"), 1, "12345678901234567890", 1, S("a1bcde"));
    test(S("abcde"), 1, "12345678901234567890", 10, S("a1234567890bcde"));
    test(S("abcde"), 1, "12345678901234567890", 19, S("a1234567890123456789bcde"));
    test(S("abcde"), 1, "12345678901234567890", 20, S("a12345678901234567890bcde"));
    test(S("abcde"), 2, "", 0, S("abcde"));
    test(S("abcde"), 2, "12345", 0, S("abcde"));
    test(S("abcde"), 2, "12345", 1, S("ab1cde"));
    test(S("abcde"), 2, "12345", 2, S("ab12cde"));
    test(S("abcde"), 2, "12345", 4, S("ab1234cde"));
    test(S("abcde"), 2, "12345", 5, S("ab12345cde"));
    test(S("abcde"), 2, "1234567890", 0, S("abcde"));
    test(S("abcde"), 2, "1234567890", 1, S("ab1cde"));
    test(S("abcde"), 2, "1234567890", 5, S("ab12345cde"));
    test(S("abcde"), 2, "1234567890", 9, S("ab123456789cde"));
    test(S("abcde"), 2, "1234567890", 10, S("ab1234567890cde"));
    test(S("abcde"), 2, "12345678901234567890", 0, S("abcde"));
    test(S("abcde"), 2, "12345678901234567890", 1, S("ab1cde"));
    test(S("abcde"), 2, "12345678901234567890", 10, S("ab1234567890cde"));
    test(S("abcde"), 2, "12345678901234567890", 19, S("ab1234567890123456789cde"));
    test(S("abcde"), 2, "12345678901234567890", 20, S("ab12345678901234567890cde"));
    test(S("abcde"), 4, "", 0, S("abcde"));
    test(S("abcde"), 4, "12345", 0, S("abcde"));
    test(S("abcde"), 4, "12345", 1, S("abcd1e"));
    test(S("abcde"), 4, "12345", 2, S("abcd12e"));
    test(S("abcde"), 4, "12345", 4, S("abcd1234e"));
    test(S("abcde"), 4, "12345", 5, S("abcd12345e"));
    test(S("abcde"), 4, "1234567890", 0, S("abcde"));
    test(S("abcde"), 4, "1234567890", 1, S("abcd1e"));
    test(S("abcde"), 4, "1234567890", 5, S("abcd12345e"));
    test(S("abcde"), 4, "1234567890", 9, S("abcd123456789e"));
    test(S("abcde"), 4, "1234567890", 10, S("abcd1234567890e"));
    test(S("abcde"), 4, "12345678901234567890", 0, S("abcde"));
    test(S("abcde"), 4, "12345678901234567890", 1, S("abcd1e"));
    test(S("abcde"), 4, "12345678901234567890", 10, S("abcd1234567890e"));
    test(S("abcde"), 4, "12345678901234567890", 19, S("abcd1234567890123456789e"));
    test(S("abcde"), 4, "12345678901234567890", 20, S("abcd12345678901234567890e"));
    test(S("abcde"), 5, "", 0, S("abcde"));
    test(S("abcde"), 5, "12345", 0, S("abcde"));
    test(S("abcde"), 5, "12345", 1, S("abcde1"));
    test(S("abcde"), 5, "12345", 2, S("abcde12"));
    test(S("abcde"), 5, "12345", 4, S("abcde1234"));
    test(S("abcde"), 5, "12345", 5, S("abcde12345"));
    test(S("abcde"), 5, "1234567890", 0, S("abcde"));
    test(S("abcde"), 5, "1234567890", 1, S("abcde1"));
    test(S("abcde"), 5, "1234567890", 5, S("abcde12345"));
    test(S("abcde"), 5, "1234567890", 9, S("abcde123456789"));
    test(S("abcde"), 5, "1234567890", 10, S("abcde1234567890"));
    test(S("abcde"), 5, "12345678901234567890", 0, S("abcde"));
    test(S("abcde"), 5, "12345678901234567890", 1, S("abcde1"));
    test(S("abcde"), 5, "12345678901234567890", 10, S("abcde1234567890"));
    test(S("abcde"), 5, "12345678901234567890", 19, S("abcde1234567890123456789"));
    test(S("abcde"), 5, "12345678901234567890", 20, S("abcde12345678901234567890"));
    test(S("abcde"), 6, "", 0, S("can't happen"));
    test(S("abcde"), 6, "12345", 0, S("can't happen"));
    test(S("abcde"), 6, "12345", 1, S("can't happen"));
    test(S("abcde"), 6, "12345", 2, S("can't happen"));
    test(S("abcde"), 6, "12345", 4, S("can't happen"));
    test(S("abcde"), 6, "12345", 5, S("can't happen"));
    test(S("abcde"), 6, "1234567890", 0, S("can't happen"));
    test(S("abcde"), 6, "1234567890", 1, S("can't happen"));
    test(S("abcde"), 6, "1234567890", 5, S("can't happen"));
    test(S("abcde"), 6, "1234567890", 9, S("can't happen"));
    test(S("abcde"), 6, "1234567890", 10, S("can't happen"));
    test(S("abcde"), 6, "12345678901234567890", 0, S("can't happen"));
    test(S("abcde"), 6, "12345678901234567890", 1, S("can't happen"));
    test(S("abcde"), 6, "12345678901234567890", 10, S("can't happen"));
    test(S("abcde"), 6, "12345678901234567890", 19, S("can't happen"));
    test(S("abcde"), 6, "12345678901234567890", 20, S("can't happen"));
    test(S("abcdefghij"), 0, "", 0, S("abcdefghij"));
    test(S("abcdefghij"), 0, "12345", 0, S("abcdefghij"));
    test(S("abcdefghij"), 0, "12345", 1, S("1abcdefghij"));
    test(S("abcdefghij"), 0, "12345", 2, S("12abcdefghij"));
    test(S("abcdefghij"), 0, "12345", 4, S("1234abcdefghij"));
    test(S("abcdefghij"), 0, "12345", 5, S("12345abcdefghij"));
    test(S("abcdefghij"), 0, "1234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 0, "1234567890", 1, S("1abcdefghij"));
    test(S("abcdefghij"), 0, "1234567890", 5, S("12345abcdefghij"));
    test(S("abcdefghij"), 0, "1234567890", 9, S("123456789abcdefghij"));
    test(S("abcdefghij"), 0, "1234567890", 10, S("1234567890abcdefghij"));
    test(S("abcdefghij"), 0, "12345678901234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 0, "12345678901234567890", 1, S("1abcdefghij"));
    test(S("abcdefghij"), 0, "12345678901234567890", 10, S("1234567890abcdefghij"));
    test(S("abcdefghij"), 0, "12345678901234567890", 19, S("1234567890123456789abcdefghij"));
    test(S("abcdefghij"), 0, "12345678901234567890", 20, S("12345678901234567890abcdefghij"));
    test(S("abcdefghij"), 1, "", 0, S("abcdefghij"));
    test(S("abcdefghij"), 1, "12345", 0, S("abcdefghij"));
    test(S("abcdefghij"), 1, "12345", 1, S("a1bcdefghij"));
    test(S("abcdefghij"), 1, "12345", 2, S("a12bcdefghij"));
    test(S("abcdefghij"), 1, "12345", 4, S("a1234bcdefghij"));
    test(S("abcdefghij"), 1, "12345", 5, S("a12345bcdefghij"));
    test(S("abcdefghij"), 1, "1234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 1, "1234567890", 1, S("a1bcdefghij"));
    test(S("abcdefghij"), 1, "1234567890", 5, S("a12345bcdefghij"));
    test(S("abcdefghij"), 1, "1234567890", 9, S("a123456789bcdefghij"));
    test(S("abcdefghij"), 1, "1234567890", 10, S("a1234567890bcdefghij"));
    test(S("abcdefghij"), 1, "12345678901234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 1, "12345678901234567890", 1, S("a1bcdefghij"));
    test(S("abcdefghij"), 1, "12345678901234567890", 10, S("a1234567890bcdefghij"));
    test(S("abcdefghij"), 1, "12345678901234567890", 19, S("a1234567890123456789bcdefghij"));
    test(S("abcdefghij"), 1, "12345678901234567890", 20, S("a12345678901234567890bcdefghij"));
    test(S("abcdefghij"), 5, "", 0, S("abcdefghij"));
    test(S("abcdefghij"), 5, "12345", 0, S("abcdefghij"));
    test(S("abcdefghij"), 5, "12345", 1, S("abcde1fghij"));
    test(S("abcdefghij"), 5, "12345", 2, S("abcde12fghij"));
    test(S("abcdefghij"), 5, "12345", 4, S("abcde1234fghij"));
    test(S("abcdefghij"), 5, "12345", 5, S("abcde12345fghij"));
    test(S("abcdefghij"), 5, "1234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 5, "1234567890", 1, S("abcde1fghij"));
    test(S("abcdefghij"), 5, "1234567890", 5, S("abcde12345fghij"));
    test(S("abcdefghij"), 5, "1234567890", 9, S("abcde123456789fghij"));
    test(S("abcdefghij"), 5, "1234567890", 10, S("abcde1234567890fghij"));
    test(S("abcdefghij"), 5, "12345678901234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 5, "12345678901234567890", 1, S("abcde1fghij"));
    test(S("abcdefghij"), 5, "12345678901234567890", 10, S("abcde1234567890fghij"));
    test(S("abcdefghij"), 5, "12345678901234567890", 19, S("abcde1234567890123456789fghij"));
    test(S("abcdefghij"), 5, "12345678901234567890", 20, S("abcde12345678901234567890fghij"));
    test(S("abcdefghij"), 9, "", 0, S("abcdefghij"));
    test(S("abcdefghij"), 9, "12345", 0, S("abcdefghij"));
    test(S("abcdefghij"), 9, "12345", 1, S("abcdefghi1j"));
    test(S("abcdefghij"), 9, "12345", 2, S("abcdefghi12j"));
    test(S("abcdefghij"), 9, "12345", 4, S("abcdefghi1234j"));
    test(S("abcdefghij"), 9, "12345", 5, S("abcdefghi12345j"));
    test(S("abcdefghij"), 9, "1234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 9, "1234567890", 1, S("abcdefghi1j"));
    test(S("abcdefghij"), 9, "1234567890", 5, S("abcdefghi12345j"));
    test(S("abcdefghij"), 9, "1234567890", 9, S("abcdefghi123456789j"));
    test(S("abcdefghij"), 9, "1234567890", 10, S("abcdefghi1234567890j"));
    test(S("abcdefghij"), 9, "12345678901234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 9, "12345678901234567890", 1, S("abcdefghi1j"));
    test(S("abcdefghij"), 9, "12345678901234567890", 10, S("abcdefghi1234567890j"));
    test(S("abcdefghij"), 9, "12345678901234567890", 19, S("abcdefghi1234567890123456789j"));
    test(S("abcdefghij"), 9, "12345678901234567890", 20, S("abcdefghi12345678901234567890j"));
    test(S("abcdefghij"), 10, "", 0, S("abcdefghij"));
    test(S("abcdefghij"), 10, "12345", 0, S("abcdefghij"));
    test(S("abcdefghij"), 10, "12345", 1, S("abcdefghij1"));
    test(S("abcdefghij"), 10, "12345", 2, S("abcdefghij12"));
    test(S("abcdefghij"), 10, "12345", 4, S("abcdefghij1234"));
    test(S("abcdefghij"), 10, "12345", 5, S("abcdefghij12345"));
    test(S("abcdefghij"), 10, "1234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 10, "1234567890", 1, S("abcdefghij1"));
    test(S("abcdefghij"), 10, "1234567890", 5, S("abcdefghij12345"));
    test(S("abcdefghij"), 10, "1234567890", 9, S("abcdefghij123456789"));
    test(S("abcdefghij"), 10, "1234567890", 10, S("abcdefghij1234567890"));
    test(S("abcdefghij"), 10, "12345678901234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 10, "12345678901234567890", 1, S("abcdefghij1"));
    test(S("abcdefghij"), 10, "12345678901234567890", 10, S("abcdefghij1234567890"));
    test(S("abcdefghij"), 10, "12345678901234567890", 19, S("abcdefghij1234567890123456789"));
    test(S("abcdefghij"), 10, "12345678901234567890", 20, S("abcdefghij12345678901234567890"));
    test(S("abcdefghij"), 11, "", 0, S("can't happen"));
    test(S("abcdefghij"), 11, "12345", 0, S("can't happen"));
    test(S("abcdefghij"), 11, "12345", 1, S("can't happen"));
    test(S("abcdefghij"), 11, "12345", 2, S("can't happen"));
    test(S("abcdefghij"), 11, "12345", 4, S("can't happen"));
    test(S("abcdefghij"), 11, "12345", 5, S("can't happen"));
    test(S("abcdefghij"), 11, "1234567890", 0, S("can't happen"));
    test(S("abcdefghij"), 11, "1234567890", 1, S("can't happen"));
    test(S("abcdefghij"), 11, "1234567890", 5, S("can't happen"));
    test(S("abcdefghij"), 11, "1234567890", 9, S("can't happen"));
    test(S("abcdefghij"), 11, "1234567890", 10, S("can't happen"));
    test(S("abcdefghij"), 11, "12345678901234567890", 0, S("can't happen"));
    test(S("abcdefghij"), 11, "12345678901234567890", 1, S("can't happen"));
    test(S("abcdefghij"), 11, "12345678901234567890", 10, S("can't happen"));
    test(S("abcdefghij"), 11, "12345678901234567890", 19, S("can't happen"));
    test(S("abcdefghij"), 11, "12345678901234567890", 20, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 0, "", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, "12345", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, "12345", 1, S("1abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, "12345", 2, S("12abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, "12345", 4, S("1234abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, "12345", 5, S("12345abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, "1234567890", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, "1234567890", 1, S("1abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, "1234567890", 5, S("12345abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, "1234567890", 9, S("123456789abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, "1234567890", 10, S("1234567890abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, "12345678901234567890", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, "12345678901234567890", 1, S("1abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, "12345678901234567890", 10, S("1234567890abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, "12345678901234567890", 19, S("1234567890123456789abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, "12345678901234567890", 20, S("12345678901234567890abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, "", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, "12345", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, "12345", 1, S("a1bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, "12345", 2, S("a12bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, "12345", 4, S("a1234bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, "12345", 5, S("a12345bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, "1234567890", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, "1234567890", 1, S("a1bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, "1234567890", 5, S("a12345bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, "1234567890", 9, S("a123456789bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, "1234567890", 10, S("a1234567890bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, "12345678901234567890", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, "12345678901234567890", 1, S("a1bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, "12345678901234567890", 10, S("a1234567890bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, "12345678901234567890", 19, S("a1234567890123456789bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, "12345678901234567890", 20, S("a12345678901234567890bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, "", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, "12345", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, "12345", 1, S("abcdefghij1klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, "12345", 2, S("abcdefghij12klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, "12345", 4, S("abcdefghij1234klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, "12345", 5, S("abcdefghij12345klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, "1234567890", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, "1234567890", 1, S("abcdefghij1klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, "1234567890", 5, S("abcdefghij12345klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, "1234567890", 9, S("abcdefghij123456789klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, "1234567890", 10, S("abcdefghij1234567890klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, "12345678901234567890", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, "12345678901234567890", 1, S("abcdefghij1klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, "12345678901234567890", 10, S("abcdefghij1234567890klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, "12345678901234567890", 19, S("abcdefghij1234567890123456789klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, "12345678901234567890", 20, S("abcdefghij12345678901234567890klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 19, "", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 19, "12345", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 19, "12345", 1, S("abcdefghijklmnopqrs1t"));
    test(S("abcdefghijklmnopqrst"), 19, "12345", 2, S("abcdefghijklmnopqrs12t"));
    test(S("abcdefghijklmnopqrst"), 19, "12345", 4, S("abcdefghijklmnopqrs1234t"));
    test(S("abcdefghijklmnopqrst"), 19, "12345", 5, S("abcdefghijklmnopqrs12345t"));
    test(S("abcdefghijklmnopqrst"), 19, "1234567890", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 19, "1234567890", 1, S("abcdefghijklmnopqrs1t"));
    test(S("abcdefghijklmnopqrst"), 19, "1234567890", 5, S("abcdefghijklmnopqrs12345t"));
    test(S("abcdefghijklmnopqrst"), 19, "1234567890", 9, S("abcdefghijklmnopqrs123456789t"));
    test(S("abcdefghijklmnopqrst"), 19, "1234567890", 10, S("abcdefghijklmnopqrs1234567890t"));
    test(S("abcdefghijklmnopqrst"), 19, "12345678901234567890", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 19, "12345678901234567890", 1, S("abcdefghijklmnopqrs1t"));
    test(S("abcdefghijklmnopqrst"), 19, "12345678901234567890", 10, S("abcdefghijklmnopqrs1234567890t"));
    test(S("abcdefghijklmnopqrst"), 19, "12345678901234567890", 19, S("abcdefghijklmnopqrs1234567890123456789t"));
    test(S("abcdefghijklmnopqrst"), 19, "12345678901234567890", 20, S("abcdefghijklmnopqrs12345678901234567890t"));
    test(S("abcdefghijklmnopqrst"), 20, "", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 20, "12345", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 20, "12345", 1, S("abcdefghijklmnopqrst1"));
    test(S("abcdefghijklmnopqrst"), 20, "12345", 2, S("abcdefghijklmnopqrst12"));
    test(S("abcdefghijklmnopqrst"), 20, "12345", 4, S("abcdefghijklmnopqrst1234"));
    test(S("abcdefghijklmnopqrst"), 20, "12345", 5, S("abcdefghijklmnopqrst12345"));
    test(S("abcdefghijklmnopqrst"), 20, "1234567890", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 20, "1234567890", 1, S("abcdefghijklmnopqrst1"));
    test(S("abcdefghijklmnopqrst"), 20, "1234567890", 5, S("abcdefghijklmnopqrst12345"));
    test(S("abcdefghijklmnopqrst"), 20, "1234567890", 9, S("abcdefghijklmnopqrst123456789"));
    test(S("abcdefghijklmnopqrst"), 20, "1234567890", 10, S("abcdefghijklmnopqrst1234567890"));
    test(S("abcdefghijklmnopqrst"), 20, "12345678901234567890", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 20, "12345678901234567890", 1, S("abcdefghijklmnopqrst1"));
    test(S("abcdefghijklmnopqrst"), 20, "12345678901234567890", 10, S("abcdefghijklmnopqrst1234567890"));
    test(S("abcdefghijklmnopqrst"), 20, "12345678901234567890", 19, S("abcdefghijklmnopqrst1234567890123456789"));
    test(S("abcdefghijklmnopqrst"), 20, "12345678901234567890", 20, S("abcdefghijklmnopqrst12345678901234567890"));
    test(S("abcdefghijklmnopqrst"), 21, "", 0, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, "12345", 0, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, "12345", 1, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, "12345", 2, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, "12345", 4, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, "12345", 5, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, "1234567890", 0, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, "1234567890", 1, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, "1234567890", 5, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, "1234567890", 9, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, "1234567890", 10, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, "12345678901234567890", 0, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, "12345678901234567890", 1, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, "12345678901234567890", 10, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, "12345678901234567890", 19, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, "12345678901234567890", 20, S("can't happen"));
  }

  { // test inserting into self
    S s_short = "123/";
    S s_long  = "Lorem ipsum dolor sit amet, consectetur/";

    s_short.insert(0, s_short.data(), s_short.size());
    assert(s_short == "123/123/");
    s_short.insert(0, s_short.data(), s_short.size());
    assert(s_short == "123/123/123/123/");
    s_short.insert(0, s_short.data(), s_short.size());
    assert(s_short == "123/123/123/123/123/123/123/123/");

    s_long.insert(0, s_long.data(), s_long.size());
    assert(s_long == "Lorem ipsum dolor sit amet, consectetur/Lorem ipsum dolor sit amet, consectetur/");
  }

  return true;
}

int main(int, char**) {
  test<std::string>();
#if TEST_STD_VER >= 11
  test<std::basic_string<char, std::char_traits<char>, min_allocator<char>>>();
  test<std::basic_string<char, std::char_traits<char>, safe_allocator<char>>>();
#endif

#if TEST_STD_VER > 17
  static_assert(test<std::string>());
  static_assert(test<std::basic_string<char, std::char_traits<char>, min_allocator<char>>>());
#endif

  return 0;
}
