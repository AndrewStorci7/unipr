#include <iostream>
#include "Stack.h"

int main() {

    using Lesson19::Stack;

    Stack<int> stack;
    Stack<double> stack1;

    for (int i = 0; i < 10; ++i) {
        stack.push((rand() % 101));
    }

    std::cout << stack;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
