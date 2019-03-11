#include <iostream>
#include <EventManager.hpp>

using namespace std;

int main() {
    EventManager manager;

    unsigned long id1 = manager.subscribe<int>([] (const int& number) {
        cout << "integer: " << number << endl;
    });

    unsigned long id2 = manager.subscribe<int>([](const int& number) {
        cout << "also an integer: " << number << endl;
    });

    unsigned long id3 = manager.subscribe<double>([](const double& number) {
        cout << "double: " << number << endl;
    });

    unsigned long id4 = manager.subscribe<double>([](const double& number) {
        cout << "also a double: " << number << endl;
    });

    unsigned long id5 = manager.subscribe<float>([](const float& number) {
        cout << "float: " << number << endl;
    });

    manager.removeSubscription<float>(id5);

    manager.emit(2);
    manager.emit(3.);
    manager.emit(5.f);

    system("pause");
    return EXIT_SUCCESS;
}