/**
 *
 * ESERCIZIO 3:

Crea due file sorgente.
- In un file, definisci una variabile globale.
- Nell'altro file, dichiara la stessa variabile come extern e usala in una funzione.
- Compila ed esegui il programma per verificare che la variabile extern sia correttamente accessibile da entrambi i file.
 */

#include <iostream>
#include "file1.cpp"
#include "file2.cpp"

int main() {
    int prova = somma(10);
    std::cout << globale << std::endl;
    std::cout << prova << std::endl;
    return 0;
}
