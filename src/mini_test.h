#ifndef MINI_TEST
#define MINI_TEST

#include <iostream>
#include <sstream>

namespace mt {

using namespace std;

template<class T>
void make_error(T lhs, T rhs, string loc) {
  ostringstream os;
  os << "  at " << loc << endl;
  os << "    expected value: " << rhs << endl;
  os << "      actual value: " << lhs;
  throw os.str().c_str();
}

void make_missing_exception_error(string loc);

template<typename T>
void make_wrong_type_exception_error(T e, const char* expected, string loc) {
  ostringstream os;
  os << "  at " << loc << endl;
  os << "    an unexpected exception ocurred" << endl;
  os << "    expected type: " << expected << endl;
  os << "    but got: " << e;
  throw os.str().c_str();
}

string location(const char* file, int line);
string bool_to_s(bool b);

void assert_eq(bool lhs, bool rhs, string loc);
void assert_eq(int lhs, int rhs, string loc);
void assert_eq(string lhs, string rhs, string loc);
void assert_eq(const char* lhs, const char* rhs, string loc);

}

#define RUN_TEST(test) {\
  {bool mt_ok = true;\
  std::cout << #test << "..." << std::flush;\
  try { test(); }\
  catch (const char* msg) { mt_ok = false; std::cout << "failed" << std::endl << msg; } \
  catch (...) { mt_ok = false; std::cout << "failed"; }\
  if (mt_ok) { std::cout << "ok"; }\
  std::cout << std::endl << std::flush;\
  }\
}
#define ASSERT_EQ(lhs, rhs) { mt::assert_eq((lhs), (rhs), mt::location(__FILE__, __LINE__)); }
#define ASSERT(expr) { mt::assert_eq((expr), true, mt::location(__FILE__, __LINE__)); }

#define ASSERT_RAISE(code) {\
  {bool mt_thrown = false;\
  try { code; }\
  catch (...) { mt_thrown = true; }\
  if (!mt_thrown) { mt::make_missing_exception_error(mt::location(__FILE__, __LINE__)); }\
  }\
}

// catch (const char* msg) { mt::make_wrong_type_exception_error(msg, #e_type, mt_location(__FILE__, __LINE__)); }

#define ASSERT_RAISE_A(e_type, code) {\
  {bool mt_thrown = false;\
  try { code; }\
  catch (e_type mt_e) { mt_thrown = true; }\
  catch (const std::exception &e) { mt::make_wrong_type_exception_error(e.what(), #e_type, mt::location(__FILE__, __LINE__)); }\
  catch (...) { mt::make_wrong_type_exception_error("<unkown type>", #e_type, mt::location(__FILE__, __LINE__)); }\
  if (!mt_thrown) { mt::make_missing_exception_error(mt::location(__FILE__, __LINE__)); }\
  }\
}
#endif
