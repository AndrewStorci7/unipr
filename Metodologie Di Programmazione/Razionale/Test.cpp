//
// Created by andrew-drink on 12/10/24.
//
#include "Rational.cpp"

using namespace Numerical;

namespace Test {

    void test_constructors() {
        std::cout << "Testing Constructors...\n";

        // Default constructor
        Rational r1;
        std::cout << "Default constructor (should be 1/1): " << r1 << std::endl;

        // Parameterized constructor
        Rational r2(3, 4);
        std::cout << "Parameterized constructor (3/4): " << r2 << std::endl;

        // Copy constructor
        Rational r3(r2);
        std::cout << "Copy constructor (copy of 3/4): " << r3 << std::endl;

        // Constructor with a single integer (implicit conversion)
        Rational r4(5);
        std::cout << "Single integer constructor (5/1): " << r4 << std::endl;
    }

    void test_arithmetic_operations() {
        std::cout << "\nTesting Arithmetic Operations...\n";

        Rational r1(3, 4);
        Rational r2(1, 2);

        // Addition
        Rational add_result = r1 + r2;
        std::cout << r1 << " + " << r2 << " = " << add_result << std::endl;

        // Subtraction
        Rational sub_result = r1 - r2;
        std::cout << r1 << " - " << r2 << " = " << sub_result << std::endl;

        // Multiplication
        Rational mul_result = r1 * r2;
        std::cout << r1 << " * " << r2 << " = " << mul_result << std::endl;

        // Division
        Rational div_result = r1 / r2;
        std::cout << r1 << " / " << r2 << " = " << div_result << std::endl;

        // Compound Assignment: +=
        r1 += r2;
        std::cout << "After " << r1 << " += " << r2 << ": " << r1 << std::endl;

        // Compound Assignment: -=
        r1 -= r2;
        std::cout << "After " << r1 << " -= " << r2 << ": " << r1 << std::endl;

        // Compound Assignment: *=
        r1 *= r2;
        std::cout << "After " << r1 << " *= " << r2 << ": " << r1 << std::endl;

        // Compound Assignment: /=
        r1 /= r2;
        std::cout << "After " << r1 << " /= " << r2 << ": " << r1 << std::endl;
    }

    void test_input_output() {
        std::cout << "\nTesting Input and Output...\n";

        Rational r;
        std::cout << "Enter a rational number (format: numerator/denominator): ";
        std::cin >> r;
        std::cout << "You entered: " << r << std::endl;
    }

    void test_comparisons() {
        std::cout << "\nTesting Comparison Operations...\n";

        Rational r1(3, 4);
        Rational r2(2, 3);

        std::cout << r1 << " == " << r2 << " is " << (r1 == r2 ? "true" : "false") << std::endl;
        std::cout << r1 << " != " << r2 << " is " << (r1 != r2 ? "true" : "false") << std::endl;
        std::cout << r1 << " < " << r2 << " is " << (r1 < r2 ? "true" : "false") << std::endl;
        std::cout << r1 << " <= " << r2 << " is " << (r1 <= r2 ? "true" : "false") << std::endl;
        std::cout << r1 << " > " << r2 << " is " << (r1 > r2 ? "true" : "false") << std::endl;
        std::cout << r1 << " >= " << r2 << " is " << (r1 >= r2 ? "true" : "false") << std::endl;
    }

} /// namespace Test