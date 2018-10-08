# GameEngine-EventSystem
This project serves as a library for an event system and for testing it.

## How to use it
```c++
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

    manager.emit(5);
    manager.emit(5.);
    manager.emit(5.f);

    system("pause");
    return EXIT_SUCCESS;
}
```

output:
```
integer: 5
also an integer: 5
double: 5
also a double: 5
Press any key to continue . . .
```
