#include <chrono>
#include <functional>
#include <iostream>
#include <list>
#include <mutex>
#include <thread>

void log(const std::list<int> &list) {
    std::cout << "\nlist: [ ";
    for (int i : list) {
        std::cout << i << ", ";
    }
    std::cout << " ]\n" << std::endl;
}

void doWork1(std::list<int> &list, bool is_minus, std::mutex &mt1) {
    std::unique_lock<std::mutex> unique_lock_1(
        mt1,
        std::defer_lock);  // usual unique_lock    std::unique_lock<std::mutex>
                           // unique_lock_1(mt1); with lock at the begining
    // asynchronous
    std::this_thread::sleep_for(5 * std::chrono::seconds(1));

    // synchronous
    unique_lock_1.lock();

    int q = 1;
    if (is_minus) {
        q = -1;
    }
    int count = 0;
    while (count < 100) {
        count += 2;
        list.push_back(count * q);
        log(list);
    }

    unique_lock_1.unlock();

    // asynchronous
    std::this_thread::sleep_for(5 * std::chrono::seconds(1));
}

int main() {
    std::mutex mt;
    std::list<int> list_1;

    std::thread t1(doWork1, std::ref(list_1), false, std::ref(mt));
    std::thread t2(doWork1, std::ref(list_1), true, std::ref(mt));
    t1.join();
    t2.join();
    return 0;
}