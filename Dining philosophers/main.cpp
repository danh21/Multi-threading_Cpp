#include <thread>
#include <print>

using namespace std;

int x{0};

void func(int a) {
    println("{} start", a);
    while (x == 0) {
        x = 1 - x;
    }
    println("{} end", a);
}

int main()
{
    thread thr1{ func,1 };
    thread thr2{ func,2 };
	
	thr1.join();
	thr2.join();
}

