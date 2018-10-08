#include <iostream>
#include <EventManager.hpp>

using namespace std;

int main() {
    EventManager manager;

    manager.subscribe<int>([] (const int& number) {
        cout << "integer: " << number << endl;
    });

    manager.subscribe<int>([](const int& number) {
        cout << "also an integer: " << number << endl;
    });

    manager.subscribe<double>([](const double& number) {
        cout << "double: " << number << endl;
    });

    manager.subscribe<double>([](const double& number) {
        cout << "also a double: " << number << endl;
    });

    manager.emit(2);
    manager.emit(3.);
    manager.emit(5.f);

    system("pause");
    return EXIT_SUCCESS;
}