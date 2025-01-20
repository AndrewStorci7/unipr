#include "sequenze.hh"

namespace Sequenze {

  /* Find Something function (template)
   *
   * @param {Iter} first Iterator to the first element of a sequence
   * @param {Iter} last Iterator to the last element of a sequence
   * @param {Unarypred} up Unary predicate to use for every iteration
   * 
   * @returns {Iter} ret
   */ 
  template <typename Iter, typename UnaryPred>
  bool find_if_greater_then(Iter first, Iter last, UnaryPred up) {
    for ( ; first != last; ++first ) {
      if (!up(*first))
	return false;
    }
    return true;
  }
  
}
