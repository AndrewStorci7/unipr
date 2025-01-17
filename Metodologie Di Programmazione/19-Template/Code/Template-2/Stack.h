//
// Created by andrew-drink on 17/01/25.
//

#ifndef TEMPLATE_2_STACK_H
#define TEMPLATE_2_STACK_H

#include <iostream>

namespace Template2 {

    template <typename T>
    class Stack {
    public:

        using value_t = T;
        using size = std::size_t;

        Stack() = default;
        Stack(Stack&& s) : _data(s._data), _next(s._next) {}
        Stack(const Stack& s);
        ~Stack() = default;

        inline void setData(const value_t& data);

        inline void setNext(const Stack& next);

        void push(value_t data);

        value_t pop() const;

        void print(std::ostream& os);

    private:
        value_t _data;
        Stack* _next;
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Stack<T>& s);



} // Template2

#endif //TEMPLATE_2_STACK_H
