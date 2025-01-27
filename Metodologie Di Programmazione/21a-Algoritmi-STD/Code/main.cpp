#include <iostream>
#include "findif.hh"
#include <vector>

int main() {

  std::vector<const char*> vcc = {"marghe", "lebes", "ciao", "prova", "ciuccmel"};
  std::vector<int> vi = {6, 9, 2, 8, 7, 9, 88, 54, 22, 78};
  
  Findif::find_if_between(vcc.begin(), vcc.end(), Findif::IsBetween<const char*>("aaa", "nnn"));

  std::cout << "FIND IF BETWEEN" << std::endl;
  Findif::find_if_between(vi.begin(), vi.end(), Findif::IsBetween(2, 10));
  std::cout << std::endl << "FIND IF EQUAL" << std::endl;
  Findif::find_if_equal(vi.begin(), vi.end(), Findif::IsEqualTo(9));
}
