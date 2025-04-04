#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

enum class TaskType { CPU_BOUND, IO_BOUND };

class ThreadPool {
public:
    ThreadPool(size_t numThreads);
    void enqueueTask(std::function<void()> task, TaskType taskType);
    void stop();
    ~ThreadPool();

private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> cpuQueue;
    std::queue<std::function<void()>> ioQueue;
    std::mutex cpuMutex;
    std::mutex ioMutex;
    std::condition_variable cv;
    bool running;
    void worker(TaskType taskType);
};

ThreadPool::ThreadPool(size_t numThreads) : running(true) {
    for (size_t i = 0; i < numThreads; ++i) {
        threads.push_back(std::thread(&ThreadPool::worker, this, TaskType::CPU_BOUND));
        threads.push_back(std::thread(&ThreadPool::worker, this, TaskType::IO_BOUND));
    }
}

void ThreadPool::worker(TaskType taskType) {
    while (running) {
        std::function<void()> task;

        if (taskType == TaskType::CPU_BOUND) {
            std::unique_lock<std::mutex> lock(cpuMutex);
            if (!cpuQueue.empty()) {
                task = std::move(cpuQueue.front());
                cpuQueue.pop();
            }
        } else {
            std::unique_lock<std::mutex> lock(ioMutex);
            if (!ioQueue.empty()) {
                task = std::move(ioQueue.front());
                ioQueue.pop();
            }
        }

        if (task) {
            task();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Simulate I/O wait or task process time
    }
}

void ThreadPool::enqueueTask(std::function<void()> task, TaskType taskType) {
    if (taskType == TaskType::CPU_BOUND) {
        std::lock_guard<std::mutex> lock(cpuMutex);
        cpuQueue.push(task);
    } else {
        std::lock_guard<std::mutex> lock(ioMutex);
        ioQueue.push(task);
    }
    cv.notify_one();
}

void ThreadPool::stop() {
    running = false;
    for (auto& thread : threads) {
        thread.join();
    }
}

ThreadPool::~ThreadPool() {
    stop();
}
