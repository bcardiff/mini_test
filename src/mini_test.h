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

class MissingExceptionExpectationException : public std::exception {
public:
  MissingExceptionExpectationException() {}

  MissingExceptionExpectationException(string loc) :
    _location(loc) { }

  virtual ~MissingExceptionExpectationException() throw() { }

  virtual const char* what() const throw() {
    ostringstream os;
    os << "  at " << _location << endl;
    os << "    an exception was expected" << endl;
    os << "    no exception was thrown";
    throw os.str().c_str();
  }

  string location() { return _location; }

private:
  string _location;
};

void make_missing_exception_error(string loc) {
  throw MissingExceptionExpectationException(loc);
}

class WrongExceptionExpectationException : public std::exception {
public:
  WrongExceptionExpectationException() {}

  WrongExceptionExpectationException(string actual, string expected, string loc) :
    _actual(actual), _expected(expected), _location(loc) { }

  virtual ~WrongExceptionExpectationException() throw() { }

  virtual const char* what() const throw() {
    ostringstream os;
    os << "  at " << _location << endl;
    os << "    an unexpected exception ocurred" << endl;
    os << "    expected type: " << _expected << endl;
    os << "    but got: " << _actual;
    return os.str().c_str();
  }

  string actual() { return _actual; }
  string expected() { return _expected; }
  string location() { return _location; }

private:
  string _actual;
  string _expected;
  string _location;
};

template<typename T>
void make_wrong_type_exception_error(T e, const char* expected, string loc) {
  throw WrongExceptionExpectationException(e, expected, loc);
}

string location(const char* file, int line) {
  ostringstream os;
  os << file << ":" << line;
  return os.str().c_str();
}

string bool_to_s(bool b) { return b ? "true" : "false"; }

#define SUPPORT_ASSERT_EQ_ON(T) \
void assert_eq(T lhs, T rhs, string loc) { if (!(lhs == rhs)) { make_error(lhs, rhs, loc); } }\


SUPPORT_ASSERT_EQ_ON(int)
SUPPORT_ASSERT_EQ_ON(double)
SUPPORT_ASSERT_EQ_ON(float)
void assert_eq(bool lhs, bool rhs, string loc) { if (lhs != rhs) { make_error(bool_to_s(lhs), bool_to_s(rhs), loc); } }
void assert_eq(string lhs, string rhs, string loc) { if (lhs.compare(rhs) != 0) { make_error(lhs, rhs, loc); } }
void assert_eq(const char* lhs, const char* rhs, string loc) { assert_eq(string(lhs), string(rhs), loc); }

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

#define ASSERT_RAISE_A(e_type, var, code) {\
  {bool mt_thrown = false;\
  try { code; }\
  catch (e_type mt_e) { mt_thrown = true; var = mt_e; }\
  catch (const std::exception &e) { mt::make_wrong_type_exception_error(e.what(), #e_type, mt::location(__FILE__, __LINE__)); }\
  catch (...) { mt::make_wrong_type_exception_error("<unkown type>", #e_type, mt::location(__FILE__, __LINE__)); }\
  if (!mt_thrown) { mt::make_missing_exception_error(mt::location(__FILE__, __LINE__)); }\
  }\
}

#endif
