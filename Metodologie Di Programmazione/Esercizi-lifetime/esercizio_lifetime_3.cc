#include <iostream>

// ---------------------------

struct X {
  std::string name;

  X(const std::string& n) : name(n) {
    std::cerr << "Constructor X::X(" << name << ")" << std::endl;
  }

  ~X() {
    std::cerr << "Destructor X::~X(" << name << ")" << std::endl;
  }
};

// ---------------------------

struct Y {
  X x1;
  X x2;

  Y() : x1("Y::x1"), x2("Y::x2") {
    std::cerr << "Constructor Y::Y()" << std::endl;
  }

  ~Y() {
    std::cerr << "Destructor Y::~Y()" << std::endl;
  }
};

// ---------------------------

struct Z : public Y {
  X x3;

  Z() : x3("Z::x3") {
    std::cerr << "Constructor Z::Z()" << std::endl;
  }

  ~Z() {
    std::cerr << "Destructor Z::~Z()" << std::endl;
  }
};

// ---------------------------

class W {
  static X staticX;
  Z z;
  X x4;

public:
  W(const std::string& str = "") : z(), x4("W::x4") {
    std::cerr << "Constructor W::W()" << std::endl;
    if (str == "give-error") { // Simula un'eccezione condizionale
      throw std::runtime_error("Error in W constructor");
    }
  }

  ~W() {
    std::cerr << "Destructor W::~W()" << std::endl;
  }
};

// X W::staticX("W::staticX");

// ---------------------------

X createTemporaryX() {
  X temp("TemporaryX");
  return temp; // Restituisce riferimento a un oggetto locale
}

// ---------------------------

X globalX("globalX");

// ---------------------------

int main() {
  std::cout << "Start of main" << std::endl;
  try {
    X localX("localX");
    std::cout << "Creating W" << std::endl;
    W w;

    std::cout << "Calling createTemporaryX" << std::endl;
    X tempRef = createTemporaryX();
    std::cout << "This will likely cause undefined behavior (nope bc I've fixed it): " << tempRef.name << std::endl;
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

X anotherGlobalX("anotherGlobalX");
