#include <iostream>

struct D;

struct C {
    C() {}
    C(const D&) {}
};

struct D {
    D() {}
    D(const C&) {}
};

void f(double d) { std::cout << "Funzione #1" << std::endl; }; // funzione #1

// void f(int i, C c = C()) { std::cout << "Funzione #2" << std::endl; }; // funzione #2

void g(C c, D d) { std::cout << "Funzione #3" << std::endl; }; // funzione #3

void g(D d, C c = C()) { std::cout << "Funzione #4" << std::endl; }; // funzione #4

void test(C c, D d) {

    std::cout << "Chiamata funzione (a): \nmia risposta -> #1\n";
    f(3.2); // chiamata A
    // Funzioni candidate: #1, #2
    // Funzioni utilizzabili: #1, #2
    // chiama la funzione #1 perché il numero e il tipo di parametri corrispondono

    std::cout << "Chiamata funzione (b): \nmia risposta -> #1\n";
    f('a'); // chiamata B
    // Funzione candidate: #1, #2
    // Funzioni utilizzabili: #1, #2
    // chiama la funzione #1 perché il numero di parametri coincide e in più avviene una promozione da char a double

    std::cout << "Chiamata funzione (c): \nmia risposta -> #2\n";
    // f('a', c); // chiamata C
    // Funzioni candidate: #1, #2
    // Funzioni utilizzabili: #2 (la funzione #1 viene scartata perché il numero di parametri non coincide)
    // chiama la funzione #2 ed avviene una promozione da char a int

    std::cout << "Chiamata funzione (d): \nmia risposta -> #3\n";
    g(c, d); // chiamata D
    // Funzioni candidate: #3, #4
    // Funzioni utilizzabili: #3 (la funzione #4 viene scartata perché l'ordine del tipo dei parametri non coincide con la chiamata)
    // chiama la funzione #3 perché coincide esattamente

    std::cout << "Chiamata funzione (e): \nmia risposta -> #4\n";
    g(d, c); // chiamata E
    // Funzioni candidate: #3, #4
    // Funzioni utilizzabili: #4 (la funzione #3 viene scartata perché l'ordine dei tipi dei parametri non coincide con la chiamata)
    // chiama la funzione #4 perché conicide esattamente

    std::cout << "Chiamata funzione (f): \nmia risposta -> errore\n";
    g(c); // chiamata F
    // Funzioni candidate: #3, #4
    // Funzioni utilizzabili: nessuna
    // genera un erroe di ambiguità perché non esiste nessuna funzione che coincide con la chiamata
}

int main() {
    C c;
    D d;
    test(c, d);
    // std::cout << "Hello, World!" << std::endl;
    return 0;
}
