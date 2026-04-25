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
 * Command  : g++ ./pass_ref.cpp -o out -lpthread && ./out
 *
 * str is now xyz
 */