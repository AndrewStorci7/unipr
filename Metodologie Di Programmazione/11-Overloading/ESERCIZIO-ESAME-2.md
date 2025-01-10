# Esame del 23 Gennaio 2024

## Esercizio sull'overloading

> **(Risoluzione overloading)** Mostrare il processo di risoluzione dell’overloading per le seguenti chiamate di funzione. Per ogni chiamata, indicare: l’insieme delle funzioni candidate; l’insieme delle funzioni utilizzabili; la migliore funzione utilizzabile (se esiste).

```c++
struct Base {
    void foo(int, double); // funzione #1
    void foo(double, int) const; // funzione #2
    void bar(double); // funzione #3
    void print(std::ostream&) const; // funzione #4
};

struct Derived : public Base {
    void foo(double, double); // funzione #5
    using Base::bar;
    void bar(double) const; // funzione #6
};

int main() {
    Derived der;
    der.foo(1.2, 0); // chiamata (a)
    der.bar(1.2); // chiamata (b)
    der.print(std::cout); // chiamata (c)
    const Base& bas = der;
    bas.foo(1.2, 0); // chiamata (d)
    bas.bar(1.2); // chiamata (e)
    bas.print(std::cout); // chiamata (f)
}
```

#### Soluzione

```c++
struct Base {
    void foo(int, double); // funzione #1
    void foo(double, int) const; // funzione #2
    void bar(double); // funzione #3
    void print(std::ostream&) const; // funzione #4
};

struct Derived : public Base {
    void foo(double, double); // funzione #5
    using Base::bar;
    void bar(double) const; // funzione #6
};

int main() {
    Derived der;

    der.foo(1.2, 0); // chiamata (a)
    // Funzioni candidate: #5, #2, #1
    // Funzioni utilizzabili: #5, #1 (la funzione #2 non è utilizzabile perché der non è const)
    // chiama la funzione #5 perché è quella che corrisponde meglio; nel secondo parametro avviene una conversione implicita da int a double

    der.bar(1.2); // chiamata (b)
    // Funzioni candidate: #6, #3
    // Funzioni utilizzabili: #3 (la funzione #6 non è utilizzabile perché der non è const)
    
    der.print(std::cout); // chiamata (c)
    // Funzioni candidate: #4,
    // Funzioni utilizzabili: #4
    // chiama la funzione #4 nonostante der non sia const
    
    const Base& bas = der;
    
    bas.foo(1.2, 0); // chiamata (d)
    // Funzioni candidate: #1, #2
    // Funzioni utilizzabili: #2 (perché bas è un riferimento costante a der)
    // chiama la funzione #2
    
    bas.bar(1.2); // chiamata (e)
    // Funzioni candidate: nessuna
    // Funzioni utilizzabili: nessuna
    // Genera errore di ambiguità perché non esiste nessuna funzione utilizzabile
    
    bas.print(std::cout); // chiamata (f)
    // Funzioni candidate: #4
    // Funzioni utilizzabili: #4
    // chiama la funzione #4 perché è l'unica utilzzabile
}
```