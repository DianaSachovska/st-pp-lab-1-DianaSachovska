#include <iostream>
#include <thread>
#include <mutex>
#include <Windows.h>
#include <iterator>
#include <list>
#include <algorithm>

using namespace std;

list<int> l;
mutex m1;

void AddToList(int a) {
    m1.lock();
    l.push_back(a);
    cout << "Added " << a << endl;
    for (int i = 1; i <= 9; i++) {
        l.push_back(a + i);
        cout << "Added " << a + i << endl;
    }
    m1.unlock();
}
void ListContains(int a) {
    m1.lock();
    for (int i = 0; i < 10; i++) {
        list<int> ::iterator it;
        if (it != l.end()) {
            cout << "Value " << a << " is present" << endl;
        } else {
            cout << "Value " << a << " not present" << endl;
        }
    }
    m1.unlock();
}

int main() {
  
    int a = 5;
  
    thread t1(AddToList, a);
    thread t2(ListContains, a);
  
    t1.join();
    t2.join();
  
    return 0;
}
