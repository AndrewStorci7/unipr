#include <iostream>
// #include <string>

struct S {
    std::string s;
    double d;

    S() = default;
    S(double& d, std::string& s) : d(d), s(s) {};
};