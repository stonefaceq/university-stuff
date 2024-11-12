#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>


std::mutex familiesFileMutex, monkeysFileMutex;
std::mutex familiesIndexMutex, monkeysIndexMutex;
std::mutex familiesGarbageMutex, monkeysGarbageMutex;

std::condition_variable familiesCondition, monkeysCondition;
std::queue<std::function<void()>> familiesQueue, monkeysQueue;

void processFamily(const std::function<void()>& task) {
    std::unique_lock<std::mutex> lock(familiesFileMutex);
    task();
}

void processMonkey(const std::function<void()>& task) {
    std::unique_lock<std::mutex> lock(monkeysFileMutex);
    task();
}

void workerFamily() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(familiesFileMutex);
            familiesCondition.wait(lock, [&]() { return !familiesQueue.empty(); });
            task = std::move(familiesQueue.front());
            familiesQueue.pop();
        }
        task();
    }
}

void workerMonkey() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(monkeysFileMutex);
            monkeysCondition.wait(lock, [&]() { return !monkeysQueue.empty(); });
            task = std::move(monkeysQueue.front());
            monkeysQueue.pop();
        }
        task();
    }
}
