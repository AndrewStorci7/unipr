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
    D* d = static_cast<D*>(a);

    try {    
        D* dd;
        E* e;
        A* aa = dynamic_cast<A*>(dd);
        A* aaa = dynamic_cast<D*>(dd);
        // D* ddd = dynamic_cast<D*>(e);
    } catch (std::bad_cast e) {
        std::cerr << e.what() << std::endl;
    }
}