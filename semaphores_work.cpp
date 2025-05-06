#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

atomic<int> S(1);

void wait() {
    while (true) {
        int expected = S.load();
        if (expected > 0 && S.compare_exchange_weak(expected, expected - 1)) {
            break;
        }
        this_thread::yield(); // cpu usage ko control karne ke liye 
    }
}

void signal() {
    S++;
}

void critical_section(int id) {
    wait();     // enter kar gye section me 

    cout << "Thread " << id << " is in critical section.\n";
    this_thread::sleep_for(chrono::seconds(1));

    cout << "Thread" << id << " finally critical section se exit kar gye.\n";
    signal(); // bahar nikal gye
}

int main() {
    thread t1(critical_section, 1);
    thread t2(critical_section, 2);

    t1.join();
    t2.join();

    return 0;
}