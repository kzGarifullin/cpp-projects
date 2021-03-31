#include<boost/lockfree/stack.hpp>
#include<iostream>
#include<chrono>
#include<vector>
#include<algorithm>
#include <random>
#include <math.h>
#include <thread>
#include <functional>
#include <atomic>
#include <exception>
#include <memory>
#include <mutex>
#include <stack>
#include <stdexcept>
std::atomic<bool> go(false);
struct Life
{
    int x, y, z;
};

void trigonom(boost::lockfree::stack<int> &stack)
{
    while (!go)
        std::this_thread::yield();
    for (unsigned i = 0; i < 100000; ++i)
    {
        stack.push(5);
        std::this_thread::yield();
        
    }
}
void read_vals(boost::lockfree::stack<int> &stack)
{
    while (!go)
        std::this_thread::yield();

    //local=local+ life.x + life.y + life.z;
    int value;
    stack.pop(value);
    std::this_thread::yield();

}
class Timer
{
public:
    using clock_t = std::chrono::steady_clock;
    using time_point_t = clock_t::time_point;
    void pause()
    {
        pa = clock_t::now();
        dur += std::chrono::duration_cast<std::chrono::microseconds>(
            pa - m_begin);
    }
    void cont()
    {
        m_begin = clock_t::now();
    }
    Timer() : m_begin(clock_t::now()), dur(0) {}
    ~Timer()
    {
        auto end = clock_t::now();
        std::cout << "micro: " << std::chrono::duration_cast<std::chrono::microseconds>(
            end - m_begin).count() + dur.count() << std::endl;
    }
private:
    time_point_t m_begin;
    time_point_t pa;
    std::chrono::microseconds dur;
};
int main(int argc, char* argv[])
{
    boost::lockfree::stack<int> stack(100);
    
    for (int i = 0; i < 100; i++) {
        stack.push(5);
    }
    std::vector < std::thread > threads;
    std::atomic<double> local = 0.0;
    for (std::size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
    {
        threads.push_back(std::thread(trigonom, std::ref(stack)));
    }

    for (std::size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
    {
        threads.push_back(std::thread(read_vals, std::ref(stack)));
    }
    Timer T;
    go = true;
    std::for_each(threads.begin(), threads.end(),
        std::mem_fn(&std::thread::join));
    

}
