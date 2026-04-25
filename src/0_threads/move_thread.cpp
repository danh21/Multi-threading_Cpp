// Example of passing a thread object to a function
#include <thread>
#include <iostream>

using namespace std;

// The task function
void hello() {
	using namespace literals;
	this_thread::sleep_for(1s);
	cout << "Hello, Thread!\n";
}

// Function taking a thread object as argument
// The object must be moved into the argument
void func(thread thr) {
	cout << "Received thread with ID " << thr.get_id() << endl;

	// The function argument now "owns" the system thread
	// It is responsible for calling join()
	thr.join();
}

int main() {
	// thread is a move-only object
	thread thr(hello);

	// Display the child thread's ID
	cout << "Hello thread has ID " << thr.get_id() << '\n';

	// Pass a named object using move()
	func(move(thr));

	// Pass a temporary object
	//func(thread(hello));
}

/* === OUTPUT ===
 * Command  : g++ ./move_thread.cpp -o out -lpthread && ./out
 *
 * Hello thread has ID 2
 * Received thread with ID 2
 * Hello, Thread!
 */