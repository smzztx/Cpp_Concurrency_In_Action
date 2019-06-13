#include <iostream>
#include <thread>
#include <algorithm>
#include <list>
#include <mutex>

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value)
{
	std::lock_guard<std::mutex> guard(some_mutex);
	some_list.push_back(new_value);
}

bool list_contains(int value_to_find)
{
	std::lock_guard<std::mutex> guard(some_mutex);
	return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}

int main()
{
	add_to_list(1);
	std::cout << std::boolalpha << list_contains(1) << std::endl;
	std::cout << std::boolalpha << list_contains(0) << std::endl;

	return 0;
}