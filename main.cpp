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

void doWork1(std::list<int> &list, std::mutex &mt_list) {
    mt_list.lock();
    int count = 0;
    while (count < 100) {
        count += 2;
        list.push_back(count);
        log(list);
    }
    std::this_thread::sleep_for(4 * std::chrono::seconds(1));
    mt_list.unlock();
}

void doWork2(std::list<int> &list, std::mutex &mt_list) {
    mt_list.lock();
    int count = 0;
    while (count > -100) {
        count -= 2;
        list.push_back(count);
        log(list);
    }
    std::this_thread::sleep_for(4 * std::chrono::seconds(1));
    mt_list.unlock();
}

int main() {
    std::mutex mt;
    std::list<int> list_1 = {};

    std::thread t1(doWork1, std::ref(list_1), std::ref(mt));
    std::thread t2(doWork2, std::ref(list_1), std::ref(mt));
    t1.join();
    t2.join();
    return 0;
}
