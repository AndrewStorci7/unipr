// Questa notazione indica al compilatore di controllare che questo file 
// sia incluso solo una volta durante la compilazione
// per evitare molteplici inclusioni.
// (Rispetta le regole dell'ODR [One Definition Rule])
#pragma once

#ifndef RATIONAL_HH
#define RATIONAL_HH

#include <iostream>

namespace Numerical {

    struct DenominatorEqualToZero {

        using Error = int;
        using Message = std::string;
    private:
        Error code_;
        Message msg_;

    public:

        DenominatorEqualToZero();

        explicit DenominatorEqualToZero(const Message& m, const Error& c = 1);

        ~DenominatorEqualToZero() = default;

        // Se the error message and the code
        std::string see();

        // See only the message
        std::string see_msg();

    }; /// struct DenominatorEqualToZero

    class Rational {

        using Intero = long;
    private:
        Intero num_;
        Intero den_;

    public:

        void check_den(const Intero &d) const;

        // Default constructor
        Rational();

        // Copy constructor
        Rational(const Rational& r) = default;

        // De-constructor
        ~Rational() = default;

        // Constructor
        explicit Rational(const Intero& n, const Intero&);

        explicit Rational(const Intero& n);

        /* noexcept serve al compilatore per dirgli che in questo
         * metodo non tiriamo nessuna eccezione,
         * e serve per ottimizzare */
        Rational(Rational&& r) noexcept;

        Rational operator+(const Rational& r) const;

        Rational operator-(const Rational& r) const;

        Rational operator*(const Rational& r) const;

        Rational operator/(const Rational& r) const;

        Rational operator++();

        Rational operator--();

        Rational operator+=(const Rational& l);

        Rational operator-=(const Rational& l);

        Rational operator/=(const Rational& l);

        Rational operator*=(const Rational& l);

        bool operator==(const Rational& r) const;

        bool operator<(const Rational& r) const;

        void print_to(std::ostream& os) const;

        void read_from(std::istream& is);

        void simplify();

    }; /// class Rational

    std::ostream& operator<<(std::ostream& os, const Rational* r);

    // std::ostream& operator<<(std::ostream& os, Rational r);

    std::istream& operator>>(std::istream& is, Rational* r);

    // std::istream& operator>>(std::istream& is, Rational r);

    inline bool operator!=(const Rational& r, const Rational* l);

    inline bool operator<=(const Rational& r, const Rational* l);

    inline bool operator>=(const Rational& r, const Rational* l);

    inline bool operator>(const Rational& r, const Rational* l);

} /// namespace Numerical

#endif // RATIONAL_HH