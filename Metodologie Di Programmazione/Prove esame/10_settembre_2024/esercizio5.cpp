#include <iostream>
using namespace std;

struct A {
    A() { cout << "Costruttore A" << endl; }
    virtual void foo(int) { cout << "A::foo(int)" << endl; }
    virtual void bar(int) { cout << "A::bar(int)" << endl; }
    virtual void bar(double) { cout << "A::bar(double)" << endl; }
    virtual ~A() { cout << "Distruttore A" << endl; }
};

struct B : public A {
    B() { cout << "Costruttore B" << endl; }
    void foo(int) { cout << "B::foo(int)" << endl; }
    void bar(int) {
        cout << "eccezione B::bar(int)" << endl;
        throw -1;
    }
    ~B() { cout << "Distruttore B" << endl; }
};

int main() {
    try {
        A* a1 = new A;
        A* a2 = new B;
        cout << "=== 1 ===" << endl;
        
        a1->foo(1.234); // avviene conversione standard (implicita)
        a2->foo(1.234); // avviene converisone standard (implicita)
        cout << "=== 2 ===" << endl;
        
        a1->bar(10101); // chiamata effettuata su A
        a2->bar(10101); // chiamata effettuata su B
        a1->bar(1.234); // chiamata effettuata su A
        a2->bar(1.234); // chiamata effettuata su B
        cout << "=== 3 ===" << endl;
        
        delete a2;
        delete a1;
    } catch (...) {}
    return 0;
}