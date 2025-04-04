#include "thread_pool.h"

ThreadPool::ThreadPool(size_t numThreads) : running(true) {
    for (size_t i = 0; i < numThreads; ++i) {
        threads.push_back(std::thread(&ThreadPool::worker, this));
    }
}

void ThreadPool::worker() {
    while (running) {
        std::function<void()> task;
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            if (!taskQueue.empty()) {
                task = std::move(taskQueue.front());
                taskQueue.pop();
            }
        }
        if (task) {
            task();
        }
    }
}

void ThreadPool::enqueueTask(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        taskQueue.push(task);
    }
}

ThreadPool::~ThreadPool() {
    running = false;
    for (auto& thread : threads) {
        thread.join();
    }
}
