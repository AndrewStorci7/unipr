//
// Created by andrew-drink on 12/11/24.
//

#include "Persona.h"
#include <exception>

namespace University {

    using Error = std::invalid_argument;

    Persona::Persona(string n, string s)
    : _name(n), _surname(s) {
        if (n.empty()) {
            throw Error("Name cannot be null or empty");
        } else if (s.empty()) {
            throw Error("Surname cannot be null or empty");
        }
    }

    Persona::Persona(string n)
    : _name(n) {
        if (n.empty()) {
            throw Error("Name cannot be null or empty");
        }
    }

    inline string Persona::getName() {
        return _name;
    }

    inline string Persona::getSurname() {
        return _surname;
    }

} // University