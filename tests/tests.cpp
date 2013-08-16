#include "mini_test.h"

void assert_raise_should_not_raise_if_the_exception_was_expected() {
  ASSERT_RAISE({
    throw "should be catched by ASSERT_RAISE";
  });
}

void assert_raise_should_raise_if_a_missing_exception_was_expected() {
  ASSERT_RAISE({
    ASSERT_RAISE({
    });
  });
}

void assert_raise_of_should_not_raise_if_the_exception_was_expected() {
  const char *e;
  ASSERT_RAISE_A(const char *, e, {
    throw "should be catched by ASSERT_RAISE";
  });
}

void assert_raise_of_should_raise_if_the_exception_was_of_wrong_type() {
  const char *e;
  ASSERT_RAISE({
    ASSERT_RAISE_A(const char *, e, {
      throw 1;
    });
  });
}

int main() {
  RUN_TEST(assert_raise_should_not_raise_if_the_exception_was_expected);
  RUN_TEST(assert_raise_should_raise_if_a_missing_exception_was_expected);

  RUN_TEST(assert_raise_of_should_not_raise_if_the_exception_was_expected);
  RUN_TEST(assert_raise_of_should_raise_if_the_exception_was_of_wrong_type);

  return 0;
}
