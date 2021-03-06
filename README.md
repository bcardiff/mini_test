# mini_test for C++

mini_test is a minimalist framework for testing C++ code.

Many C++ testing frameworks requires skills that are not found from the beginning.

## Features

* Easy to install & use: download & copy [`./src/mini_test.h`](https://raw.github.com/bcardiff/mini_test/master/src/mini_test.h).
* Create plain `void` test case functions.
* Write assertions for expected values.
* Write plain `main()` with the list of test functions to run.
* Report success or failure per test function.


## Installation

1. Copy [`./src/mini_test.h`](https://raw.github.com/bcardiff/mini_test/master/src/mini_test.h) to your C++ project.
2. Add reference to `mini_test.h` in your test file.

mini_test is a single header library.

## Usage

Suppose you want to test a `int max(int, int);` function defined in `your_lib.h`/`your_lib.cpp`.


1. Create `tests.cpp`. Include `your_lib.h` and `mini_test.h`

	```
	// file: tests.cpp

	#include "mini_test.h"
	#include "your_lib.h"
	```

1. Add test cases. Use `ASSERT(<bool>)` or `ASSERT_EQ(<T>, <T>)` where `T = bool, int, const char *, string` to assert expectations.

	```
	// file: tests.cpp
	#include "mini_test.h"
	#include "your_lib.h"

    void max_between_positives() {
      int m = max(3, 7);
      ASSERT_EQ(m, 7);
    }

    void max_between_negatives() {
      int m = max(-3, -7);
      ASSERT_EQ(m, -3);
    }
    ```

1. Create a main entry point that list the test cases to be executed.

	```
	// file: tests.cpp
	#include "mini_test.h"
	#include "your_lib.h"

    void max_between_positives() { ... }
    void max_between_negatives() { ... }

    int main() {
      RUN_TEST(max_between_positives);
      RUN_TEST(max_between_negatives);

	  return 0;
    }
    ```

1. Compile & run. You should see:

	```
	$ ./tests
	max_between_positives...ok
	max_between_negatives...ok
	```

	or, if you mistook `>` with `<`:

	```
	$ ./tests
	max_between_positives...failed
	  at tests.cpp:6
	    expected value: 7
	      actual value: 3
	max_between_negatives...failed
	  at tests.cpp:11
	    expected value: -3
	      actual value: -7

	```

Check the complete [samples](https://github.com/bcardiff/mini_test/tree/master/samples) on [github](https://github.com/bcardiff/mini_test).


[![githalytics.com alpha](https://cruel-carlota.pagodabox.com/684d04121e5b8a12d91c4166ee1b1659 "githalytics.com")](http://githalytics.com/bcardiff/mini_test)
