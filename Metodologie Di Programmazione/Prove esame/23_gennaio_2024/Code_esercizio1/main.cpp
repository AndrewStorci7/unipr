#include <iostream>

struct Base {
    void foo(int, double) { std::cout << "Funzione #1" << std::endl; } // funzione #1
    void foo(double, int) const { std::cout << "Funzione #2" << std::endl; } // funzione #2
    void bar(double) { std::cout << "Funzione #3" << std::endl; } // funzione #3
    void print(std::ostream&) const { std::cout << "Funzione #4" << std::endl; } // funzione #4
};

struct Derived : public Base {
    void foo(double, double) { std::cout << "Funzione #5" << std::endl; } // funzione #5
    using Base::bar;
    void bar(double) const { std::cout << "Funzione #6" << std::endl; } // funzione #6
};

int main() {

    Derived der;
    std::cout << "Chiamata A" << std::endl;
    der.foo(1.2, 0); // chiamata (a)
    std::cout << "Chiamata B" << std::endl;
    der.bar(1.2); // chiamata (b)
    std::cout << "Chiamata C" << std::endl;
    der.print(std::cout); // chiamata (c)

    const Base& bas = der;
    std::cout << "Chiamata D" << std::endl;
    bas.foo(1.2, 0); // chiamata (d)
    std::cout << "Chiamata E" << std::endl;
    std::cout << "undefined reference" << std::endl;
    ///bas.bar(1.2); // chiamata (e)
    std::cout << "Chiamata F" << std::endl;
    bas.print(std::cout); // chiamata (f)
}