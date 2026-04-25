// Example with thread ID
#include <iostream>
#include <thread>

using namespace std;

// Task function
// Displays the thread's ID
void hello() {
	cout << "Hello from thread with ID " << this_thread::get_id() << endl;
}

int main() {
	// Display the main thread's ID
	cout << "Main thread has ID " << this_thread::get_id() << endl;

	// Create an thread object
	thread thr(hello);

	// Display the child thread's ID
	cout << "Hello thread has ID " << thr.get_id() << '\n';

	// Wait for the thread to complete
	thr.join();

	// Display the child thread's ID again
	cout << "Hello thread now has ID " << thr.get_id() << '\n';
}

/* === OUTPUT ===
 * Command  : g++ ./get_id.cpp -o out -lpthread && ./out
 *
 * Main thread has ID 1
 * Hello thread has ID 2
 * Hello from thread with ID 2
 * Hello thread now has ID thread::id of a non-executing thread
 */