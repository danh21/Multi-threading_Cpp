// Broken implementation of lock-free queue (has data race)
#include <vector>
#include <list>
#include <thread>
#include <iostream>

using namespace std;

template <typename T>
struct LockFreeQueue {
private:
	// Use a list to store the elements
	list<T> lst;

	// iHead and iTail iterators
	typename list<T>::iterator iHead, iTail;

    mutex m;
    
    bool firstConsume = false;
public:
	// Class constructor
	LockFreeQueue()
	{
		// Create a "dummy" element to separate iHead from iTail
		lst.push_back(T());
		iHead = lst.begin();
		iTail = lst.end();
	}

	// Producer thread function
	void Produce(const T t)
	{
	    lock_guard<mutex> lock(m);
		// Add the new element
		lst.push_back(t);

		// Update iTail
		iTail = lst.end();

		// Erase the removed elements
		lst.erase(lst.begin(), iHead);
	}

	// Consumer thread function
	void Consume()
	{
	    lock_guard<mutex> lock(m);
	    ++iHead;
	}

	// Function to display all the elements
	void Print()
	{
		// Go to the first element, skip dummy element
		auto head = iHead;
		++head;

		// We cannot use a range-for loop, because we only access some of the elements
		for (auto el = head; el != iTail; ++el)
			cout << *el << " ";
		cout << '\n';
	}
}; // End of class definition

int main()
{
	LockFreeQueue<int> lfq;
	vector<thread> threads;

	for (int i = 0; i < 10; ++i) {
		// Run the member functions of LockFreeQueue in threads
		// Syntax for member function with thread:
		// First argument is a pointer to the member function
		// Second argument is the address of the object the member function is called on
		// (this will be the "this" pointer in the member function)
		thread produce(&LockFreeQueue<int>::Produce, &lfq, i);
		threads.push_back(move(produce));
	}
	
	for (int i = 0; i < 5; i++) {
	    thread consume(&LockFreeQueue<int>::Consume, &lfq);
		threads.push_back(move(consume));
	}

	// Wait for the threads to complete
	for (auto& thr: threads)
		thr.join();

	lfq.Print();
}