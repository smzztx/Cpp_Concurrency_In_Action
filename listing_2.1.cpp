#include <iostream>
#include <thread>
#include <unistd.h>

void do_something(int& i)
{
    ++i;
    std::cout << i << std::endl;
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

void oops()
{
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread my_thread(my_func);
	my_thread.detach();
}

int main()
{
	oops();
	sleep(20);
	return 0;
}