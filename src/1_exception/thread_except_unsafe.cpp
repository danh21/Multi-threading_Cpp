// What happens to a thread object
// when an exception is thrown?
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
	try {
		// Create a thread object
		thread thr(hello);

		// Code that might throw an exception
		throw exception();

		thr.join();
	}
	catch (exception& e) {
		cout << "Exception caught: " << e.what() << '\n';
	}
}
/* === OUTPUT ===
 * Compiled : 2026-04-24 16:11:06
 * Command  : g++ ./thread_except_unsafe.cpp -o out && ./out
 *
 * Hello, Thread!
 * terminate called without an active exception
 */
