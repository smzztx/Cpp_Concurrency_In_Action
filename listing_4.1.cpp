#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <unistd.h>

struct data_chunk {};

bool more_data_to_prepare() { return true; }

void process(data_chunk) {}

bool is_last_chunk(data_chunk) { return true; }

data_chunk prepare_data()
{
    return data_chunk();
}

std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

void data_preparation_thread()
{
    while(more_data_to_prepare())
    {
        std::cout << "data_preparation_thread1" << std::endl;
        data_chunk const data = prepare_data();
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
        return;
    }
}

void data_processing_thread()
{
    while(true)
    {
        std::cout << "data_processing_thread1" << std::endl;
        std::unique_lock<std::mutex> lk(mut);
        std::cout << "data_processing_thread2" << std::endl;
        data_cond.wait(lk, []{ return !data_queue.empty(); });
        std::cout << "data_processing_thread3" << std::endl;
        data_chunk data = data_queue.front();
        data_queue.pop();
        lk.unlock();
        process(data);
        std::cout << "data_processing_thread4" << std::endl;
        if(is_last_chunk(data))
            break;
    }
}

int main()
{
    std::thread t2(data_processing_thread);
    sleep(1);
    std::thread t1(data_preparation_thread);

    t1.join();
    t2.join();

    return 0;
}
