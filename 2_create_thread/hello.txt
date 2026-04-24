// First program with thread
#include <thread>
#include <iostream>

using namespace std;
using namespace std::literals;

// Callable object - thread entry point
void hello() {
    this_thread::sleep_for(2s);
	cout << "Hello, Thread!\n";
}

int main() {
    cout << "Starting thread...\n";
	// Create a thread object
	// Pass the entry point function to the constructor
	thread thr(hello);
	
	// Wait for the thread to complete
	thr.join();
}