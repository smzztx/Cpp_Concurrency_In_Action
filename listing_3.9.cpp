#include <exception>
#include <memory>
#include <stack>
#include <mutex>
#include <iostream>

class some_big_object {};
void swap(some_big_object &lhs, some_big_object &rhs) {}
class X
{
private:
	some_big_object some_detail;
	std::mutex m;
public:
	X(some_big_object const &sd) : some_detail(sd) {}
	friend void swap(X &lhs, X &rhs)
	{
		if(&lhs == &rhs) return;
		std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);
		std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock);
		std::lock(lhs.m, rhs.m);
		swap(lhs.some_detail, rhs.some_detail);
	}
};

int main()
{
	return 0;
}