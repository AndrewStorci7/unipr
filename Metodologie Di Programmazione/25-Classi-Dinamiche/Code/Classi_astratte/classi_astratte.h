#ifndef CLASSI_ASTRATTE_H
#define CLASSI_ASTRATTE_H

#include <iostream>

namespace ClassiAstratte {

    class Interface {
        public:
            virtual void print(std::ostream& os) const = 0;
            virtual void scan(std::istream& is) = 0;

            virtual std::string getName() = 0;
            virtual const std::string& getName() const = 0;
            
            virtual void setName(const std::string& val) = 0;
            virtual void setName(std::string& val) = 0;

            virtual bool isValid(const std::string& val) const = 0; 
    };

    class Persona : public Interface {
        public:

            Persona() = default;
            Persona(std::string& name) : name(name) {};
            ~Persona() = default;

            void print(std::ostream& os) const override {
                os << "persona: " << name;
            }

            bool isValid(const std::string& val) const override {
                for ( auto i = val.begin(); i != val.end(); ++i ) {
                    if (std::isdigit(*i))
                        return true;
                }
                return false;
            }

            void scan(std::istream& is) override {
                std::string name = "2";

                while (!isValid(name))
                    is >> name;
                this->name = name;
            }

            std::string getName() override {
                return this->name;
            }

            const std::string& getName() const override {
                return this->name;
            }
            
            void setName(const std::string& val) override {
                this->name = val;
            }

            void setName(std::string& val) override {
                this->name = val;
            }

        private:
            std::string name;
    };

    std::ostream& operator<<(std::ostream& os, const Persona& p);
    std::ostream& operator<<(std::ostream& os, const Persona* p);

} // Classi Astratte

#endif