/**
 * ESERCIZIO 1
 *
 *
 */

#include <iostream>
#include "funzioni.h"

int main() {

    int a[] = {1, 2, 3, 4, 5};
    int* b = new int[7];
    int* c = new int[6];
    for (int i = 0; i < 7; ++i)
        *(b + i) = i + 1;

    ArrayVsPuntatori::print(b, 7);
    ArrayVsPuntatori::print(c, 6);
    ArrayVsPuntatori::mod(c, 7);
    ArrayVsPuntatori::print(c, 6);

    int size_a = ArrayVsPuntatori::size(a);
    int size_b = ArrayVsPuntatori::size(b);

    std::cout << "sizeof int (sizeof (a)): " << sizeof a << std::endl;
    std::cout << "sizeof int (sizeof (b)): " << sizeof b << std::endl;

    std::cout << "sizeof int* (sizeof (*a)): " << sizeof *a << std::endl;
    std::cout << "sizeof int* (sizeof (*b)): " << sizeof *b << std::endl;

    std::cout << "Dimensione a (int a[]): " << size_a << " [dato aspettato: " << sizeof a / sizeof *a << "]" << std::endl;
    std::cout << "Dimensione b (int* b): " << size_b << " [dato aspettato: " << sizeof b << "]" << std::endl;
    std::cout << "Dimensione b (int* b): " << size_b << " [dato aspettato: " << sizeof c << "]" << std::endl;

    delete[] b;
    return 0;
}
