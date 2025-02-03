#include "classe_dinamica.hh"

namespace ClassiDinamiche {

    /// Persona

    std::string Persona::getName() const {
        return name;
    }

    std::string Persona::getSurname() const {
        return surname;
    }

    void Persona::setName(const std::string& new_val) {
        this->name = new_val;
    }
    
    void Persona::setSurname(const std::string& new_val) {
        this->surname = new_val;
    }


    /// Studente

    std::string Studente::getCorso() const {
        return corso;
    }

    void Studente::setCorso(const std::string& new_val) {
        this->corso = new_val;
    }

    std::ostream& operator<<(std::ostream& os, const Persona& p) {
        p.print(os);
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Persona* p) {
        p->print(os);
        return os;
    }

}