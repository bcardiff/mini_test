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
  throw os.str().c_str();
}

void mt_make_missing_exception_error(string loc);

template<typename T>
void mt_make_wrong_type_exception_error(T e, const char* expected, string loc) {
  ostringstream os;
  os << "  at " << loc << endl;
  os << "    an unexpected exception ocurred" << endl;
  os << "    expected type: " << expected << endl;
  os << "    but got: " << e;
  throw os.str().c_str();
}

string mt_location(const char* file, int line);
string mt_bool_to_s(bool b);

void mt_assert(bool lhs, bool rhs, string loc);
void mt_assert(int lhs, int rhs, string loc);
void mt_assert(string lhs, string rhs, string loc);
void mt_assert(const char* lhs, const char* rhs, string loc);

#define RUN_TEST(test) {\
  {bool ok = true;\
  cout << #test << "..." << flush;\
  try { test(); }\
  catch (const char* msg) { ok = false; cout << "failed" << endl << msg; } \
  catch (...) { ok = false; cout << "failed"; }\
  if (ok) { cout << "ok"; }\
  cout << endl << flush;\
  }\
}
#define ASSERT_EQ(lhs, rhs) { mt_assert((lhs), (rhs), mt_location(__FILE__, __LINE__)); }
#define ASSERT(expr) { mt_assert((expr), true, mt_location(__FILE__, __LINE__)); }

#define ASSERT_RAISE(code) {\
  {bool mt_thrown = false;\
  try { code; }\
  catch (...) { mt_thrown = true; }\
  if (!mt_thrown) { mt_make_missing_exception_error(mt_location(__FILE__, __LINE__)); }\
  }\
}

// catch (const char* msg) { mt_make_wrong_type_exception_error(msg, #e_type, mt_location(__FILE__, __LINE__)); }

#define ASSERT_RAISE_A(e_type, code) {\
  {bool mt_thrown = false;\
  try { code; }\
  catch (e_type mt_e) { mt_thrown = true; }\
  catch (const std::exception &e) { mt_make_wrong_type_exception_error(e.what(), #e_type, mt_location(__FILE__, __LINE__)); }\
  catch (...) { mt_make_wrong_type_exception_error("<unkown type>", #e_type, mt_location(__FILE__, __LINE__)); }\
  if (!mt_thrown) { mt_make_missing_exception_error(mt_location(__FILE__, __LINE__)); }\
  }\
}
#endif
