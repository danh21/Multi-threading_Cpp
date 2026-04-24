// Example of a thread which throws an uncaught exception
#include <thread>
#include <iostream>

using namespace std;

// Task function
void hello() {
	throw exception();

	cout << "Hello, Thread!\n";
}

int main() {
	// Create a thread object
	try {
		thread thr{hello};
		thr.join();
	}
	catch (exception& e) {
		cout << "Exception caught: " << e.what() << '\n';
	}

	// Check that the program is still running
	cout << "Finished\n";
}
/* === OUTPUT ===
 * Compiled : 2026-04-24 16:11:11
 * Command  : g++ ./uncaught_exception.cpp -o out && ./out
 *
 * terminate called after throwing an instance of 'std::exception'
 *   what():  std::exception
 */
