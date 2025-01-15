//
// Created by andrew-drink on 15/01/25.
//

#include "Stack.h"

namespace Lesson19 {

    /*template <typename T>
    Stack<T>::Stack()
    : _data(0), _prev(nullptr) {}*/

    /*template <typename T>
    Stack<T>::Stack(const T& data, const Stack& prev)
    : _data(data) {
        _prev = prev;
    }*/

    /*template <typename T>
    Stack<T>::Stack(Stack&& s)
    : _data(s._data), _prev(s._prev) {}*/

    /*template <typename T>
    Stack<T>::Stack(const Stack<T> &s) {
        _data = s._data;
        _prev = s._prev;
    }*/

    /*template <typename T>
    const int Stack<T>::push(const T& newData) {
        Stack* newStack = new Stack(newData);
        *this->_prev = newStack;
        delete newStack;
    }*/

    /*template <typename T>
    void Stack<T>::print(std::ostream& os) {
        Stack& loop = *this;
        while (loop._prev != nullptr) {
            os << loop._data << ", ";
        }
        // print last object
        os << loop._data << std::endl;
        delete loop;
    }*/

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Stack<T>& s) {
        s.print(os);
        return os;
    }

} // Lesson19