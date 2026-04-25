// Example of using a lambda expression as a thread's entry point
// The lambda takes arguments
#include <thread>
#include <iostream>

using namespace std;

int main() {
    int i = 3;

	// Use a lambda expression as the thread's entry point
	thread thr(
		// The first argument is the lambda expression
		[] (int i1, int i2) {
			cout << "The sum of " << i1 << " and " << i2 << " is "
				<< i1 + i2 << '\n';
		},

		// The remaining arguments are passed to the lambda expression
		2, 3
	);

	// Use a lambda expression as the thread's entry point
	thread thr1(
		// The first argument is the lambda expression
		[&i] {
		i *= 2;
	});

    thr.join();
	thr1.join();

	cout << "Value of i is now " << i << '\n';
}

/* === OUTPUT ===
 * Command  : g++ ./pass_lambda_expression.cpp -o out -lpthread && ./out
 *
 * The sum of 2 and 3 is 5
 * Value of i is now 6
 */