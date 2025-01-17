#include <iostream>
#include <string>

// ---------------------------

struct A {
  std::string name;
  A(const std::string& n) : name(n) {
    std::cerr << "Constructor A::A(" << name << ")" << std::endl;
  }
  ~A() {
    std::cerr << "Destructor A::~A(" << name << ")" << std::endl;
  }
};

// ---------------------------

struct B {
  A a1;
  A a2;

  B() : a1("B::a1"), a2("B::a2") {
    std::cerr << "Constructor B::B()" << std::endl;
  }
  ~B() {
    std::cerr << "Destructor B::~B()" << std::endl;
  }
};

// ---------------------------

struct C : public B {
  A a3;

  C() : a3("C::a3") {
    std::cerr << "Constructor C::C()" << std::endl;
    throw std::runtime_error("Error in C constructor");
  }
  ~C() {
    std::cerr << "Destructor C::~C()" << std::endl;
  }
};

// ---------------------------

struct D {
  A a4;
  B b;
  C c;

  D() : a4("D::a4"), b(), c() {
    std::cerr << "Constructor D::D()" << std::endl;
  }
  ~D() {
    std::cerr << "Destructor D::~D()" << std::endl;
  }
};

// ---------------------------

A globalA("globalA");

// ---------------------------

int main() {
  std::cout << "Start of main" << std::endl;
  try {
    A localA("localA");
    B b;
    std::cout << "Creating object D" << std::endl;
    D d;
  }
  catch (const std::runtime_error& e) {
    std::cerr << "Caught std::runtime_error: " << e.what() << std::endl;
  }
  catch (...) {
    std::cerr << "Caught unknown exception" << std::endl;
  }
  std::cout << "End of main" << std::endl;
  return 0;
}

// ---------------------------

A anotherGlobalA("anotherGlobalA");

// ---------------------------

/// Test
// Sposta `A anotherGlobalA("anotherGlobalA");` sopra `main` per vedere l'ordine dei costruttori e distruttori.
// Commenta `throw std::runtime_error("Error in C constructor");` nel costruttore di `C` e osserva il comportamento.
