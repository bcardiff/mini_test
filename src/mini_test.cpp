#include "mini_test.h"
#include <iostream>
#include <sstream>
using namespace std;

void mt_assert(bool lhs, bool rhs, string loc) { if (lhs != rhs) { mt_make_error(mt_bool_to_s(lhs), mt_bool_to_s(rhs), loc); } }
void mt_assert(int lhs, int rhs, string loc) { if (lhs != rhs) { mt_make_error(lhs, rhs, loc); } }
void mt_assert(string lhs, string rhs, string loc) { if (lhs.compare(rhs) != 0) { mt_make_error(lhs, rhs, loc); } }
void mt_assert(const char* lhs, const char* rhs, string loc) { mt_assert(string(lhs), string(rhs), loc); }


string mt_location(const char* file, int line) {
  ostringstream os;
  os << file << ":" << line;
  return os.str().c_str();
}

string mt_bool_to_s(bool b) { return b ? "true" : "false"; }

void mt_make_missing_exception_error(string loc) {
  ostringstream os;
  os << "  at " << loc << endl;
  os << "    an exception was expected" << endl;
  os << "    no exception was thrown";
  throw os.str().c_str();
}
