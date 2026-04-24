// Example of using a lambda expression as a thread's entry point
// The lambda takes arguments
#include <thread>
#include <iostream>

using namespace std;

int main() {
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

	thr.join();
}
/* === OUTPUT ===
 * Compiled : 2026-04-24 15:30:32
 * Command  : g++ ./thread_lambda_arg.cpp -o out && ./out
 *
 * The sum of 2 and 3 is 5
 */
