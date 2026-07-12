#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

void log(const std::thread::id id, bool is_main, bool is_finish) {
    if (!is_finish) {
        if (is_main) {
            std::cout << "main thread : " << id << " is working\n" << std::endl;
        } else {
            std::cout << "thread : " << id << " is working\n" << std::endl;
        }
    } else {
        if (is_main) {
            std::cout << "main thread : " << id << " is finished\n"
                      << std::endl;
        } else {
            std::cout << "thread : " << id << " is finished\n" << std::endl;
        }
    }
}

class class_test_1 {
   public:
    class_test_1() = default;

    int doWork1(const int a) {
        int res;
        log(std::this_thread::get_id(), false, false);
        std::this_thread::sleep_for(7 * std::chrono::seconds(1));
        res = a * 2;
        log(std::this_thread::get_id(), false, true);
        return res;
    }

    void doWork2() {
        log(std::this_thread::get_id(), false, false);
        std::this_thread::sleep_for(7 * std::chrono::seconds(1));
        log(std::this_thread::get_id(), false, true);
    }

    void doWork3(const int a, int &c) {
        log(std::this_thread::get_id(), false, false);
        std::this_thread::sleep_for(7 * std::chrono::seconds(1));
        c = a * 3;
        log(std::this_thread::get_id(), false, true);
    }

    ~class_test_1() = default;
};

int main() {
    log(std::this_thread::get_id(), true, false);

    class_test_1 class_value;

    int input_value_1 = 9;
    int result_1 = -1;
    std::thread t1([&class_value, input_value_1, &result_1]() {
        result_1 = class_value.doWork1(input_value_1);
    });

    t1.join();
    std::cout << "res 1 = " << result_1 << "\n" << std::endl;

    //    std::thread t2([&class_value]() {
    //        class_value.doWork2(input_value_2, result_2);
    //    });
    std::thread t2(&class_test_1::doWork2, std::ref(class_value));

    t2.join();

    int input_value_3 = 5;
    int result_3 = -1;
    //    std::thread t3([&class_value, input_value_3, &result_3]() {
    //        class_value.doWork3(input_value_3, result_3);
    //    });
    std::thread t3(&class_test_1::doWork3, std::ref(class_value), input_value_3,
                   std::ref(result_3));

    t3.join();
    std::cout << "res 3 = " << result_3 << "\n" << std::endl;

    log(std::this_thread::get_id(), true, true);
    return 0;
}
