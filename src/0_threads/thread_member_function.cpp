// Example of using a member function as a thread's entry point
#include <thread>
#include <iostream>

using namespace std;

// Class whose member function
// will be used as the thread's entry point
class greeter {
public:
	void hello() {
		cout << "Hello, Member Function Thread!\n";
	}
};

int main() {
	// Create an object of the class
	greeter greet;

	// Create an thread object
	// Pass a pointer to the member function
	// and a pointer to the object to call it on
	thread thr(&greeter::hello, &greet);

	thr.join();
}
/* === OUTPUT ===
 * Compiled : 2026-04-24 15:30:36
 * Command  : g++ ./thread_member_function.cpp -o out && ./out
 *
 * Hello, Member Function Thread!
 */
