// Mutual deadlock
// Two threads wait for the other to unlock a mutex
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::literals;

mutex mut1;
mutex mut2;

void funcA()
{
	cout << "Thread A trying to lock mutex 1...\n";
	lock_guard<mutex> lck_guard(mut1);		// Acquire lock on mut1
	cout << "Thread A has locked mutex 1\n";
	this_thread::sleep_for(50ms);	                // Do some work
	cout << "Thread A trying to lock mutex 2...\n";
	lock_guard<mutex> lck_guard2(mut2);		// Wait for lock on mut2
	cout << "Thread A has locked mutex 2\n";
	this_thread::sleep_for(50ms);	                // Do some work
	cout << "Thread A releases all its locks\n";
}

void funcB()
{
	cout << "Thread B trying to lock mutex 2...\n";
	lock_guard<mutex> lck_guard1(mut2);	    // Acquire lock on mut2
	cout << "Thread B has locked mutex 2\n";
	this_thread::sleep_for(50ms);	                // Do some work
	cout << "Thread B trying to lock mutex 1...\n";
	lock_guard<mutex> lck_guard2(mut1);	    // Wait for lock on mut1
	cout << "Thread B has locked mutex 1\n";
	this_thread::sleep_for(50ms);	                // Do some work
	cout << "Thread B releases all its locks\n";
}

int main()
{
	thread thrA(funcA);
	thread thrB(funcB);
	
	thrA.join(); thrB.join();
}