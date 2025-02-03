#include "classi_astratte.h"

int main() {

    using ClassiAstratte::Interface;
    using ClassiAstratte::Persona;

    // Errore: non può essere istanziata una classe astratta
    // Interface* i = new Interface();
    Persona* p = new Persona();

    std::cout << *p << std::endl;
}