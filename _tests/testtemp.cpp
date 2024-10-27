#include <iostream>
#include <string>
#include <cstdlib>

template <typename T, typename U>
class MyClass {
public:
    void print() const {
        std::cout << "Generic template with two types" << std::endl;
    }
};

// Partial specialization where the second type is `int`
template <typename T>
class MyClass<T, int> {
public:
    void print() const {
        std::cout << "Specialized template where second type is int" << std::endl;
    }
};

// Partial specialization where both types are the same
// template <typename T>
// class MyClass<T, T> {
// public:
//     void print() const {
//         std::cout << "Specialized template where both types are the same" << std::endl;
//     }
// };

int main() {
    MyClass<double, std::string> generic;      // Uses generic template
    MyClass<double, int> secondIsInt;          // Uses specialization for second type int
    // MyClass<int, int> bothSame;                // Uses specialization for both types the same

    generic.print();           // Outputs: Generic template with two types
    secondIsInt.print();       // Outputs: Specialized template where second type is int
    // bothSame.print();          // Outputs: Specialized template where both types are the same

    return 0;
}
