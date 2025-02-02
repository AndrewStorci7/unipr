#include <iostream>

struct D;

struct C {
    C() {}
    C(const D&) {}
};

struct D {
    D() {}
    D(const C&) {}
};

void f(double d) { std::cout << "Funzione #1" << std::endl; } // funzione #1

void f(int i, C c = C()) { std::cout << "Funzione #2" << std::endl; } // funzione #2

void g(C c, D d) { std::cout << "Funzione #3" << std::endl; } // funzione #3

void g(D d, C c = C()) { std::cout << "Funzione #4" << std::endl; } // funzione #4

void test(C c, D d) {
    f(3.2); // chiamata A
    f('a'); // chiamata B
    f('a', c); // chiamata C

    g(c, d); // chiamata D
    g(d, c); // chiamata E
    g(c); // chiamata F
}

int main() {

    D d;
    C c;
    test(c, d);

}