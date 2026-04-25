// Example of thread with a functor
#include <thread>
#include <iostream>

using namespace std;

// Functor class with overloaded () operator
class Hello {
	public:
	void operator()() { cout << "Hello, Functor Thread!\n"; }
};

int main() {
	// Create an object of the functor class
	Hello hello;

	// Pass the functor object to thread's constructor
	thread thr(hello);

	// Wait for the thread to complete
	thr.join();
}

/* === OUTPUT ===
 * Command  : g++ ./pass_functor.cpp -o out -lpthread && ./out
 *
 * Hello, Functor Thread!
 */