//
// Created by andrew on 01/11/24.
//

#pragma once

#include <iostream>
#include <vector>
#include "../Business/Customer/customer.h"

namespace Classes {

    using string = std::string;
    using vPerson = std::vector<string>;
    using customer = Business::Customer;

    class Activity {
    private:
        int _id;
        string _name;
        vPerson _person;
        customer c;

    public:

        Activity();

        Activity(int id, string n, string p, customer c);

        Activity(string n, string p, customer c);
    };

} // Classes
