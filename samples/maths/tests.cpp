#include "mini_test.h"
#include "math_module.h"

void absolute_of_positives() {
  int x = absolute(4);
  ASSERT_EQ(x, 4);
}

void absolute_of_negatives() {
  int x = absolute(-5);
  ASSERT_EQ(x, 5);
}

int main() {
  RUN_TEST(absolute_of_positives);
  RUN_TEST(absolute_of_negatives);
}

