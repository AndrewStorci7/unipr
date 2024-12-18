//
// Created by andrew-drink on 04/12/24.
//

// #pragma once

#include <iostream>

namespace Numerical {

    using ostream = std::ostream;
    using istream = std::istream;

    template <typename T>
    class Rational {
    private:
        T _num;
        T _den;

        void checkDen(T d);

    public:
        Rational() : _num(0), _den(1) {}

        Rational(T n, T d) : _num(n), _den(d) {
            checkDen(d);
            simplify();
        }

        Rational(T n) : _num(n), _den(1) {}

        Rational(const Rational& o);

        Rational(Rational&& o) noexcept;

        void print(ostream& os);

        void scan(istream& is) const;

        inline T getNum();

        inline T getDen();

        inline void setNum(T n);

        inline void setDen(T d);

        inline bool operator==(const Rational& r);

        inline bool operator<(const Rational& r);

        void simplify();
    };

    /**
     * Overload of the operator <<
     *
     * @tparam T    numerical type
     * @param os    ouput stream
     * @param r     Rational
     * @return      output stream
     */
    template <typename T>
    ostream& operator<<(ostream& os, Rational<T>& r) {
        r.print(os);
        return os;
    }

    /**
     * Overload of the operator <<
     *
     * @tparam T    numerical type
     * @param os    ouput stream
     * @param r     const Rational
     * @return      output stream
     */
    template <typename T>
    ostream& operator<<(ostream& os, const Rational<T>& r) {
        r.print(os);
        return os;
    }

    /**
     * Overload of the operator >>
     *
     * @tparam T    numerical type
     * @param is    input stream
     * @param r     Rational
     * @return      input stream
     */
    template <typename T>
    istream& operator>>(istream& is, Rational<T>& r) {
        r.scan(is);
        return is;
    }

    /**
     * Check if two rational are different
     *
     * @tparam T    numerical type
     * @param r     Rational rvalue
     * @param l     Rational lvalue
     * @return bool
     */
    template <typename T>
    inline bool operator!=(const Rational<T>& r, const Rational<T>& l) {
        return not r == l;
    }

    /**
     * Check if the target rational is lower or equal then the rational passed as param
     *
     * @tparam T    numerical type
     * @param r     Rational rvalue
     * @param l     Rational lvalue
     * @return bool
     */
    template <typename T>
    inline bool operator<=(const Rational<T>& r, const Rational<T>& l) {
        return (r == l) or (r < l);
    }

    /**
     * Check if the target rational is bigger or equal to the rational passed as param
     *
     * @tparam T    numerical type
     * @param r     Rational rvalue
     * @param l     Rational lvalue
     * @return bool
     */
    template <typename T>
    inline bool operator>=(const Rational<T>& r, const Rational<T>& l) {
        return (r == l) or (r > l);
    }

    /**
     * Check if the target rational is bigger to the rational passed as param
     *
     * @tparam T    numerical type
     * @param r     Rational rvalue
     * @param l     Rational lvalue
     * @return bool
     */
    template <typename T>
    inline bool operator>(const Rational<T>& r, const Rational<T>& l) {
        return not (r < l);
    }

    template <typename T>
    Rational<T> operator-(const Rational<T>& r, const Rational<T>& l) {
        // static_assert(r.getDen() != 0 && l.getDen() != 0);

        Rational<T> ret;

        T tmp_den = r.getDen() * l.getDen();
        T tmp_r_num = (tmp_den / r.getDen()) * r.getNum();
        T tmp_l_num = (tmp_den / l.getDen()) * l.getNum();

        ret.setDen(tmp_den);
        ret.setNum(tmp_r_num - tmp_l_num);

        return ret;
    }

    /**
     * Calculate the sum between two rational numbers
     *
     * @tparam T    numerical type
     * @param r     Rational rvalue
     * @param l     Rational lvalue
     * @return Rational<T>
     */
    template <typename T>
    Rational<T> operator+(const Rational<T>& r, const Rational<T>& l) {
        // static_assert(r.getDen() != 0 && l.getDen() != 0);

        Rational<T> ret;

        T tmp_den = r.getDen() * l.getDen();
        T tmp_r_num = (tmp_den / r.getDen()) * r.getNum();
        T tmp_l_num = (tmp_den / l.getDen()) * l.getNum();

        ret.setDen(tmp_den);
        ret.setNum(tmp_r_num + tmp_l_num);

        return ret;
    }

    template <typename T>
    Rational<T> operator+(Rational<T>& r, Rational<T>& l) {
        // static_assert(r.getDen() != 0 && l.getDen() != 0);

        Rational<T> ret;

        T tmp_den = r.getDen() * l.getDen();
        T tmp_r_num = (tmp_den / r.getDen()) * r.getNum();
        T tmp_l_num = (tmp_den / l.getDen()) * l.getNum();

        ret.setDen(tmp_den);
        ret.setNum(tmp_r_num + tmp_l_num);

        return ret;
    }

    template <typename Trvalue, typename Tlvalue>
    Rational<Trvalue> operator+(Rational<Trvalue>& r, Rational<Tlvalue>& l) {
        // static_assert(r.getDen() != 0 && l.getDen() != 0);

        Trvalue tmp_den = r.getDen() * l.getDen();
        Trvalue tmp_r_num = (tmp_den / r.getDen()) * r.getNum();
        Trvalue tmp_l_num = (tmp_den / l.getDen()) * l.getNum();

        Rational<Trvalue> ret(tmp_r_num + tmp_l_num, tmp_den);

        return ret;
    }

    /**
     * Calculate the substraction between two rational numbers
     *
     * @tparam T    numerical type
     * @param r     Rational rvalue
     * @param l     Rational lvalue
     * @return Rational<T>
     */
    template <typename T>
    Rational<T> operator-(Rational<T>& r, Rational<T>& l) {
        // static_assert(r.getDen() != 0 && l.getDen() != 0);

        Rational<T> ret;

        T tmp_den = r.getDen() * l.getDen();
        T tmp_r_num = (tmp_den / r.getDen()) * r.getNum();
        T tmp_l_num = (tmp_den / l.getDen()) * l.getNum();

        ret.setDen(tmp_den);
        ret.setNum(tmp_r_num - tmp_l_num);

        return ret;
    }

    /**
     * Calculate the substraction between two rational numbers
     *
     * @tparam Trvalue  numerical type rvalue
     * @tparam Tlvalue  numerical type lvalue
     * @param r         Rational rvalue
     * @param l         Rational lvalue
     * @return Rational<Trvalue>
     */
    template <typename Trvalue, typename Tlvalue>
    Rational<Trvalue> operator-(Rational<Trvalue>& r, Rational<Tlvalue>& l) {
        // static_assert(r.getDen() != 0 && l.getDen() != 0);

        Trvalue tmp_den = r.getDen() * l.getDen();
        Trvalue tmp_r_num = (tmp_den / r.getDen()) * r.getNum();
        Trvalue tmp_l_num = (tmp_den / l.getDen()) * l.getNum();

        Rational<Trvalue> ret(tmp_r_num - tmp_l_num, tmp_den);

        return ret;
    }
}