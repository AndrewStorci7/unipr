#include <iostream>
#include "template.h"

int main() {

    using Lesson19::max;

    const char* prova = new char();
    prova = "ciao";
    const char* prova2 = new char();
    prova2 = "dopodomani";
    int a = 10, b = 3;
    double c = 3.5, f = 3.6;
    char h1 = 'f', h2 = '6';

    std::cout << "Prova max(int, int): \n" << "a:\t" << a << "\nb:\t" << b << "\nrisultato:\t" << max(a, b) << std::endl;
    std::cout << "Prova max(const char*, const char*): \n" << "a:\t" << prova << "\nb:\t" << prova2 << "\nrisultato:\t" << max(prova, prova2) << std::endl;
    std::cout << "Prova max(double, double): \n" << "a:\t" << c << "\nb:\t" << f << "\nrisultato:\t" << max(c, f) << std::endl;
    std::cout << "Prova max(char, char): \n" << "a:\t" << h1 << "\nb:\t" << h2 << "\nrisultato:\t" << max(h1, h2) << std::endl;
    std::cout << "Prova max<double>(int, double): \n" << "a:\t" << a << "\nb:\t" << f << "\nrisultato:\t" << max<double>(a, f) << std::endl;
    std::cout << "Prova max<int>(int, double): \n" << "a:\t" << a << "\nb:\t" << f << "\nrisultato:\t" << max<int>(a, f) << std::endl;

    return 0;
}
