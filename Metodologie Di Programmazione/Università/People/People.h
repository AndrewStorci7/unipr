//
// Created by andrew-drink on 06/12/24.
//

#ifndef UNIVERSITÀ_PEOPLE_H
#define UNIVERSITÀ_PEOPLE_H

#include <iostream>

namespace People {

    using name = std::string;
    using surname = std::string;
    using ostream = std::ostream;
    using istream = std::istream;

    class People {
    private:
        name _n;
        surname _s;

        inline bool is_unwanted_char(char c);

        void sanitize_str(name& input);

    public:
        People() : _n(""), _s("") {}

        People(name n, surname s) : _n(n), _s(s) {}

        People(name n) : _n(n), _d("") {}

        People(const People& o);

        People(People&& o) noexcept;

        ~People() = default;

        void print(ostream& os);

        void scan(istream& is) const;
    };

    ostream& operator<<(ostream& os, const People& p);

    istream& operator>>(istream& is, People& p);

} // People

#endif //UNIVERSITÀ_PEOPLE_H
