#include <iostream>
#include <thread>
#include <chrono>
#include <functional>


int doWork()
{
    std::cout<<std::this_thread::get_id() << " doWork started"<<std::endl;
    std::this_thread::sleep_for(3 * std::chrono::seconds(1));
    std::cout<<std::this_thread::get_id() << " doWork finished\n"<<std::endl;
    return 0;
}

int main(){
    std::thread t1(doWork);

    //t1.detach();//finish second thread if main thread is finished

    //t1.join();//just wait when this thread finished and after go ahead

    std::cout<<std::this_thread::get_id() << " main started"<<std::endl;
    std::this_thread::sleep_for(3 * std::chrono::seconds(1));
    std::cout<<std::this_thread::get_id() << " main finished"<<std::endl;
    return 0;
}
