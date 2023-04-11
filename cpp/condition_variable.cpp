#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;
uintmax_t counter = 0;

void consume() {
    auto id = std::hash<std::thread::id>{}(std::this_thread::get_id());

    do {
        // Condition variables only work with unique_lock
        // because you can call unlock() as oposed to the
        // regular lock_guard object.
        std::unique_lock ulock(m);
        cv.wait(ulock);
        // This would never return
        //cv.wait(ulock, [&](){return false;});
        std::cout << "Thread " << id << " with counter " << counter << std::endl;
    } while(counter < 10);

    std::cout << "Thread " << id << " exiting" << std::endl;
}

void produce() {
    do {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard lock(m);
        counter++;
        cv.notify_one();
    } while(counter < 10);

    cv.notify_all();
}

int main() {
    std::vector<std::thread> consumers;

    for(int i = 0; i < 5; i++) {
        std::thread thread(consume);
        consumers.push_back(std::move(thread));
    }

    std::thread producer(produce);

    producer.join();
    for(auto &consumer: consumers) {
        consumer.join();
    }

    std::cout << "Exiting main" << std::endl;

    return 0;
}
