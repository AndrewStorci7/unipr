//
// Created by andrew-drink on 17/01/25.
//

#include "Stack.h"

namespace Template2 {

    template <typename T>
    Stack<T>::Stack(const Stack<T> &s) {
        _data = s._data;
        _next = s._next;
    }

    template <typename T>
    inline void Stack<T>::setData(const T& data) {
        _data = data;
    }

    template <typename T>
    inline void Stack<T>::setNext(const Stack<T>& next) {
        _next = next;
    }

    template <typename T>
    void Stack<T>::push(T data) {
        // copy of the *this object
        Stack<T> copy = *this;
        Stack<T> ret;
        ret._data = data;

        while (this->_next != nullptr)
            copy = *this->_next;

        copy._next = ret;
        delete copy;
    }

} // Template2