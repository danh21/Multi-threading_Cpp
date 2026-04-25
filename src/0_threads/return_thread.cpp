// Example of returning a thread object from a function
#include <thread>
#include <iostream>
#include <chrono>

using namespace std;

// Task function for the thread
void hello() {
	cout << "Hello, Thread!\n";
}

// Function returning a thread object
thread func() {
	// Start the thread
	thread thr(hello);

	// Return a local variable
	return thr;

	// Return a temporary object
	// return thread(hello);
}

int main() {
	// Call a function which return an thread object
	thread thr = func();
	cout << "Received thread with ID " << thr.get_id() << '\n';

	// Our thr object now "owns" the system thread
	// It is responsible for calling join()
	thr.join();
}

/* === OUTPUT ===
 * Command  : g++ ./return_thread.cpp -o out -lpthread && ./out
 *
 * Hello, Thread!
 * Received thread with ID 2
 */