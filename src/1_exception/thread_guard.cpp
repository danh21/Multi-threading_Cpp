// Uses a wrapper class for thread
// Ensures safe destruction when an exception is throw
#include <thread>
#include <iostream>

using namespace std;

class thread_guard {
	thread thr;
public:
	// Constructor takes rvalue reference argument (thread is move-only)
	explicit thread_guard(thread&& thr): thr(move(thr)) {
	}

	// Destructor - join the thread if necessary
	~thread_guard()
	{
		if (thr.joinable())
			thr.join();
	}

	thread_guard(const thread_guard&) = delete;       // Deleted copy operators prevent copying
	thread_guard& operator=(const thread_guard&) = delete;

	// The move assignment operator is not synthesized
};

// Callable object - thread entry point
void hello()
{
	cout << "Hello, Thread!\n";
}

int main()
{
	try {
		thread thr(hello);
		thread_guard tguard{move(thr)};

		//thread_guard tguard{thread(hello)};

		// Code which might throw an exception
		throw exception();

	} // Calls ~thread_guard followed by ~thread

	catch (exception& e) {
		cout << "Exception caught: " << e.what() << '\n';
	}
}
/* === OUTPUT ===
 * Compiled : 2026-04-24 16:11:09
 * Command  : g++ ./thread_guard.cpp -o out && ./out
 *
 * Hello, Thread!
 * Exception caught: std::exception
 */
