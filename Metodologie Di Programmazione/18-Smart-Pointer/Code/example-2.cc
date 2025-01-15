#include <iostream>
#include <memory>

void maybe_print(std::weak_ptr<int> wp) {
	if (auto sp2 = wp.lock())
	  std::cout << *sp2 << std::endl;
	else
	  std::cout << "non più disponibile" << std::endl;
}

void foo() {
  std::weak_ptr<int> wp;
  {
    auto sp = std::make_shared<int>(42);
    wp = sp; // wp non incrementa il reference count della risorsa
    *sp = 55;
    maybe_print(wp); // stampa 55
  } // sp viene distrutto, insieme alla risorsa
	
  maybe_print(wp); // stampa "non più disponibile"
}

int main() {

  foo();

  return 0;
}
