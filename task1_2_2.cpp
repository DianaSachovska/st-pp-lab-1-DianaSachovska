#include <iostream>
#include <thread>
#include <mutex>
#include <Windows.h>
#include <iterator>
#include <list>
#include <algorithm>

using namespace std;

void Thread1() {
    cout << "1\n";
}

void Thread2() {
    cout << "2\n";
}
int main() {

    thread t1(Thread1);
    thread t2(Thread2);
  
    t1.detach();
    t2.detach();

    return 0;
}
