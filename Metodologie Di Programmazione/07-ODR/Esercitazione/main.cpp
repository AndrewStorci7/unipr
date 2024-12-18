/**
 *
ESERCIZIO

Crea un progetto C++ con due file sorgente (file1.cpp e file2.cpp) e un header file (MyClass.h).
- Definisci una classe MyClass nell'header file, includendo le guardie di inclusione. (FATTO)
- In entrambi i file sorgente, includi l'header file e crea un'istanza della classe MyClass. (FATTO)
- Compila ed esegui il programma per verificare che non ci siano errori di ODR. (FATTO)

 */

#include <iostream>
#include "file1.cpp"
#include "file2.cpp"

int main() {
    std::cout << File1::m1 << File2::m1 << std::endl;
    return 0;
}
