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
    - [listing_2.4](listing_2.4.cpp)
    	- 打开一个新文档后分离线程。
    	- std::thread 还可以传递函数所需的参数。
    - [2.2 向线程函数传递参数](2.2.cpp)
    	- 传参时，引用会被复制进线程中；如需使用引用，请使用 std::ref。
    	- 指向动态变量的指针作为参数传递给线程时，函数有很有可能会在字面值转化成 std::string 对象之前崩溃(oops)，从而导致一些未定义的行为。（可能是局部变量buffer被销毁）
    	- 可以传递一个成员函数指针作为线程函数，并提供一个合适的对象指针作为第一个参数。
    - [listing_2.5](listing_2.5.cpp)
    	- std::thread 支持移动。
    - [listing_2.6](listing_2.6.cpp)
    	- 使用移动时，在构造函数处检查 joinable()。
    - [listing_2.7](listing_2.7.cpp)
    - [listing_2.8](listing_2.8.cpp)
    - 2.5 标识线程
    	- 线程标识类型是 std::thread::id，可以通过两种方式进行检索。第一种，可以通过调用 std::thread 对象的成员函数 get_id() 来直接获取；第二种，当前线程中调用 std::this_thread::get_id() 也可以获得线程标识。
    	- 如果两个对象的 std::thread::id 相等，那它们就是同一个线程，或者都“无线程”。如果不等，那么就代表了两个不同线程，或者一个有线程，另一没有线程。具体的输出结果是严格依赖于具体实现的，C++ 标准的唯一要求就是要保证ID比较结果相等的线程，必须有相同的输出 。
- 第3章 线程间共享数据
	- [listing_3.1](listing_3.1.cpp)
		- 使用互斥量。
		- [listing_3.2](listing_3.2.cpp)
			- 当其中一个成员函数返回的是保护数据的指针或引用时，会破坏对数据的保护。
        - [listing_3.3](listing_3.3.cpp)
        - [listing_3.4](listing_3.4.cpp)
        - [listing_3.5](listing_3.5.cpp)
        	- 使用安全的接口，pop()接口：
        		- 传入一个引用。
        		- 无异常抛出的拷贝构造函数或移动构造函数。
        		- 返回指向弹出值的指针。
        - [listing_3.6](listing_3.6.cpp)
        	- 当一个类有2个互斥量时，一个线程先锁A互斥量再锁B，另一个先锁B再锁A，这样就可能造成死锁。
        	- 当 std::lock 成功的获取一个互斥量上的锁，并且当其尝试从另一个互斥量上再获取锁时，就会有异常抛出，第一个锁也会随着异常的产生而自动释放，所以 std::lock 要么将两个锁都锁住，要不一个都不锁。
        - [listing_3.7](listing_3.7.cpp)
        	- 分层互斥。
        - [listing_3.8](listing_3.8.cpp)
        	- static thread_local ，每个线程只有一个该变量，变量的状态完全独立。
        - [listing_3.9](listing_3.9.cpp)
        	- 