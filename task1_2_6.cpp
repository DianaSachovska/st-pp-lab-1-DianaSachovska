#include <iostream>
#include <thread>
#include <mutex>
#include <Windows.h>
#include <iterator>
#include <list>
#include <algorithm>

using namespace std;

class someData {
  public: 
    string name;
    string surname;
    string address;
    int age;

    void print() {
        cout << "Name: " << name << endl;
        cout << "Surname: " << surname << endl;
        cout << "Address: " << address << endl;
        cout << "Age: " << age << endl;
    }
};

class exchangePerson {
    someData data;
    mutex m;

  public:
    static void JohnDoe(exchangePerson & person) {
        person.data.name = "John";
        person.data.surname = "Doe";
        person.data.address = "Unknown";
        person.data.age = 120;
    }
    static void JacobSmith(exchangePerson & person) {
        person.data.name = "Jacob";
        person.data.surname = "Smith";
        person.data.address = "Known";
        person.data.age = 1;
    }

    static void Swap(exchangePerson & p1, exchangePerson & p2) {
        if ( &p1 == &p2) {
            return;
        }

        lock(p1.m, p2.m);
      
        lock_guard < mutex > lock_a(p1.m, adopt_lock);
        lock_guard < mutex > lock_b(p2.m, adopt_lock);
        cout << "==========================================" << endl;

        cout << "Before:\n";
        p1.data.print();
        p2.data.print();

        cout << "==========================================" << endl;

        swap(p1.data, p2.data);

        cout << "After:\n";
        p1.data.print();
        p2.data.print();
        cout << "==========================================" << endl;
    }
};

int main() {
    exchangePerson John;
    exchangePerson Jacob;

    thread john(exchangePerson::JohnDoe, ref(John));
    john.detach();

    thread jacob(exchangePerson::JacobSmith, ref(Jacob));
    jacob.detach();

    thread swap(exchangePerson::Swap, ref(John), ref(Jacob));
    swap.join();

    return 0;
}
