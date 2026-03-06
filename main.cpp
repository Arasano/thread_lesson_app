#include <iostream>
#include <thread>
#include <chrono>
#include <functional>


void doWork(const int a, const int b,int &c)
{
    std::this_thread::sleep_for(2 * std::chrono::seconds(1));
    c = a + b;
}

int main(){
    int q = -1;

    std::thread t1([&q](){
        while(true)
        {
            std::this_thread::sleep_for(2 * std::chrono::seconds(1));
            std::cin >> q;

            if (q == 0)
                break;
        }
    });


    std::thread t2([&q](){
        int count = 0;
        while(true)
        {
            std::string str = "-----------------------------------";
            if (count == 30)
                count = 0;
            str.insert(count,"0");
            std::cout<< str << std::endl;
            std::this_thread::sleep_for(250 * std::chrono::milliseconds(1));
            count++;

            if (q == 0)
                break;
        }
    });

    t1.join();
    t2.join();
    return 0;
}
