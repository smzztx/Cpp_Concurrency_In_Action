# Cpp_Concurrency_In_Action
《C++ Concurrency In Action——Practical Multithreading》笔记

$ g++ -o ex01 ex01.cpp -std=c++11 -pthread
$ g++ -o listing_3.13 listing_3.13.cpp -std=c++11 -lboost_system

thread_local mutable

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
        - std::unique_lock 实例没有与自身相关的互斥量，一个互斥量的所有权可以通过移动操作，在不同的实例中进行传递。
    - [listing_3.10](listing_3.10.cpp)
        - 获取值之后，两个值可能会变化，这样会失去比较的意义。
    - [listing_3.11](listing_3.11.cpp)
        - 没有必要每次都获取锁。C++ 标准提供了一种纯粹保护共享数据初始化过程的机制。
    - [listing_3.12](listing_3.12.cpp)
        - 可以使用 std::once_flag 和 std::call_once 来处理这种情况。比起锁住互斥量，并显式的检查指针，每个线程只需要使用 std::call_once，在 std::call_once 的结束时，就能安全的知道指针已经被其他的线程初始化了。使用 std::call_once 比显式使用互斥量消耗的资源更少，特别是当初始化完成后。
    - [listing_3.13](listing_3.13.cpp)
        - 读者-作者锁。对于更新操作，可以使用 std::lock_guard<boost::shared_mutex> 和 std::unique_lock<boost::shared_mutex>上锁。作为 std::mutex 的替代方案，与 std::mutex 所做的一样，这就能保证更新线程的独占访问。因为其他线程不需要去修改数据结构，所以其可以使用 boost::shared_lock<boost::shared_mutex> 获取访问权。
    - 嵌套锁。std::recursive_mutex 类，使用该类时需要合理规划，因为前一次锁未解之前，被保护的对象可能还在被修改。
- 第4章 同步并发操作
	- [listing_4.1](listing_4.1.cpp)
		- 实现条件变量 std::condition_variable。
		- 当条件不满足时，线程将对互斥量解锁，并且重新开始等待。这就是为什么用 std::unique_lock 而不使用 std::lock_guard ——等待中的线程必须在等待期间解锁互斥量，并在这这之后对互斥量再次上锁，而 std::lock_guard 没有这么灵活。
	- [listing_4.2](listing_4.2.cpp)
	- [listing_4.3](listing_4.3.cpp)
	- [listing_4.4](listing_4.4.cpp)
	- [listing_4.5](listing_4.5.cpp)
		- 如果锁住互斥量是一个可变操作，那么这个互斥量对象就会标记为可变的，之后他就可以在 empty() 和拷贝构造函数中上锁了。
		- 当新的数据准备完成，调用 notify_one() 将会触发一个正在执行 wait() 的线程，去检查条件和 wait() 函数的返回状态(因为你仅是向 data_queue 添加一个数据项)。这里不保证线程一定会被通知到，即使只有一个等待线程被通知时，所有处线程也有可能都在处理数据。
		- 另一种可能是，很多线程等待同一事件，对于通知他们都需要做出回应。在这些情况下， 准备线程准备数据数据时，就会通过条件变量调用 notify_all() 成员函数，而非直接调用 notify_one() 函数。
		- 当等待线程只等待一次，当条件为 true 时，它就不会再等待条件变量了，所以一个条件变量可能并非同步机制的最好选择。尤其是，条件在等待一组可用的数据块时。在这样的情况下，期望(future)就是一个适合的选择。
	- [listing_4.6](listing_4.6.cpp)
	- [listing_4.7](listing_4.7.cpp)
		- 使用期望 std::future 和 std::async 。
		- std::async(baz, std::ref(x))会报错，必须为auto f = std::async(baz, std::ref(x))。
	- [listing_4.8](listing_4.8.cpp)
	- [listing_4.9](listing_4.9.cpp)
		- 使用“任务”，std::packaged_task。
	- [listing_4.10](listing_4.10.cpp)
		- 使用“承诺”，std::promise。
	- [listing_4.11](listing_4.11.cpp)
		- wait_for + 时间段；wait_until + 时间点。
	- [listing_4.12](listing_4.12.cpp)
		- 快速排序，顺序实现版。
	- [listing_4.13](listing_4.13.cpp)
    	- 快速排序，“期望”并行版。
    	- 当任务过多时(已影响性能)，这些任务应该在使用 get() 函数获取的线程上运行，而不是在新线程上运行，这样就能避免任务向线程传递的开销。值得注意的是，这完全符合 std::async 的实现，为每一个任务启动一个线程(甚至在任务超额时；使用同步操作简化代码在 std::launch::deferred 没有明确规定的情况下)；或为了同步执行所有任务(在 std::launch::async 有明确规定的情况下)。当你依赖运行库的自动缩放，建议你去查看一下你的实 现文档，了解一下将会有怎么样的行为表现。
    - [listing_4.14](listing_4.14.cpp)
    - [listing_4.15](listing_4.15.cpp)
    	- Actor model，这里不太懂。
    - [listing_4.16](listing_4.16.cpp)
- 第5章 C++内存模型和原子类型操作
	- 


---------
https://github.com/anthonywilliams/ccia_code_samples.git