#include <iostream>
#include <thread>
#include <unistd.h>

void do_something(int& i)
{
    ++i;
    std::cout << i << std::endl;
}

void do_something_in_current_thread()
{
	//...
}

struct func
{
	int &i;
	func(int &i_) : i(i_) {}
	void operator()()
	{
		for(unsigned j = 0; i < 1000000; ++j)
			do_something(i);
	}
};

void f()
{
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	try
	{
		do_something_in_current_thread();
	}catch(...)
	{
		t.join();
		throw;
	}
	t.join();
}

int main()
{
	f();
	return 0;
}