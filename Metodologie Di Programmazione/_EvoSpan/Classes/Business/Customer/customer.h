//
// Created by andrew on 01/11/24.
//

#pragma once

#include <iostream>
#include <string>

namespace Business {

    using string = std::string;

    class Customer {
    private:
        string _name;
        string _surname;
        string _cf;

    public:

        Customer();

        Customer(string&& n, string&& s, string&& cf);

        Customer(string n, string s, string cf);

        Customer(Customer&& c) noexcept;

        Customer(const Customer& c);

        void print(std::ostream& os);

        void read(std::istream& is) const;

        inline string& getCF() const;

        inline string getCF();

        inline bool operator==(const Customer& c) const;
    };

    std::ostream& operator<<(std::ostream& os, const Customer& c);

    std::istream& operator>>(std::istream& is, Customer& c);

    inline bool operator!=(const Customer& c1, const Customer& c2);

} // Business
