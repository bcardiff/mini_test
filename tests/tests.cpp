#include "mini_test.h"

#define BKMK location(__FILE__, __LINE__)

using namespace mt;

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

void assert_eq_fails_with_values_and_location() {
  ValueExpectationException<int> e;
  string l;
  ASSERT_RAISE_A(ValueExpectationException<int>, e, {
     l = BKMK; ASSERT_EQ(1, 0);
  });

  ASSERT_EQ(e.actual(), 1);
  ASSERT_EQ(e.expected(), 0);
  ASSERT_EQ(e.location(), l);
}

void assert_eq_succed_if_values_match() {
  ASSERT_EQ(42, 42);
}

void assert_eq_with_strings() {
  ValueExpectationException<string> e;
  string l;
  ASSERT_RAISE_A(ValueExpectationException<string>, e, {
    l = BKMK; ASSERT_EQ(string("foo"), string("bar"));
  });

  ASSERT_EQ(e.actual(), string("foo"));
  ASSERT_EQ(e.expected(), string("bar"));
  ASSERT_EQ(e.location(), l);

  ASSERT_EQ(string("lorem ipsum"), string("lorem ipsum"));
}

void assert_eq_with_char_ptr() {
  ValueExpectationException<string> e;
  string l;
  ASSERT_RAISE_A(ValueExpectationException<string>, e, {
    l = BKMK; ASSERT_EQ("foo", "bar");
  });

  ASSERT_EQ(e.actual(), "foo");
  ASSERT_EQ(e.expected(), "bar");
  ASSERT_EQ(e.location(), l);

  ASSERT_EQ("lorem ipsum", "lorem ipsum");
}

void assert_eq_with_strings_and_char_ptr() {
  ValueExpectationException<string> e;
  string l;
  ASSERT_RAISE_A(ValueExpectationException<string>, e, {
    l = BKMK; ASSERT_EQ(string("foo"), "bar");
  });

  ASSERT_EQ(e.actual(), string("foo"));
  ASSERT_EQ(e.expected(), "bar");
  ASSERT_EQ(e.location(), l);

  ASSERT_EQ(string("lorem ipsum"), "lorem ipsum");
}

int main() {
  RUN_TEST(assert_raise_should_not_raise_if_the_exception_was_expected);
  RUN_TEST(assert_raise_should_raise_if_a_missing_exception_was_expected);

  RUN_TEST(assert_raise_of_should_not_raise_if_the_exception_was_expected);
  RUN_TEST(assert_raise_of_should_raise_if_the_exception_was_of_wrong_type);

  RUN_TEST(assert_eq_fails_with_values_and_location);
  RUN_TEST(assert_eq_succed_if_values_match);

  RUN_TEST(assert_eq_with_strings);
  RUN_TEST(assert_eq_with_char_ptr);
  RUN_TEST(assert_eq_with_strings_and_char_ptr);

  return 0;
}
