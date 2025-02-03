#include <iostream>

struct A {
    A() = default;
    ~A() = default;
};

struct B {
    B() = default;
    ~B() = default;
};

struct C : public B {
    C() = default;
    ~C() = default;
};
struct D : public A {
    D() = default;
    ~D() = default;
};
struct E {
    E() = default;
    ~E() = default;
};

int main() {

    A* a;
    D* a2;
    A* aa = static_cast<D*>(a);
    A* aaa = static_cast<A*>(a2);

    // A* d;
    // D* dd = static_cast<A*>(d); // Errore: no up-cast
    // D* dd = dynamic_cast<A*>(d); // Errore: no up-cast
    D* d;
    C c; 
    C& ref_c = c;
    A* prova = dynamic_cast<A*>(d);
    try {
        A& ref_a = dynamic_cast<A&>(*d);
        // A& ref_aa = dynamic_cast<A&>(ref_c);
    } catch (std::bad_cast e) {
        std::cerr << e.what() << std::endl;
    }
}