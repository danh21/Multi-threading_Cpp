// Example of using a lambda expression as a thread's entry point
// The lambda captures a local variable
#include <thread>
#include <iostream>

using namespace std;

int main() {
	int i = 3;

	// Use a lambda expression as the thread's entry point
	thread thr(
		// The first argument is the lambda expression
		[&i] {
		i *= 2;
	});

	thr.join();

	cout << "Value of i is now " << i << '\n';
}
/* === OUTPUT ===
 * Compiled : 2026-04-24 15:30:34
 * Command  : g++ ./thread_lambda_ref.cpp -o out && ./out
 *
 * Value of i is now 6
 */
