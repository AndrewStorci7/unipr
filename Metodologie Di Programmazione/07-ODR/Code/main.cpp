#include <iostream>
#include "Razionale/Razionale.h"

template <typename T>
using rational = Numerical::Rational<T>;

int main() {

    rational<int> ri;

    std::cout << "Costruttore: " << ri << std::endl;

    rational<int> r_int = (1, 2);
    rational<int> r_int1 = (2, 1);
    rational<int> _r_int = (5);

    std::cout << "Costruttore con = () e 2 param: " << r_int << std::endl;
    std::cout << "Costruttore con = () e 2 param: " << r_int1 << std::endl;
    std::cout << "Costruttore con = () e 1 param: " << _r_int << std::endl;

    rational<int> r_int2 = {4, 1};
    rational<int> r_int2_a = {4, 6};
    rational<int> _r_int2 = {3};

    std::cout << "Costruttore con = {} e 2 param: " << r_int2 << std::endl;
    std::cout << "Costruttore con = {} e 2 param: " << r_int2_a << std::endl;
    std::cout << "Costruttore con = {} e 1 param: " << _r_int2 << std::endl;

    rational<int> r_int3{4, 7};
    rational<int> _r_int3{9};

    std::cout << "Costruttore con {} e 2 param: " << r_int3 << std::endl;
    std::cout << "Costruttore con {} e 1 param: " << _r_int3 << std::endl;

    rational<int> r_int5(44, 5);
    rational<int> _r_int5(67);

    std::cout << "Costruttore con () e 2 param: " << r_int5 << std::endl;
    std::cout << "Costruttore con () e 1 param: " << _r_int5 << std::endl;

    rational<int> r_int6 = {1, 0};
    rational<int> _r_int6 = (4, 0);
    rational<int> _r_int6_a(4, 0);
    rational<int> _r_int6_b{4, 0};
    rational<int> _r_int6_c = r_int5;
    rational<int> _r_int6_d(r_int5);
    rational<int> _r_int6_e{r_int5};
    // rational<int> _r_int6_f;

    std::cout << "Costruttore con = {} e den = 0: " << r_int6 << std::endl;
    std::cout << "Costruttore con = () e den = 0: " << _r_int6 << std::endl;
    std::cout << "Costruttore con () e den = 0: " << _r_int6_a << std::endl;
    std::cout << "Costruttore con {} e den = 0: " << _r_int6_b << std::endl;
    std::cout << "Costruttore di copia con operatore = : " << _r_int6_c << std::endl;
    std::cout << "Costruttore di copia con (): " << _r_int6_d << std::endl;
    std::cout << "Costruttore di copia con {}: " << _r_int6_e << std::endl;
    // std::cout << "Costruttore di copia con {} e den = 0: " << _r_int6_f << std::endl;

    rational<double> rd;
    rational<double> r_double1 = {23.09, 34.98};
    rational<double> r_double2 = {23.09, 0};

    std::cout << "(double) Costruttore: " << rd << std::endl;
    std::cout << "(double) Costruttore con = {}: " << r_double1 << std::endl;
    std::cout << "(double) Costruttore con = {} e den = 0: " << r_double2 << std::endl;


    //// Operazioni aritemtiche
    /// Somma

    rational<int> ri_plus(3, 5);
    rational<int> ri_plus2(5, 9);
    auto ri_ret = ri_plus + ri_plus2;

    std::cout << "(int) " << ri_plus << " + " << ri_plus2 << " = " << ri_ret << std::endl;

    { // Somma tra due razionali di tipo diverso
        rational<double> rd_plus(7.34, 5.342);
        rational<int> ri_plus3(10, 22);
        auto rdi_ret_a = ri_plus3 + rd_plus;
        auto rdi_ret_b = rd_plus + ri_plus3;

        std::cout << "(int) " << ri_plus3 << " + " << rd_plus << " = " << rdi_ret_a << std::endl;
        std::cout << "(double) " << rd_plus << " + " << ri_plus3 << " = " << rdi_ret_b << std::endl;
    }

    /// Sottrazione

    { // sottrazione tra due razionale di tipo diverso
        rational<double> rd_plus(7.34, 5.342);
        rational<int> ri_plus3(10, 22);
        auto rdi_ret_a = ri_plus3 - rd_plus;
        auto rdi_ret_b = rd_plus - ri_plus3;

        std::cout << "(int) " << ri_plus3 << " + " << rd_plus << " = " << rdi_ret_a << std::endl;
        std::cout << "(double) " << rd_plus << " + " << ri_plus3 << " = " << rdi_ret_b << std::endl;
    }

    //// Semplifica

    rational<int> ri_simplified(2, 4);
    rational<int> ri_simplified2(3, 12);
    rational<int> ri_simplified3(19, 13);
    rational<int> ri_simplified4(6, 3);

    std::cout << "Razionale semplificato (f.o 2/4): " << ri_simplified << std::endl;
    std::cout << "Razionale semplificato (f.o 3/12): " << ri_simplified2 << std::endl;
    std::cout << "Razionale semplificato (f.o 19/13): " << ri_simplified3 << std::endl;
    std::cout << "Razionale semplificato (f.o 6/3): " << ri_simplified4 << std::endl;

    return 0;
}
