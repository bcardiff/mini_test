#ifndef MINI_TEST
#define MINI_TEST

#include <iostream>
#include <sstream>
#include <exception>

namespace mt {

using namespace std;

template<class T>
class ValueExpectationException : public std::exception {
public:
  ValueExpectationException() {}

  ValueExpectationException(T actual, T expected, string loc) :
    _actual(actual), _expected(expected), _location(loc) { }

  virtual ~ValueExpectationException() throw() { }

  virtual const char* what() const throw() {
    ostringstream os;
    os << "  at " << _location << endl;
    os << "    expected value: " << _expected << endl;
    os << "      actual value: " << _actual;
    return os.str().c_str();
  }

  T actual() { return _actual; }
  T expected() { return _expected; }
  string location() { return _location; }

private:
  T _actual;
  T _expected;
  string _location;
};

template<class T>
void make_error(T lhs, T rhs, string loc) {
  throw ValueExpectationException<T>(lhs, rhs, loc);
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

#define SUPPORT_ASSERT_EQ_ON(T) \
void assert_eq(T lhs, T rhs, string loc) { if (!(lhs == rhs)) { make_error(lhs, rhs, loc); } }\


void assert_eq(bool lhs, bool rhs, string loc);
SUPPORT_ASSERT_EQ_ON(int)
SUPPORT_ASSERT_EQ_ON(double)
SUPPORT_ASSERT_EQ_ON(float)
void assert_eq(string lhs, string rhs, string loc);
void assert_eq(const char* lhs, const char* rhs, string loc);

}

#define RUN_TEST(test) {\
  {bool mt_ok = true;\
  std::cout << #test << "..." << std::flush;\
  try { test(); }\
  catch (std::exception& e) { mt_ok = false; std::cout << "failed" << std::endl << e.what(); } \
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

#define ASSERT_RAISE_A(e_type, var, code) {\
  {bool mt_thrown = false;\
  try { code; }\
  catch (e_type mt_e) { mt_thrown = true; var = mt_e; }\
  catch (const std::exception &e) { mt::make_wrong_type_exception_error(e.what(), #e_type, mt::location(__FILE__, __LINE__)); }\
  catch (...) { mt::make_wrong_type_exception_error("<unkown type>", #e_type, mt::location(__FILE__, __LINE__)); }\
  if (!mt_thrown) { mt::make_missing_exception_error(mt::location(__FILE__, __LINE__)); }\
  }\
}


// code that could be splitted in .cpp if needed

namespace mt {

using namespace std;

void assert_eq(bool lhs, bool rhs, string loc) { if (lhs != rhs) { make_error(bool_to_s(lhs), bool_to_s(rhs), loc); } }
void assert_eq(string lhs, string rhs, string loc) { if (lhs.compare(rhs) != 0) { make_error(lhs, rhs, loc); } }
void assert_eq(const char* lhs, const char* rhs, string loc) { assert_eq(string(lhs), string(rhs), loc); }

string location(const char* file, int line) {
  ostringstream os;
  os << file << ":" << line;
  return os.str().c_str();
}

string bool_to_s(bool b) { return b ? "true" : "false"; }

void make_missing_exception_error(string loc) {
  ostringstream os;
  os << "  at " << loc << endl;
  os << "    an exception was expected" << endl;
  os << "    no exception was thrown";
  throw os.str().c_str();
}

}


#endif
