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
 * Command  : g++ ./pass_args.cpp -o out -lpthread && ./out
 *
 * Hello, Thread!
 */