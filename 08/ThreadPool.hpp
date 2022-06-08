#pragma once


#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool{

private:

    size_t size_;
    std::condition_variable alarm_;
    bool destruction_ = false;
    std::mutex mutex_;
    std::vector<std::thread> threads_;
    std::queue<std::function<void()>> queue_;

    static void computer(ThreadPool*);

public:

    explicit ThreadPool(size_t poolSize);
    ~ThreadPool();

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
};

#include "ThreadPool.tpp"
