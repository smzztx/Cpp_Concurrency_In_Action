#include <iostream>
#include <thread>

void do_something(int& i)
{
    ++i;
    std::cout << i << std::endl;
}

class thread_guard
{
	std::thread &t;
public:
	explicit thread_guard(std::thread &t_) : t(t_) {}
	~thread_guard()
	{
		if(t.joinable())
		{
			t.join();
		}
	}
	thread_guard(thread_guard const&) = delete;
	thread_guard &operator=(thread_guard const&) = delete;
};

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
	thread_guard g(t);
	do_something_in_current_thread();
}

int main()
{
	f();
	return 0;
}