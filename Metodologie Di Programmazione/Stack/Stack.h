//
// Created by andrew-drink on 15/01/25.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <iostream>
#include <cassert>
#include <vector>

namespace Lesson19 {

    template <typename T>
    class Stack {
    public:
        using value_type = T;
        using size_type = std::size_t;

        Stack() = default;

        ~Stack() = default;

        /*Stack(Stack&& s)
        : data(s.data) {}

        Stack(const Stack& s) {
           data = s.data;
        }*/

        inline bool empty() const {
            return data.empty();
        }

        inline int push(const value_type &d) {
            data.push_back(d);
        }

        inline T pop() {
            assert(!empty());
            T tmp = data.end();
            data.pop_back();
            return tmp;
        }

        void print(std::ostream &os) {
            for (T _d : data) {
                if (_d == data.end())
                    os << _d << std::endl;
                else os << _d << ", ";
            }
        }

    private:
        std::vector<T> data;
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Stack<T>& s);

} // Lesson19

#endif //STACK_STACK_H
