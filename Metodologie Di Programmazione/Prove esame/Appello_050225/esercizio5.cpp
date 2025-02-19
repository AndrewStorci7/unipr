#include <iostream>

using namespace std;

struct A {
  A() { cout << "A::A()" << endl; }
  virtual void m1() const { cout << "A::m1() const" << endl; }
  void m2() const { cout << "A::m2()" << endl; }
  ~A() { cout << "A::~A()" << endl; }
};

struct B : public A {
  void m1() const { cout << "B::m1()" << endl; }
  void m2() const { cout << "B::m2()" << endl; }
};

struct C : public B {
  C() { cout << "C::C()" << endl; }
  void m1() const { cout << "C::m1()" << endl; }
  void m2() const { cout << "C::m2()" << endl; }
  ~C() { cout << "C::~C()" << endl; }
};

int main() {

  A* a = new B(); // A::A() 
  const B* b = new C(); // C::C() e A::A()

  a->m1(); // B::m1()
  a->m2(); // B::m2()
  b->m1(); // C::m1()
  b->m2(); // C::m2()

  delete a; // A::~A()
  delete b; // A::~A() e C::~C()
}
