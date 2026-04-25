// Example of passing arguments to a thread function by move
#include <iostream>
#include <thread>
#include <string>

using namespace std;

// Thread entry point
// Requires an rvalue argument
void func(string&& str) {
	cout << "Ownership of \"" << str << "\" transferred to thread" << '\n';
}

int main() {
	string str = "moveable";
	cout << "Starting thread" << '\n';

	// Wrap str in a call to move()
	thread thr(func, move(str));
	thr.join();

	// Verify that str has been modified
	cout << "Do I still have any data?" << ' ';
	cout << (str.empty() ? "No" : "Yes") << ".\n";
}

/* === OUTPUT ===
 * Command  : g++ ./move_data.cpp -o out -lpthread && ./out
 *
 * Starting thread
 * Ownership of "moveable" transferred to thread
 * Do I still have any data? No.
 */