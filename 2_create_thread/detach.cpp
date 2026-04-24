// thread and detach()
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
	
	// Detach the child thread
	thr.detach();
	
	// Continue executing without waiting for the child thread
}