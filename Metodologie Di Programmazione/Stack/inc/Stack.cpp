//
// Created by andrew-drink on 13/11/24.
//

#include "Stack.h"
// #include <exception>

namespace Memory {

    using ErrorStack = std::invalid_argument;

    // TRR = trailing return type
    /*template<typename T>
    inline auto Stack<T>::top() -> Stack<T>::top() const {

    }*/

    template<typename T>
    Stack<T>::Stack() {
        _capacity = 16;
        _data = {};
    }

    template<typename T>
    Stack<T>::Stack(size_t sz)
    : _capacity(sz) {
        if (sz < 16) {
            throw ErrorStack("Invalid size type, cannot be less than 16");
        }
    }

    template<typename T>
    void Stack<T>::print(std::ostream &os, const Stack::value_type &o) {
        os << "{";
    }

} // Memory