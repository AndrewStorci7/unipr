//
// Created by andrew on 01/11/24.
//

#include "customer.h"

namespace Business {

    Customer::Customer() {
        _name = "";
        _surname = "";
        _cf = "";
    }

    Customer::Customer(string&& n, string&& s, string&& cf)
        : _name(n), _surname(s), _cf(cf){
        if (n.empty() or s.empty() or cf.empty()) {
            throw std::invalid_argument("Params cannot be empty");
        }
    }

    Customer::Customer(Customer &&c) noexcept
        : _name(c._name), _surname(c._surname), _cf(c._cf){
        /// TODO
    }

    Customer::Customer(const Customer &c) {
        _name = c._name;
        _surname = c._surname;
        _cf = c._cf;
    }

    void Customer::print(std::ostream &os) {
        os << "Customer: " << _name << " " << _surname << ", " << _cf << std::endl;
    }

    /// TODO
    /*
    void Customer::read(std::istream &is) const {

        std::cout << "Name: ";
        is >>
    }
    */

    inline bool Customer::operator==(const Customer &c) const {
        return (_name == c._name and _surname == c._surname and _cf == c._cf);
    }


} // Business