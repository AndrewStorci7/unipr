//
// Created by andrew-drink on 11/10/24.
//
#include "Rational.hh"

#include <stdexcept>
#include <cassert>
#include <numeric>

namespace Numerical {

///////////////////////////////////////////////////////////////////////////////////////////
/// DenominatorEqualToZero
///////////////////////////////////////////////////////////////////////////////////////////

// Default constructor
    DenominatorEqualToZero::DenominatorEqualToZero() {
        this->code_ = 1;
        this->msg_ = "Invalid denominator: cannot be zero";
    }

// Constructor
    DenominatorEqualToZero::DenominatorEqualToZero(const Message &m, const Error &c)
            : code_(c), msg_(m) {
        this->code_ = c;
        this->msg_ = m;
    }

// Se the error message and the code
    std::string DenominatorEqualToZero::see() {
        Message ret = this->msg_ + " with error code: " + std::to_string(this->code_);
        return ret;
    }

// See only the message
    std::string DenominatorEqualToZero::see_msg() {
        Message ret = this->msg_;
        return ret;
    }

///////////////////////////////////////////////////////////////////////////////////////////
/// Rational
///////////////////////////////////////////////////////////////////////////////////////////

// Check if denominator != 0
    void Rational::check_den(const Intero &d) const {
        if (d == 0)
            throw DenominatorEqualToZero();
    }

    bool Rational::operator==(const Rational &r) const {
        assert(r.den_ != 0 && this->den_ != 0);
        return (this->den_ == r.den_ && this->num_ == r.num_);
    }

// Default constructor
    Rational::Rational() {
        this->num_ = 1;
        this->den_ = 1;
    }

// Copy constructor
    // Rational::Rational(const Rational &r)
    // : num_(r.num_), den_(r.den_) {}

// Constructor
    Rational::Rational(const Intero &n, const Intero &d)
            : num_(n), den_(d) {
        // Check if the denominator is zero
        try {
            check_den(d);
            this->num_ = n;
            this->den_ = d;
        } catch (DenominatorEqualToZero &e) {
            std::cout << "Error thrown inside function:constructor() from function:check_den() Rational.cpp:79 \n"
                      << e.see() << std::endl;
        }
    }

// Constructor with 1 param
    Rational::Rational(const Intero& n)
    : num_(n) {
        this->num_ = n;
        this->den_ = 1;
    }

    /* noexcept serve al compilatore per dirgli che in questo
    * metodo non tiriamo nessuna eccezione,
    * e serve per ottimizzare */
    Rational::Rational(Rational&& r) noexcept
    : num_(r.num_), den_(r.den_) {
        r.num_ = 1;
        r.den_ = 1;
    }

    Rational Rational::operator+(const Rational &r) const {
        Rational ret;
        ret.den_ = std::lcm(this->den_, r.den_);
        Intero t_n1 = (ret.den_ / this->den_) * this->num_; // tmp numerator one
        Intero t_n2 = (ret.den_ / r.den_) * r.num_; // tmp numerator two
        Intero num = t_n1 + t_n2;
        ret.num_ = num;
        ret.simplify();
        return ret;
    }

    Rational Rational::operator-(const Rational &r) const {
        Rational ret;
        ret.den_ = std::lcm(this->den_, r.den_);
        Intero t_n1 = (ret.den_ / this->den_) * this->num_; // tmp numerator one
        Intero t_n2 = (ret.den_ / r.den_) * r.num_; // tmp numerator two
        Intero num = t_n1 - t_n2;
        ret.num_ = num;
        ret.simplify();
        return ret;
    }

    Rational Rational::operator*(const Rational &r) const {
        Rational ret;
        Intero num = this->num_ * r.num_;
        Intero den = this->den_ * r.den_;
        ret.num_ = num;
        ret.den_ = den;
        ret.simplify();
        return ret;
    }

    Rational Rational::operator/(const Rational &r) const {
        assert(r.den_ != 0);
        Rational ret;
        Intero num = this->num_ * r.den_;
        Intero den = this->den_ * r.num_;
        ret.num_ = num;
        ret.den_ = den;
        ret.simplify();
        return ret;
    }

    bool Rational::operator<(const Rational &r) const {
        return ((this->num_ / this->den_) < (r.num_ > r.den_));
    }

// Print the rational number
    void Rational::print_to(std::ostream &os) const {
        os << this->num_ << "/" << this->den_;
    }

// Handler for cin overload
    void Rational::read_from(std::istream &is) {
        Intero n = 0, d = 0;
        char b = '/';
        is >> n >> b >> d;
        try {
            check_den(d);
            this->num_ = n;
            this->den_ = d;
        } catch (DenominatorEqualToZero &e) {
            std::cout << "Error thrown inside function:read_from() from function:check_den() Rational.cpp:139 \n"
                      << e.see() << std::endl;
        }
    }

    void Rational::simplify() {
        Intero gcd = static_cast<int>(std::gcd(this->num_, this->den_));
        assert(gcd > 0);
        this->num_ /= gcd;
        this->den_ /= gcd;
    }

    std::ostream &operator<<(std::ostream &os, const Rational &r) {
        r.print_to(os);
        return os;
    }

    std::istream &operator>>(std::istream &is, Rational &r) {
        r.read_from(is);
        return is;
    }

    inline bool operator!=(const Rational &r, const Rational &l) {
        return not(r == l);
    }

    inline bool operator<=(const Rational &r, const Rational &l) {
        return ((r == l) || (r < l));
    }

    inline bool operator>=(const Rational &r, const Rational &l) {
        return ((r == l) || not(r < l));
    }

    inline bool operator>(const Rational &r, const Rational &l) {
        return not(r < l);
    }

    Rational Rational::operator+=(const Rational &l) {
        return *this + l;
    }

    Rational Rational::operator-=(const Rational &l) {
        return *this - l;
    }

    Rational Rational::operator/=(const Rational &l) {
        return *this / l;
    }

    Rational Rational::operator*=(const Rational &l) {
        return *this * l;
    }

    Rational Rational::operator++() {
        Rational add_;
        return *this + add_;
    }

    Rational Rational::operator--() {
        Rational rem_;
        return *this - rem_;
    }

} /// namespace Numerical