#include "obj_function.h"

namespace ObjFunction {

  /* Funzione per testare sia la corretta implementazione di `MaggioreDiN` (oggetto funzione)
   * che per testare il funzionamento di `all_of()`
   */
  void test(const std::vector<int>& vi) {
    if (std::all_of(vi.begin(), vi.end(), MaggioreDiN(100)))
      std::cout << "Tutti grandi" << std::endl;
    else std::cout << "Non sono tutti grandi" << std::endl;
  }
  
} // namespace ObjFunction
