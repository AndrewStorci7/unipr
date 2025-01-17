#include <iostream>

#include <string>

namespace N {

    struct C {

        int i;

        std::string& first(); // funzione #1

        const std::string& first() const; // funzione #2

        std::string& last(); // funzione #3

        const std::string& last() const; // funzione #4

    }; // class C

    void bar(double); // funzione #5

    std::string& bar(int); // funzione #6

} // namespace N

void foo(N::C& cm, const N::C& cc) {

    std::string& s1 = cm.first(); // chiamata A
    // Funzioni candidate: #1
    // chiamta la funzione #1 perché viene salvata in una variabile di tipo riferiemnto a string

    const std::string& s2 = cm.last(); // chiamata B
    // Funzioni candidate: #1, #2
    // chiama la funzione #2 perché viene salvata in una variabile di tipo riferimento costante a stringa

    std::string& s3 = cc.first(); // chiamata C


    const std::string& s4 = cc.last(); // chiamata D

    bar(s4.size()); // chiamata E
}

int main() {
    N::C cm;
    N::C cc;
    foo(cm, cc);
    return 0;
}
