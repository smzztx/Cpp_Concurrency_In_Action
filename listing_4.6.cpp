#include <future>
#include <iostream>
#include <unistd.h>

int find_the_answer_to_ltuae()
{
    std::cout << "int find_the_answer_to_ltuae()1" << std::endl;
    // sleep(1);
    std::cout << "int find_the_answer_to_ltuae()2" << std::endl;
    return 2333;
}

void do_other_stuff()
{
    std::cout << "void do_other_stuff()" << std::endl;
}

int main()
{
    std::future<int> the_answer = std::async(find_the_answer_to_ltuae);
    // sleep(2);
    do_other_stuff();
    std::cout << "the answer is " << the_answer.get() << std::endl;

    return 0;
}