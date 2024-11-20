//
// Created by andrew-drink on 12/11/24.
//

#include "Student.h"
#include <exception>

namespace University {

    using Error = std::invalid_argument;

    Student::Student(string n, string s, int m, int f)
    : Persona(n, s), _matricola(m) {

        switch (f) {
            case 0: {   /// Computer Science
                this->exams = {"Fondamenti dell'Informatica", "Fondamenti di Programmazione", "Analisi Matematica 1", "Fisica 1", "Algoritmi e Strutture Dati", "Metodologie di Programmazione"};
                break;
            }
            case 1: {   /// Engeneer COmputer Science
                this->exams = {"Statistica", "Fondamenti di Programmazione", "Analisi Matematica 2", "Composti Chimici", "Chimica", "Sistemi Operativi"};
                break;
            }
            case 2: {   /// Math
                this->exams = {"Statistica", "Fondamenti della Matematica", "Elementi di Probabilità", "Fisica 1", "Analisi Matematica 1", "Analisi Matematica 2"};
                break;
            }
        }
    }

    inline int Student::getMatricola() {
        return _matricola;
    }

    vector Student::getExams() const {
        for (string exam : exams) {
            std::cout << exam << std::endl;
        }
        return exams;
    }

    void print(os& os) {
        os << "Student: " <<   
    }
} // University