#include <iostream>
// #include <random>
#include "Stack.h"

template <typename T>
using stack = Template2::Stack<T>;

int main() {

    stack<int> s_int;
    stack<int> s_int2{};
    stack<int> s_int3();
    stack<int> s_int4 = {};
    // stack<int> s_int5 = ();
    // stack<int> s_int6 = s_int;

    stack<double> s_double;
    stack<double> s_double2{};
    stack<double> s_double3();
    stack<double> s_double4 = {};
    // stack<double> s_double5 = ();
    // stack<double> s_double6 = s_double;

    for (int i = 0; i < 10; ++i)
        s_int.push(rand() % 100);

}
