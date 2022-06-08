#pragma once


ThreadPool::ThreadPool(size_t poolSize){
    size_ = poolSize;
    threads_.reserve(poolSize);
    for (size_t i=0; i<poolSize; i++)
        threads_.push_back(std::thread(ThreadPool::computer, this));
}

ThreadPool::~ThreadPool(){
    std::unique_lock<std::mutex> lock(this->mutex_);
    this->destruction_ = true;
    lock.unlock();
    this->alarm_.notify_all();
    for (size_t i=0; i<size_; i++){
        threads_[i].join();
    }
}

void ThreadPool::computer(ThreadPool* pool){
    while(true){
        std::unique_lock<std::mutex> lock(pool->mutex_);
        pool->alarm_.wait(lock, [pool](){
            return !pool->queue_.empty() || pool->destruction_;
        });

        if (pool->destruction_)
            return;

        std::function<void()> task = pool->queue_.front();
        pool->queue_.pop();
        lock.unlock();
        task();
    }
}

template <class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))>{

    auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>(std::bind(func, args...));
    auto future = task->get_future();

    std::unique_lock<std::mutex> lock(this->mutex_);
    this->queue_.emplace([task]{(*task)();});
    lock.unlock();
    this->alarm_.notify_one();

    return future;
}
