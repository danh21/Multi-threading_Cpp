// Example of a thread which throws an exception
#include <thread>
#include <iostream>

using namespace std;

// Task function
void hello() {
	try {
		// Throw an exception
		throw exception();
	}
	catch (exception& e) {
		cout << "Exception caught: " << e.what() << '\n';
	}
	cout << "Hello, Thread!\n";
}

int main() {
	// Create a thread object
	thread thr(hello);
	thr.join();

	// Check that the program is still running
	cout << "Finished\n";
}