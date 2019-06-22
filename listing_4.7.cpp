#include <future>
#include <iostream>
#include <unistd.h>
#include <string>

struct X
{
    void foo(int, std::string const&) {}
    std::string bar(std::string const&) { return std::string("abc"); }
};

X x;
auto f1 = std::async(&X::foo, &x, 42, "hello");
auto f2 = std::async(&X::bar, &x, "goodbye");

struct Y
{
    double operator()(double) { return 3.14; }
};

Y y;
// auto f3 = std::async(&Y::operator(), &y, 3.14);
auto f3 = std::async(y, 3.14);
auto f4 = std::async(std::ref(y), 2.718);
X baz(X&) {}
auto f = std::async(baz, std::ref(x));   //must use auto f = std::async(baz, std::ref(x)); std::async(baz, std::ref(x)) will be error!

class move_only
{
public:
    move_only() {}
    move_only(move_only&&) {}
    move_only(move_only const&) = delete;
    move_only& operator=(move_only&&) {}
    move_only& operator=(move_only const&) = delete;
    void operator()() {}
};

auto f5 = std::async(move_only());

int main()
{
    return 0;
}