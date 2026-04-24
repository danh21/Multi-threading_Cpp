// Example of passing an argument to a thread function

#include <thread>
#include <iostream>

using namespace std;

// Callable object - thread entry point
void hello(string str) {
    cout << str << '\n';
}

int main() {
	// hello() takes a string argument
	thread thr(hello, "Hello, Thread!");

	thr.join();
}
/* === OUTPUT ===
 * Compiled : 2026-04-24 15:30:30
 * Command  : g++ ./thread_args.cpp -o out && ./out
 *
 * Hello, Thread!
 */
