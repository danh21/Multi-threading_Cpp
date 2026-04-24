// Example of passing arguments to a thread function by reference
#include <thread>
#include <iostream>
#include <string>

using namespace std;

// Thread entry point
void hello(string& s) {
	s = "xyz";
}

int main() {
	string str = "abc" ;

	// Wrap argument in a call to ref()
// 	thread thr(hello, str); //error
	thread thr(hello, ref(str));
	thr.join();

	// Verify that it has been modified
	cout << "str is now " << str << '\n';
}
/* === OUTPUT ===
 * Compiled : 2026-04-24 15:30:39
 * Command  : g++ ./thread_ref.cpp -o out && ./out
 *
 * str is now xyz
 */
