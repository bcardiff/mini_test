#include "mini_test.h"

void test_bool() {
  ASSERT_EQ(true, false);
}

void test_int() {
  ASSERT_EQ(1, 0);
}

void test_string_literal() {
  ASSERT_EQ("this does", "not match");
}

void test_string() {
  string s1("this does");
  string s2("not match");
  ASSERT_EQ(s1, s2);
}

void test_string_and_literal() {
  string s1("this does");
  ASSERT_EQ(s1, "not match");
}

int main() {
  RUN_TEST(test_bool);
  RUN_TEST(test_int);
  RUN_TEST(test_string);
  RUN_TEST(test_string_literal);
  RUN_TEST(test_string_and_literal);
}
