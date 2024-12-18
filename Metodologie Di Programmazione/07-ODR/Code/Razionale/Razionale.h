//
// Created by andrew-drink on 04/12/24.
//

#pragma once

#include <numeric>
#include "Razionale.cpp"

namespace Numerical {

    /**
     * Check if the parameter passed to the function is zero.
     * If true it will set by default 1
     *
     * @tparam T    Numerical type
     * @param d     Denominator
     */
    template <typename T>
    void Rational<T>::checkDen(T d) {
        if (d == 0)
            this->_den = 1;
        else this->_den = d;
    }

    /**
     * Copy Constructor
     * 
     * @tparam T    numerical type
     * @param n     numerator
     * @param d     denominator (!= 0)
     */
    template <typename T>
    Rational<T>::Rational(const Rational& o) {
        // static_assert(o._den == 0);
        _num = o._num;
        _den = o._den;
    }

    /**
     * Move Constructor
     * 
     * @tparam T    numerical type
     * @param n     numerator
     * @param d     denominator (!= 0)
     */
    template <typename T>
    Rational<T>::Rational(Rational&& o) noexcept
    : _num(o._num), _den(o._den) {
        // static_assert(o._den != 0);
    }

    /**
     * Print the rational number in the format num/den
     * 
     * @tparam T    numerical type 
     * @param os    output stream
     */
    template <typename T>
    void Rational<T>::print(ostream &os) {
        os << _num;
        if (_den != 1)
            os << "/" << _den;
    }

    /**
     * Scan the ration number in the format num/den
     * - Check if the denominator is equal to zero
     *
     * @tparam T    numerical type
     * @param is    input stream
     */
    template <typename T>
    void Rational<T>::scan(istream& is) const {
        T num, den;
        char del;
        is << num << del << den;
        checkDen(den);
    }

    /**
     * Getter of the _num attribute
     *
     * @tparam T    numerical type
     * @return _num numerator
     */
    template <typename T>
    inline T Rational<T>::getNum() {
        return this->_num;
    }

    /**
     * Getter of the _den attribute
     *
     * @tparam T    numerical type
     * @return _den denominator
     */
    template <typename T>
    inline T Rational<T>::getDen() {
        return this->_den;
    }

    /**
     * Setter of the _num attribute
     *
     * @tparam T    numerical type
     * @param n     numerator
     */
    template <typename T>
    inline void Rational<T>::setNum(T n) {
        _num = n;
    }

    /**
     * Setter of the _den attribute
     *
     * @tparam T    numerical type
     * @param n     numerator
     */
    template <typename T>
    inline void Rational<T>::setDen(T d) {
        checkDen(d);
    }

    /**
     * Check if two rational are equals
     *
     * @tparam T    numerical type
     * @param r     Rational
     */
    template <typename T>
    inline bool Rational<T>::operator==(const Rational<T> &r) {
        return (_num == r._num) and (_den == r._den);
    }

    /**
     * Check if the target rational is lower than the passed as param
     *
     * @tparam T    numerical type
     * @param r     Rational
     */
    template <typename T>
    inline bool Rational<T>::operator<(const Rational<T> &r) {
        return double(_num / _den) < double(r._num / r._den);
    }

    /**
     * Simplify the rational number finding the greatest common divisor
     * It only works with integer
     *
     * @tparam T    numerical type
     */
    template <typename T>
    void Rational<T>::simplify() {
        if constexpr (std::is_same_v<T, int>) {
            T _gcd = std::gcd(this->_num, this->_den);

            this->_num /= _gcd;
            this->_den /= _gcd;
        }
    }

}