# Cpp_Concurrency_In_Action
《C++ Concurrency In Action——Practical Multithreading》笔记

$ g++ -o ex01 ex01.cpp -std=c++11 -pthread


## 目录
- 第1章 你好，C++的并发世界
	- [listing_1.1](listing_1.1.cpp)
		- 使用 std::thread ，和成员函数 join() 。
- 第2章 线程管理
	- [listing_2.1](listing_2.1.cpp)
		- 使用 detach() ；启动一个线程后，可以等待这个线程结束，也可以放在后台运行；放在后台运行时，可能会使用已经销毁的局部变量的指针或引用，导致出错（上述程序测试10次未出现问题，说明该错误并不容易复现）。
    - [listing_2.2](listing_2.2.cpp)
    	- 使用了 try/catch 块确保访问本地状态的线程退出后，函数才结束。
    	- listing2.1 使用了detach()，当主线程结束后，子线程也会结束；listing2.2 使用了join()，主线程会等待子线程结束。
    - [listing_2.3](listing_2.3.cpp)
    	- 自定义一个 thread_guard 类来管理销毁子线程。
    	- `不是只能使用移动来转移线程所有权吗？`
