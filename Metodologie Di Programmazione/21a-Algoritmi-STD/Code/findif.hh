#ifndef FIND_IF_H_PROVA_SEQUENZE
#define FIND_IF_H_PROVA_SEQUENZE

#include <iostream>
#include <cstring>

namespace Findif {

  // Predicato Unario
  template <typename T>
  struct IsEqualTo {

    using value_type = T;
    using ref = value_type&;
    using cref = const ref;

    value_type _val;

    IsEqualTo(value_type val) : _val(val) {}

    bool operator()(cref val) const {
      return val == _val;
    }
  };

  // Predicato Unario specializzato per const char*
  template <>
  struct IsEqualTo<const char*> {

    const char* _val;

    IsEqualTo(const char* val) : _val(val) {}

    bool operator()(const char* cc) const {
      return strcmp(_val, _val) == 0;
    }
  };

  // Predicato Binario
  template <typename T>
  struct IsBetween {

    using value_type = T;
    using ref = value_type&;
    using cref = const ref;

    value_type _val1;
    value_type _val2;

    IsBetween(value_type v1, value_type v2) : _val1(v1), _val2(v2) {}

    bool operator()(cref val) const {
      return (val >= _val1 and val <= _val2);
    }
  };

  // Predicato Binario specializzato per const char*
  template <>
  struct IsBetween<const char*> {

    const char* _val1;
    const char* _val2;

    IsBetween(const char* v1, const char* v2) : _val1(v1), _val2(v2) {}

    bool operator()(const char* cc) const {
      return (strcmp(cc, _val1) >= 0 and strcmp(cc, _val2) <= 0);
    }
  };

  /* Implementazione di find_if personalizzato per la ricerca
   * di elementi all'interno di una sequenza siano uguali ad un certo valore (il valore viene dato dal predicato unario)
   */ 
  template <typename Iter, typename BinaryPred>
  void find_if_between(Iter first, Iter last, BinaryPred bp) {
    for ( ; first != last; ++first) {
      if (bp(*first))
	std::cout << *first << " è compreso tra " << bp._val1 << " e " << bp._val2 << std::endl;
      else std::cout << *first << " NON è compreso tra " << bp._val1 << " e " << bp._val2 << std::endl;
    }
  }

  /* Implementazione di find_if personalizzato per la ricerca
   * di elementi all'interno di una sequenza comprei in un determinato range (il range viene determinato dal predicato binario) 
   */ 
  template <typename Iter, typename UnaryPred>
  void find_if_equal(Iter first, Iter last, UnaryPred up) {
    for ( ; first != last; ++first) {
      if (up(*first))
	std::cout << *first << " è uguale " << up._val << std::endl;
      else std::cout << *first << " NON è uguale " << up._val << std::endl;
    }
  }
}

#endif
