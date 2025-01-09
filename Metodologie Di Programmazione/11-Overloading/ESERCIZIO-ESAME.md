# Esercizio sull'overloading preso dall'esame del 9 Gennaio 2024

```c++
#include <string>

namespace N {

    struct C {

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
    // Funzioni candidate: #1, #2
    // chiama la funzione #1 perché viene salvata in una variabile di tipo riferiemnto a string

    const std::string& s2 = cm.last(); // chiamata B
    // Funzioni candidate: #4
    // chiama la funzione #4 perché viene salvata in una variabile di tipo riferimento costante a stringa

    std::string& s3 = cc.first(); // chiamata C
    // Funzioni candidate: #1
    // viene generato un errore per ambiguità, perché cc è un riferimento costante ad un oggetto C

    const std::string& s4 = cc.last(); // chiamata D
    // Funzioni candidate: #

    bar(s4.size()); // chiamata E
    // Genera un errore perche non e presente nessuna dichiarazione dellonscope locale/interno della funzione bar()
}
```