#ifndef MINI_TEST
#define MINI_TEST

/*

Mini Test for C++
author: Brian J. Cardiff

1. include mini_test.h

   #include "mini_test.h"

2. Create simple test cases.

    void testName() {
      // test code
    }

3. Use ASSERT(<bool>) or ASSERT_EQ(<T>, <T>) where T = bool, int, string.

    void testName() {
      int m = max(3, 7);
      ASSERT_EQ(m, 7);
    }

4. Create a main entry point that list the test cases to be executed.

    int main() {
      RUN_TEST(testName);
      RUN_TEST(testName2);
      RUN_TEST(testName3);
      // etc.
    }

5. Compile & run.

*/

#include <iostream>
#include <sstream>
using namespace std;

template<class T>
void mt_make_error(T lhs, T rhs, string loc) {
  ostringstream os;
  os << "  at " << loc << endl;
  os << "    expected value: " << rhs << endl;
  os << "      actual value: " << lhs;
  throw os.str();
}

string mt_location(const char* file, int line) {
  ostringstream os;
  os << file << ":" << line;
  return os.str();
}

string mt_bool_to_s(bool b) { return b ? "true" : "false"; }

void mt_assert(bool lhs, bool rhs, string loc) { if (lhs != rhs) { mt_make_error(mt_bool_to_s(lhs), mt_bool_to_s(rhs), loc); } }
void mt_assert(int lhs, int rhs, string loc) { if (lhs != rhs) { mt_make_error(lhs, rhs, loc); } }
void mt_assert(string lhs, string rhs, string loc) { if (lhs.compare(rhs) != 0) { mt_make_error(lhs, rhs, loc); } }
void mt_assert(const char* lhs, const char* rhs, string loc) { mt_assert(string(lhs), string(rhs), loc); }
#define RUN_TEST(test) {\
  {bool ok = true;\
  cout << #test << "..." << flush;\
  try { test(); }\
  catch (string& msg) { ok = false; cout << "error" << endl << msg; } \
  catch (...) { ok = false; cout << "error"; }\
  if (ok) { cout << "ok"; }\
  cout << endl << flush;\
  }\
}
#define ASSERT_EQ(lhs, rhs) { mt_assert((lhs), (rhs), mt_location(__FILE__, __LINE__)); }
#define ASSERT(expr) { mt_assert((expr), true, mt_location(__FILE__, __LINE__)); }

#endif
