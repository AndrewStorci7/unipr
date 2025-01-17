# Esame del 7 Febbraio 2024

## Esercizio sull'overloading

> **(Risoluzione overloading)** Mostrare il processo di risoluzione dell’overloading per le seguenti chiamate di funzione. Per ogni chiamata, indicare: l’insieme delle funzioni candidate; l’insieme delle funzioni utilizzabili; la migliore funzione utilizzabile (se esiste).

```c++
struct D;

struct C {
    C() {}
    C(const D&) {}
};

struct D {
    D() {}
    D(const C&) {}
};

void f(double d) { std::cout << "Funzione #1"; }; // funzione #1

void f(int i, C c = C()) { std::cout << "Funzione #2"; }; // funzione #2

void g(C c, D d) { std::cout << "Funzione #3"; }; // funzione #3

void g(D d, C c = C()) { std::cout << "Funzione #4"; }; // funzione #4

void test(C c, D d) {
    
    f(3.2); // chiamata A
    // Funzioni candidate: #1, #2
    // Funzioni utilizzabili: #1, #2
    // chiama la funzione #1 perché il numero e il tipo di parametri corrispondono 
    
    f(’a’); // chiamata B
    // Funzione candidate: #1, #2
    // Funzioni utilizzabili: #1, #2
    // chiama la funzione #2 perché il numero di parametri coincide e in più avviene una promozione da char a int (viene sempre preferita la conversione da char a int piuttosto che da char a double)
    
    f(’a’, c); // chiamata C
    // Funzioni candidate: #1, #2
    // Funzioni utilizzabili: #2 (la funzione #1 viene scartata perché il numero di parametri non coincide)
    // chiama la funzione #2 ed avviene una promozione da char a int
    
    g(c, d); // chiamata D
    // Funzioni candidate: #3, #4
    // Funzioni utilizzabili: #3 (la funzione #4 viene scartata perché l'ordine del tipo dei parametri non coincide con la chiamata)
    // chiama la funzione #3 perché coincide esattamente 
    
    g(d, c); // chiamata E
    // Funzioni candidate: #3, #4
    // Funzioni utilizzabili: #4 (la funzione #3 viene scartata perché l'ordine dei tipi dei parametri non coincide con la chiamata)
    // chiama la funzione #4 perché conicide esattamente
    
    g(c); // chiamata F
    // Funzioni candidate: #3, #4
    // Funzioni utilizzabili: #4 (la funzione #3 viene scartata perché )
    // chiama la funzione #4 perché l'oggetto D ha un costruttore che prende come parametro un oggetto C, ed avvengono meno conversioni rispetto alla funzione #3 (1 in meno), perciò il compialtore preferisce quella con meno conversioni
}
```