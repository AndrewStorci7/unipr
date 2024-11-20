//
// Created by andrew-drink on 13/11/24.
//
#pragma once

#include <iostream>
#include <vector>

namespace Memory {

    template<typename T>
    class Stack {
    public:
        // Alias for my parametric type
        using value_type = T;
        using vec = std::vector<value_type>;

        using size_type = std::size_t;

        Stack();

        Stack(size_type st);

        Stack(value_type&& o);

        Stack(const value_type& o);

        ~Stack();

        void print(std::ostream& os, const value_type& o);

        void scan(std::istream& is, value_type& o) const;

        value_type& top() const;

    private:
        vec _data;
        size_type _capacity;

    };

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Stack<T> &o);

} // Memory
