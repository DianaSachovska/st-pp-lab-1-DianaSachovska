#include <iostream>
#include <thread>
#include <mutex>
#include <Windows.h>
#include <iterator>
#include <list>
#include <algorithm>

using namespace std;

list<int> l;

void AddToList(int a) {
    l.push_back(a);
    cout << "Added " << a << endl;
    for (int i = 1; i <= 9; i++) {
        l.push_back(a + i);
        cout << "Added " << a + i << endl;
    }
}
void ListContains(int a) {
    list < int > ::iterator it = std::find(l.begin(), l.end(), a);

    if (it != l.end()) {
        cout << "Value " << a << " is present" << endl;
    } else {
        cout << "Value " << a << " not present" << endl;
    }
}

int main() {
    int a = 5;
    thread t1(AddToList, a);
    thread t2(ListContains, a);
    t1.join();
    t2.join();
    return 0;
}
