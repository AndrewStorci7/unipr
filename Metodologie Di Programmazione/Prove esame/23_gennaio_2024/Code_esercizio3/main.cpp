#include <iostream>
#include "is_equal.hh" 
#include <vector>

int main() {
  {
    std::vector<int> vi = {3, 6, 8, 1, 5, 3, 9};
    std::vector<int> vii = {4, 4, 4, 6, 2, 1, 8, 3, 9, 8, 7, 3, 6, 0, 2, 7};

    auto check = Esercizio3::contains<std::vector<int>::iterator>(vi.begin(), vi.end(), vii.begin(), vii.end());

    std::cout << "Verdetto finale: " << (check ? "Tutti gli elementi della prima sequenza son contenuti nella seconda" : "NON Tutti gli elementi della prima sequenza son contenuti nella seconda") << std::endl;
  }
  
  {
    std::vector<int> vii = {1, 2, 3, 4, 5};
    std::vector<int> vi = {1, 4, 1, 5, 1, 1, 7, 2, 5, 3, 2};

    auto check = Esercizio3::contains<std::vector<int>::iterator>(vi.begin(), vi.end(), vii.begin(), vii.end());

    std::cout << "Verdetto finale: " << (check ? "Tutti gli elementi della prima sequenza son contenuti nella seconda" : "NON Tutti gli elementi della prima sequenza son contenuti nella seconda") << std::endl;
  }
}
