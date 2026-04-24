// Lazy initialization (multi-threaded)
// Uses Meyers singleton
#include <mutex>
#include <thread>
#include <iostream>

using namespace std;

class Test {
	// ...
public:
	Test()
	{
		cout << "Test constructor called\n";
	}

	void func()
	{
		/*...*/
	}
};

void process()
{
	static Test ptest;            // Variable which is lazily initialized
	ptest.func();
}

int main()
{
	thread thr1(process);
	thread thr2(process);
	thr1.join(); thr2.join();
}