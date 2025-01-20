#include <iostream>
#include "sequenze.hh"
#include <vector>

int main() {

  std::vector<int> vi = {5, 10, 15, 19, 7, 8};
  std::vector<double> vd = {2.6, 4.7, 1.0, 4.5, 5.5, 7.1};
  std::vector<std::string> vs = {"prova", "ciao", "armando", "salvo", "marghe", "mara"};
  
  // auto ret = Sequenze::find_something(vi.begin(), vi.end(), Sequenze::IsEqualTo(3));
  auto res = Sequenze::find_if_greater_then(vi.begin(), vi.end(), Sequenze::IsGreaterOfN(4));
  
  std::cout << ((res) ? "L'array ha valori più grandi di 4" : "L'array NON ha valori più grandi di 4") << std::endl;

  auto res2 = Sequenze::find_if_equals_to(vs.begin(), vs.end(), Sequenze::IsEqualTo<std::string>("marghe"));

  std::cout << ((res2) ? "L'array ha un elemento uguale alla parola 'marghe'" : "L'array ha un elemento uguale alla parola 'marghe'") << std::endl;

  return 0;
}
