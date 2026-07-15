#include <chrono>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

void log(const int num) { std::cout << num << " \n"; }

void doWork(const int num, std::recursive_mutex &mt1) {
    std::lock_guard<std::recursive_mutex> lock_guard(mt1);
    // mt1.lock();
    if (num < 0) {
        std::cout << std::endl;
        mt1.unlock();
        return;
    }
    log(num);
    std::this_thread::sleep_for(1 * std::chrono::milliseconds(200));
    doWork(num - 1, mt1);
    // mt1.unlock();
}

int main() {
    std::recursive_mutex mt1;

    std::thread t1(doWork, 10, std::ref(mt1));
    std::this_thread::sleep_for(1 * std::chrono::milliseconds(10));
    std::thread t2(doWork, 30, std::ref(mt1));
    t1.join();
    t2.join();
    return 0;
}
