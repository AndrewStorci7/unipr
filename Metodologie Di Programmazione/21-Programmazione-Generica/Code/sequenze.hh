#ifndef SEQUENZA_H_ESERCITAZIONE_PG
#define SEQUENZA_H_ESERCITAZIONE_PG

#include <vector>
#include <cstring>

namespace Sequenze {

  struct IsGreaterOfN {

    int _N; // Dato con la quale effettuare il confronto
    
    IsGreaterOfN(int i) : _N(i) {}

    inline bool operator()(const int& i) const {
      return i > _N;
    }
    
  };

  template <typename T>
  struct IsEqualTo {
    using value_type = T;
    using ref = value_type&;
    using const_ref = const ref; 

    value_type val;

    IsEqualTo(value_type _val) : val(_val) {}

    inline bool operator()(const_ref val) const {
      return val == this->val;
    }

    inline bool operator()(const char* cc) const {
      return strcmp(cc, val) == 0;
    }
    
  };
  
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
      std::cout << *first << " è più grande di 4" << std::endl;
      if (!up(*first)) {
	std::cout << *first << " NON è più grande di 4" << std::endl;
	return false;
      } else {
	std::cout << *first << " è più grande di 4" << std::endl;
      }
    }
    return true;
  }

  template <typename Iter, typename UnaryPred>
  bool find_if_equals_to(Iter first, Iter last, UnaryPred up) {
    bool ret = false;
    for ( ; first != last; ++first) {
      if (up(*first)) {
	std::cout << *first << " è uguale a 'marghe'" << std::endl;
	ret = true;
      } else {
	std::cout << *first << " NON è uguale a 'marghe'" << std::endl;	
      }
    }
    return ret;
  }
  
} // namespace Sequenze

#endif
