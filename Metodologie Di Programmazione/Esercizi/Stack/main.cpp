#include <iostream>
#include "inc/Stack.h"

template <typename T>
using stack = Memory::Stack<T>;

int main() {

    // Memory::Stack<int> s_int;
    // Memory::Stack<double> s_double;
    stack<int> s_int;
    stack<int> s_int_2 = (34);
    stack<double> s_double = (11.56);

    std::cout << "First Stack: " << s_int;
    std::cout << "Second Stack: " << s_int_2;

    return 0;
}
