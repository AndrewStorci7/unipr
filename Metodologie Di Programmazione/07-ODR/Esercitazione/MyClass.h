//
// Created by andrew-drink on 18/12/24.
//

#pragma once

#include <iostream>

namespace Classe {

    using ostream = std::ostream;
    using istream = std::istream;

    class MyClass {
    private:
        int _n;
        int _d;
    public:
        MyClass() : _n(0), _d(0) {}
        MyClass(int n, int d) : _n(n), _d(d) {}
        MyClass(int n) : _n(n), _d(0) {}
        MyClass(MyClass&& obj) : _n(obj._n), _d(obj._d) {}
        MyClass(const MyClass& obj) {
            _n = obj._n;
            _d = obj._d;
        }

        inline int getN() const { return this->_n; }
        inline int getD() const { return this->_d; }

        inline void setN(int n) { this->_n = n; }
        inline void setD(int d) { this->_d = d; }
    };

    ostream& operator<< (ostream& os, const MyClass& obj) {
        os << obj.getN() << ", " << obj.getD() << std::endl;
        return os;
    }

    istream& operator>> (istream& is, MyClass& obj) {
        int n = 0, d = 0;
        is >> n;
        is >> d;
        obj.setN(n);
        obj.setD(d);
        return is;
    }
} // Classe

