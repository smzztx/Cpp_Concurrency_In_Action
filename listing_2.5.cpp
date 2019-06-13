#include <iostream>
#include <thread>

void some_function()
{

}

void some_other_function(int i)
{
	std::cout << i << std::endl;
}

std::thread f()
{
	return std::thread(some_function);
}

std::thread g()
{
	std::thread t(some_other_function, 42);
	return t;
}

int main()
{
	std::thread t1 = f();
	if(t1.joinable())
	{
		t1.join();
	}

	std::thread t2 = g();
	if(t2.joinable())
	{
		t2.join();
	}

	return 0;
}