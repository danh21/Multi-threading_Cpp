// Use defer_lock to avoid deadlock
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
    unique_lock<mutex> uniq_lk1(mut1, defer_lock);   // Associate mutex with lock...
    unique_lock<mutex> uniq_lk2(mut2, defer_lock);   // ...but don't lock it yet
	
	cout << "Thread A trying to lock mutexes 1 and 2...\n";
    
	// Now lock both of them
	auto idx = try_lock(uniq_lk1, uniq_lk2);
	if (idx != -1) {
		cout << "Thread A try_lock failed on mutex with index " << idx << '\n';
	}
	else {
		cout << "Thread A has locked mutexes 1 and 2\n";
		this_thread::sleep_for(50ms);
		cout << "Thread A releasing mutexes 1 and 2...\n";
	}
}

void funcB() {
    unique_lock<mutex> uniq_lk2(mut2, defer_lock);   // Associate mutex with lock...
    unique_lock<mutex> uniq_lk1(mut1, defer_lock);   // ...but don't lock it yet
	
	cout << "Thread B trying to lock mutexes 2 and 1...\n";
    
	// Now lock both of them
	auto idx = try_lock(uniq_lk2, uniq_lk1);
	if (idx != -1) {
		cout << "Thread B try_lock failed on mutex with index " << idx << '\n';
	}
	else {
		cout << "Thread B has locked mutexes 2 and 1\n";
		this_thread::sleep_for(50ms);
		cout << "Thread B releasing mutexes 2 and 1...\n";
	}
}

int main() {
	thread thrA(funcA);
	thread thrB(funcB);
	
	thrA.join(); thrB.join();
}
