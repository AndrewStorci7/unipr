#ifndef CLASSE_DINAMICA_H
#define CLASSE_DINAMICA_H

#include <iostream>

namespace ClassiDinamiche {

    class Persona {
        public:

            Persona() = default;
            Persona(std::string name_, std::string surname_) : name(name_), surname(surname_) {};
            ~Persona() = default;

            virtual void print(std::ostream& os) const {
                os << "Persona { " << name << ", " << surname << " }" << std::endl; 
            }

            std::string getName() const;
            std::string getSurname() const;

            void setName(const std::string& new_val);
            void setSurname(const std::string& new_val);

        private:
            std::string name;
            std::string surname;
    };

    class Studente : public Persona  {
        public:

            Studente() = default;
            Studente(std::string name_, std::string surname_, std::string corso_) 
            : Persona(name_, surname_), corso(corso_) {};
            ~Studente() = default;

            void print(std::ostream& os) const override {
                os << "Studente { " << this->getName() << ", " << this->getSurname() << ", " << corso << " }" << std::endl; 
            }

            std::string getCorso() const;

            void setCorso(const std::string& new_val);

        private:
            std::string corso;
    };

    std::ostream& operator<<(std::ostream& os, const Persona& p);
    std::ostream& operator<<(std::ostream& os, const Persona* p);

} // ClassiDinamiche

#endif