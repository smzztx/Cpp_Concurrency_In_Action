# Cpp_Concurrency_In_Action
《C++ Concurrency In Action——Practical Multithreading》笔记

$ g++ -o ex01 ex01.cpp -std=c++11 -pthread
测试10次未出现问题，该错误并不容易复现。
第1章 你好，C++的并发世界
[listing_1.1](listing_1.1.cpp)
使用std::thread，和成员函数join()。
第2章 线程管理
[listing_2.1](listing_2.1.cpp)
启动一个线程后，可以等待这个线程结束，也可以放在后台运行；放在后台运行时，可能会使用已经销毁的局部变量的指针或引用，导致出错（上述程序测试10次未出现问题，说明该错误并不容易复现。）。
