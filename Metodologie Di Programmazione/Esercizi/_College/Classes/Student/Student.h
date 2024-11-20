//
// Created by andrew-drink on 12/11/24.
//
#pragma once

#include "../Persona/Persona.h"
#include <iostream>
#include <vector>

namespace University {

    using string = std::string;
    using os = std::ostream;
    using is = std::istream;
    using vector = std::vector<string>;

    class Student : Persona {
    private:
        int _matricola;
        vector exams;

    public:
        Student() = default;

        /**
         * Default constructor with params
         * @param n => name
         * @param s => surname
         * @param m => matricola
         * @param f => faculty
         */
        Student(string n, string s, int m, int f);

        inline int getMatricola();

        vector getExams() const;

        void print(os&);

        void scan(is& is) const;

        inline bool operator==(const Student& o);
    };

    os& operator<<(os& os, const Student& s);

    is& operator>>(is& is, Student& s);

    inline bool operator!=(const Student& s, const Student& o);

} // University
