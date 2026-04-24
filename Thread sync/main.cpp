// Example using promise and shared_future
// to send a result from a producer thread
// to multiple consumer threads
#include <future>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
using namespace std::literals;

// The producer's task function takes a promise as argument
void produce(promise<int>& px)
{
	// Produce the result
    int x = 533;
    this_thread::sleep_for(2s);
	
	// Store the result in the shared state
	cout << "Promise sets shared state to " << x << '\n';
    px.set_value(x);
}

// The consumer's task function takes a shared_future as argument
void consume(shared_future<int>& fx)
{
	// Get the result from the shared state
	cout << "Thread " << this_thread::get_id() << " calling get()...\n";
    int x = fx.get();

    cout << "Thread " << this_thread::get_id() << " returns from calling get()\n";
	cout << "Thread " << this_thread::get_id() << " has answer " << x << '\n';
}

int main() {
	// Create a promise object
	// This creates an associated future object
	// and sets up a shared state between them
    promise<int> prom;
	
	// Get a shared_future associated with the promise
	// This will move the promise's future into a shared future
    shared_future<int> shared_fut1 = prom.get_future();
	
	// Copy the shared future object
    shared_future<int> shared_fut2 = shared_fut1;

	// Start the threads
	// The producer task function takes the promise as argument
	thread thr_producer(produce, ref(prom));	
	
	// Start two consumer threads
	// The consumer task function takes a shared future as argument
	// Each thread uses a different shared future object
	thread thr_consumer1(consume, ref(shared_fut1));
	thread thr_consumer2(consume, ref(shared_fut2));

    thr_consumer1.join();
    thr_consumer2.join();
    thr_producer.join();
}