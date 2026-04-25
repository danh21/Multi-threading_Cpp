// Example with thread handle
#include <thread>
#include <iostream>

using namespace std;

// Task function
void hello() {
	cout << "Hello, Thread!" << endl;
}

int main() {
	// Create an thread object
	thread thr(hello);

	// Display the child thread's native handle
	cout << "Hello thread has native handle " << thr.native_handle() << '\n';

	// Wait for the thread to complete
	thr.join();

	// Display the child thread's native handle again
	cout << "Hello thread now has native handle " << thr.native_handle() << '\n';
}

/* === OUTPUT ===
 * Command  : g++ ./native_handle.cpp -o out -lpthread && ./out
 *
 * Hello thread has native handle 2
 * Hello, Thread!
 * Hello thread now has native handle 0
 */