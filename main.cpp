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

void doWork1(std::list<int> &list, bool with_minus, std::mutex &mt1,
             std::mutex &mt2) {
    std::lock_guard<std::mutex> lock_guard1(mt1);
    std::this_thread::sleep_for(1 * std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lock_guard2(mt2);

    int count = 0;
    while (count < 100) {
        count += 2;
        if (!with_minus) {
            list.push_back(count);
        } else {
            list.push_back(-1 * count);
        }
        log(list);
    }
    std::this_thread::sleep_for(4 * std::chrono::seconds(1));
}

int main() {
    std::mutex mt1;
    std::mutex mt2;
    std::list<int> list_1 = {};

    std::thread t1(doWork1, std::ref(list_1), true, std::ref(mt1),
                   std::ref(mt2));
    std::thread t2(doWork1, std::ref(list_1), false, std::ref(mt2),  // mt1
                   std::ref(mt1));  // mt2 the problem will be solved
    t1.join();
    t2.join();
    return 0;
}
