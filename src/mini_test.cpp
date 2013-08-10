#include "mini_test.h"
#include <iostream>
#include <sstream>

namespace mt {

using namespace std;

void assert_eq(bool lhs, bool rhs, string loc) { if (lhs != rhs) { make_error(bool_to_s(lhs), bool_to_s(rhs), loc); } }
void assert_eq(int lhs, int rhs, string loc) { if (lhs != rhs) { make_error(lhs, rhs, loc); } }
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
