#include "mini_test.h"
#include <stdexcept>

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

void assert_raise_should_raise_a_missing_exception_expectation_exception_if_a_missing_exception_was_expected() {
  MissingExceptionExpectationException e;
  string l;
  ASSERT_RAISE_A(MissingExceptionExpectationException, e, {
    l=BKMK;ASSERT_RAISE({});
  });

  ASSERT_EQ(e.location(), l);
}

void assert_raise_a_should_not_raise_if_the_exception_was_expected() {
  const char *e;
  ASSERT_RAISE_A(const char *, e, {
    throw "should be catched by ASSERT_RAISE";
  });
}

void assert_raise_a_should_raise_if_the_exception_was_of_wrong_type() {
  WrongExceptionExpectationException e;
  string l;
  const char *inner;
  ASSERT_RAISE_A(WrongExceptionExpectationException, e, {
    l = BKMK; ASSERT_RAISE_A(const char *, inner, {throw 1;});
  });

  ASSERT_EQ(e.location(), l);
  ASSERT_EQ(e.expected(), "const char *");
  ASSERT_EQ(e.actual(), "<unkown type>");
}

void assert_raise_a_should_raise_if_the_exception_was_of_wrong_type_with_inner_exception() {
  WrongExceptionExpectationException e;
  string l;
  const char *inner;
  ASSERT_RAISE_A(WrongExceptionExpectationException, e, {
    l = BKMK; ASSERT_RAISE_A(const char *, inner, {throw logic_error("foo bar");});
  });

  ASSERT_EQ(e.location(), l);
  ASSERT_EQ(e.expected(), "const char *");
  ASSERT_EQ(e.actual(), "foo bar");
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

void assert_eq_succeed_if_values_match() {
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

void assert_eq_with_doubles() {
  ValueExpectationException<double> e;
  string l;
  ASSERT_RAISE_A(ValueExpectationException<double>, e, {
    l = BKMK; ASSERT_EQ(1.1, 2.0);
  });

  ASSERT_EQ(e.actual(), 1.1);
  ASSERT_EQ(e.expected(), 2.0);
  ASSERT_EQ(e.location(), l);

  ASSERT_EQ(42.0, 42.0);
}

void assert_eq_with_floats() {
  ValueExpectationException<float> e;
  string l;
  ASSERT_RAISE_A(ValueExpectationException<float>, e, {
    l = BKMK; ASSERT_EQ(1.1f, 2.0f);
  });

  ASSERT_EQ(e.actual(), 1.1f);
  ASSERT_EQ(e.expected(), 2.0f);
  ASSERT_EQ(e.location(), l);

  ASSERT_EQ(42.0f, 42.0f);
}

void assert_succeed_on_true() {
  ASSERT(true);
}

void assert_fails_on_false() {
  ValueExpectationException<string> e;
  string l;
  ASSERT_RAISE_A(ValueExpectationException<string>, e, {
    l = BKMK; ASSERT(false);
  });

  ASSERT_EQ(e.location(), l);
  ASSERT_EQ(e.actual(), "false");
  ASSERT_EQ(e.expected(), "true");
}

int counter_f = 0;
int f() { counter_f++; return 1; }
int counter_g = 0;
int g() { counter_g++; return 0; }
void expressions_are_evaluated_once() {
  ASSERT_RAISE({
    ASSERT_EQ(f(), g())
  });

  ASSERT_EQ(counter_f, 1);
  ASSERT_EQ(counter_g, 1);
}

int main() {
  RUN_TEST(assert_raise_should_not_raise_if_the_exception_was_expected);
  RUN_TEST(assert_raise_should_raise_if_a_missing_exception_was_expected);
  RUN_TEST(assert_raise_should_raise_a_missing_exception_expectation_exception_if_a_missing_exception_was_expected);

  RUN_TEST(assert_raise_a_should_not_raise_if_the_exception_was_expected);
  RUN_TEST(assert_raise_a_should_raise_if_the_exception_was_of_wrong_type);
  RUN_TEST(assert_raise_a_should_raise_if_the_exception_was_of_wrong_type_with_inner_exception);

  RUN_TEST(assert_eq_fails_with_values_and_location);
  RUN_TEST(assert_eq_succeed_if_values_match);

  RUN_TEST(assert_eq_with_strings);
  RUN_TEST(assert_eq_with_char_ptr);
  RUN_TEST(assert_eq_with_strings_and_char_ptr);
  RUN_TEST(assert_eq_with_doubles);
  RUN_TEST(assert_eq_with_floats);

  RUN_TEST(assert_succeed_on_true);
  RUN_TEST(assert_fails_on_false);

  RUN_TEST(expressions_are_evaluated_once);

  return 0;
}
