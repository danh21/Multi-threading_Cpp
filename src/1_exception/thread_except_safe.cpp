// Safely destroying a thread object
// when an exception is thrown (verbose)
#include <thread>
#include <iostream>

using namespace std;

// Callable object - thread entry point
void hello()
{
	cout << "Hello, Thread!\n";
}

int main()
{
	// Create a thread object
	thread thr(hello);

	try {
		// Code that might throw an exception
		throw exception();

		// No exception if we got here - call join() as usual
		thr.join();
	}
	catch (exception& e) {
		cout << "Exception caught: " << e.what() << '\n';
		thr.join();                           // Call join() before thr's destructor is called
	}
} // Calls ~thr()
/* === OUTPUT ===
 * Compiled : 2026-04-24 16:11:04
 * Command  : g++ ./thread_except_safe.cpp -o out && ./out
 *
 * Exception caught: std::exception
 * Hello, Thread!
 */
