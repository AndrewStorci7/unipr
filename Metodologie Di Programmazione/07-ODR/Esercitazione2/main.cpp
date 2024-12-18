/**
 *
 * ESERCIZIO 2:
Crea un header file con una funzione inline che esegue una semplice operazione (ad esempio, somma due numeri).
- Includi l'header file in due file sorgente e chiama la funzione inline in entrambi.
- Compila ed esegui il programma per verificare che non ci siano errori di ODR.

- Modifica la funzione inline in uno dei file sorgente e ricompila. Osserva cosa succede e spiega il comportamento.
SPIEGAZIONE:
    Il compilatore da errore: 'redefinition of `int somma(const int&, const int&)`'
    Questo avviene perché appunto stiamo violando la ODR, essendo la funzione `somma` già definita all'interno di `header.h`.
 */

#include <iostream>
#include "file1.cpp"
#include "file2.cpp"

int main() {
    std::cout << File1::prova << std::endl << File2::prova << std::endl;
    return 0;
}