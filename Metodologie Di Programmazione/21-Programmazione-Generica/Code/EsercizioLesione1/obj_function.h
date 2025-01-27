#ifndef OBJ_FUNCTION_ESERCIZIO_LEZIONE_H
#define OBJ_FUNCTION_ESERCIZIO_LEZIONE_H

#include <iostream>
#include <vector>
#include <algorithm>

namespace ObjFunction {

  struct MaggioreDiN {
    using size_type = std::size_t;

    size_type _N;

    MaggioreDiN(int i) : _N(i) {}

    /* Overload di funzione dell'operatore binario `operator()`
     * (*this) è un oggetto funzione
     */
    inline bool operator()(int i) const {
      return i > _N;
    };
    
  };

  void test(const std::vector<int>& vi);
  
} // namespace ObjFunction

#endif
