#include "mini_test.h"

// void should_not_raise_if_no_exception() {

// }

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
  ASSERT_RAISE_A(const char *, {
    throw "should be catched by ASSERT_RAISE";
  });
}

void assert_raise_of_should_raise_if_the_exception_was_of_wrong_type() {
  ASSERT_RAISE({
    ASSERT_RAISE_A(const char *, {
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
