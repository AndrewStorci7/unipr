#ifndef MIN_ELEM_TFUNCTION_H
#define MIN_ELEM_TFUNCTION_H

#include <iostream>
#include <cstring>

namespace Esercizio3 {

    template <typename T>
    struct LowerThan {

        using value_type = T;
        using const_reference = const value_type&;

        LowerThan() = default;

        bool operator()(const_reference val1, const_reference val2) {
            return val1 < val2;
        }

        bool operator()(const char*& val1, const char*& val2) {
            return strcmp(val1, val2) >= 0;
        }

    };

    template <typename Iter, typename BinaryPred>
    Iter min_element(Iter first, Iter last, BinaryPred pred) {

        Iter min = first;

        for ( ; first != last; ++first ) {
            std::cout << *min << " is minor than " << *first << "?" << std::endl;
            if (not pred(*min, *first)) {
                min = first;
            }
        }

        return (min != first) ? min : last; 
    }

    template <typename Iter>
    void print(Iter first, Iter last) {
        for ( ; first != last; ++first ) {
            std::cout << *first << "\t";
        }
        std::cout << std::endl;
    }

} // namespace Esercizio3

#endif