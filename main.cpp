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
    //auto result = new int(0);
    // std::thread t1(doWork,2,2,*result);

    int result;

    std::thread t1(doWork,9,1,std::ref(result));

    //t1.detach();//finish second thread if main thread is finished

    //t1.join();//just wait when this thread finished and after go ahead

    // while(true)
    // {
    //     std::this_thread::sleep_for(3 * std::chrono::seconds(1));
    // }
    // std::cout<<std::this_thread::get_id() << " main started"<<std::endl;
    // std::this_thread::sleep_for(3 * std::chrono::seconds(1));
    // std::cout<<std::this_thread::get_id() << " main finished"<<std::endl;

    t1.join();
    std::cout << result << std::endl;

    // delete result;

    return 0;

}
