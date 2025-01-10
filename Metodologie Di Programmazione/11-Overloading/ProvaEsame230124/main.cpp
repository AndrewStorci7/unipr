#include <iostream>

struct Base {
    void foo(int, double) { std::cout << "Funzione #1" << std::endl; }; // funzione #1
    void foo(double, int) const { std::cout << "Funzione #2" << std::endl; }; // funzione #2
    void bar(double) { std::cout << "Funzione #3" << std::endl; }; // funzione #3
    void print(std::ostream&) const { std::cout << "Funzione #4" << std::endl; }; // funzione #4
};

struct Derived : public Base {
    void foo(double, double) { std::cout << "Funzione #5" << std::endl; }; // funzione #5
    using Base::bar;
    void bar(double) const { std::cout << "Funzione #6" << std::endl; }; // funzione #6
};

int main() {
    Derived der;

    std::cout << "Chiamata funzione (a): ";
    der.foo(1.2, 0); // chiamata (a)
    // Funzioni candidate: #5, #2, #1
    // Funzioni utilizzabili: #5, #1 (la funzione #2 non è utilizzabile perché der non è const)
    // chiama la funzione #5 perché è quella che corrisponde meglio; nel secondo parametro avviene una conversione implicita da int a double

    std::cout << "Chiamata funzione (b): ";
    der.bar(1.2); // chiamata (b)
    // Funzioni candidate:

    std::cout << "Chiamata funzione (c): ";
    der.print(std::cout); // chiamata (c)

    const Base& bas = der;

    std::cout << "Chiamata funzione (d): ";
    bas.foo(1.2, 0); // chiamata (d)

    std::cout << "Chiamata funzione (e): " << std::endl;
    // bas.bar(1.2); // chiamata (e)

    std::cout << "Chiamata funzione (f): ";
    bas.print(std::cout); // chiamata (f)
}