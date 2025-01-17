//
// Created by andrew-drink on 10/01/25.
//

#include <iostream>

struct A {
    void foo(double) { std::cout << "Funzione #1" << std::endl; }; // funzione #1
    void bar(double) { std::cout << "Funzione #2" << std::endl; }; // funzione #2
    void bar(double&) const { std::cout << "Funzione #2" << std::endl; }; // funzione #2
    void foo(int) { std::cout << "Funzione #3" << std::endl; }; // funzione #3
    void foo(int&) const { std::cout << "Funzione #4" << std::endl; }; // funzione #4
};

struct B : public A {
    void foo(char) { std::cout << "Funzione #5" << std::endl; }; // funzione #5
    void bar(char) { std::cout << "Funzione #6" << std::endl; }; // funzione #6
};

void test(A a, B b) {
    a.foo('a');
    a.foo(14);
}

void test2(const A& a, const B& b) {

}

int main() {
    A a;
    B b;
    const A ca;
    const B cb;


    return 0;
}
