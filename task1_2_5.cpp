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
    lock_guard < mutex > lock(m1);
    l.push_back(a);
    cout << "Added " << a << endl;
}

void ListContains(int a) {
    lock_guard<mutex> lock(m1);
    list<int>::iterator it = std::find(l.begin(), l.end(), a);

    if (it != l.end()) {
        cout << "Value " << a << " is present" << endl;
    } else {
        cout << "Value " << a << " not present" << endl;
    }
}

int main() {
    int a = 5;
    for (int i = 0; i < 10; i++) {
        thread t1(AddToList, a + i);
        t1.detach();
    }
    for (int i = 0; i < 10; i++) {
        thread t2(ListContains, a);
        t2.detach();
    }
    Sleep(2000);
    return 0;
}
