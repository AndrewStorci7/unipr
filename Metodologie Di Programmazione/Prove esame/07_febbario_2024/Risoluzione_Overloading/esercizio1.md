# Esercizio 1 prova del 07 Febbraio 2024

### Risoluzione overloading

> **Mostrare il processo di risoluzione dell’overloading per le seguenti chiamate di funzione. Per ogni chiamata, indicare: l’insieme delle funzioni candidate; l’insieme delle funzioni utilizzabili; la migliore funzione utilizzabile (se esiste).**

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

void f(double d); // funzione #1

void f(int i, C c = C()); // funzione #2

void g(C c, D d); // funzione #3

void g(D d, C c = C()); // funzione #4

void test(C c, D d) {
    f(3.2); // chiamata A
    f(’a’); // chiamata B
    f(’a’, c); // chiamata C

    g(c, d); // chiamata D
    g(d, c); // chiamata E
    g(c); // chiamata F
}
```

#### Soluzione

- **Chiamata A**:
    - <u>**Funzioni candidate**</u>: `#1`, `#2`.
    - <u>**Funzioni utilzzabili**</u>: `#1`, `#2`.
    - <u>**Miglior funzione utilizzabile**</u>: la funzione `#1` è la miglior funzione utilizzabile per **match perfetto**, il numero di parametri e il tipo del parametro combaciano.

- **Chiamata B**:
    - <u>**Funzioni candidate**</u>: `#1`, `#2`.
    - <u>**Funzioni utilzzabili**</u>: `#1`, `#2`.
    - <u>**Miglior funzione utilizzabile**</u>: la funzione `#2` è la miglior funzione utilizzabile perché il compilatore preferisce la promozione alla conversione standard: nella funzione `#1` per l'appunto verrebbe una **conversione standard** da `char` a `double`, invece nella funzione `#2` una **promozione** da `char` a `int`.

- **Chiamata C**: 
    - <u>**Funzioni candidate**</u>: `#1`, `#2`.
    - <u>**Funzioni utilzzabili**</u>: `#2`.
    - <u>**Miglior funzione utilizzabile**</u>: la funzione `#2` è la miglior funzione utilizzabile perché il numero di parametri combacia; per il primo parametro avviene una **promozione** da `char` a `int`.

- **Chiamata D**:
    - <u>**Funzioni candidate**</u>: `#3`, `#4`.
    - <u>**Funzioni utilzzabili**</u>: `#3`, `#4`.
    - <u>**Miglior funzione utilizzabile**</u>: la funzione `#3` è la miglior funzione utilizzabile per il **match perfetto**.

- **Chiamata E**:
    - <u>**Funzioni candidate**</u>: `#3`, `#4`.
    - <u>**Funzioni utilzzabili**</u>: `#3`, `#4`.
    - <u>**Miglior funzione utilizzabile**</u>: la funzione `#4` è la miglior funzione utilizzabile per il **match perfetto**.

- **Chiamata F**:
    - <u>**Funzioni candidate**</u>: `#3`, `#4`.
    - <u>**Funzioni utilzzabili**</u>: `#4`.
    - <u>**Miglior funzione utilizzabile**</u>: la funzione `#4` è la miglior funzione utilizzabile perché per il parametro avviene una costruzione dell'oggetto `D` con l'oggetto `C` e per il secondo parametro avviene una costruzione di default senza parametri.

