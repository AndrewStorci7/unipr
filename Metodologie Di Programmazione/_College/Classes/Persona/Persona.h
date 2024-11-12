//
// Created by andrew-drink on 12/11/24.
//
#pragma once

#include <iostream>

namespace University {

    using string = std::string;
    using os = std::ostream;
    using is = std::istream;

    class Persona {
    protected:
        string _name;
        string _surname;

    public:
        Persona() = default;

        Persona(string n, string s);

        Persona(string n);

        inline string getName();

        inline string getSurname();

        /// Mi serve crearne una per Persona ??
        void print(os& os);

        /// Mi serve crearne una per Persona ??
        void scan(is& is) const;
    };

} // University
