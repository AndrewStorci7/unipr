#ifndef ESERCIZIO_3_IS_EQUAL_HH
#define ESERCIZIO_3_IS_EQUAL_HH

#include <algorithm>

namespace Esercizio3 {

  template <typename T, typename C = T>
  struct IsEqual {
    using value_type = T;
    using value_type2 = C;
    using ref = value_type&;
    using ref2 = value_type2&;
    using cref = const ref;

    value_type val;
    value_type2 val2;

    IsEqual(value_type val) : val(val) {}

    bool operator()(cref v) const {
      return val == v;
    }
  };

  template <typename InputIt1, typename InputIt2 = InputIt1>
  bool contains(
    InputIt1 first1, InputIt1 last1,
    InputIt2 first2, InputIt2 last2
  ) {

    for ( ; first2 != last2; ++first2) {    
      if (std::find_if(first1, last1, IsEqual(*first2)) == last1)
	return false;
    }
    return true;
  }
  
} // Esercizio3

#endif
