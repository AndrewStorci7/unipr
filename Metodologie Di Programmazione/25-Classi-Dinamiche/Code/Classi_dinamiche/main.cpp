#include <iostream>
#include "classe_dinamica.hh"

// Classe statica
class Statica { ~Statica() = default; };

// Classe dinamica
class Dinamica { virtual ~Dinamica() = default; };

int main() {

    using ClassiDinamiche::Persona;
    using ClassiDinamiche::Studente;

    std::cout << "Statica " << sizeof(Statica) << std::endl;
    std::cout << "Dinamica " << sizeof(Dinamica) << std::endl;

    Persona* p = new Studente("Andrea", "Storci", "Informatica");
    Persona* p2 = new Persona("Andrea", "Storci");

    // Errore: non si può fare
    // Studente* s = new Persona("prova", "prova");

    std::cout << *p << std::endl;
    std::cout << *p2 << std::endl;

    return 0;
}