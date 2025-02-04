# Esercizio 1 della prova del 09 Gennaio 2024

## Risoluzione Overloading

> **Mostrare il processo di risoluzione dell’overloading per le seguenti chiamate di funzione. Per ogni chiamata, indicare: l’insieme delle funzioni candidate; l’insieme delle funzioni utilizzabili; la migliore funzione utilizzabile (se esiste); il motivo di eventuali errori di compilazione.**

```cpp
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
    const std::string& s2 = cm.last(); // chiamata B
    std::string& s3 = cc.first(); // chiamata C
    const std::string& s4 = cc.last(); // chiamata D
    bar(s4.size()); // chiamata E
}
```

### Soluzione

- **Chiamata A**:
    - <u>**Funzioni candidate**</u>: `#1`, `#2`.
    - <u>**Funzioni utilizzabili**</u>: `#1`, `#2`.
    - <u>**Miglior funzione utilzzabile**</u>: la funzione `#1` perché l'oggetto chiamate è modificabile e la variabile sulla quale verrà restituito il risultato non è `const`.

- **Chiamata B**:
    - <u>**Funzioni candidate**</u>: `#3`, `#4`.
    - <u>**Funzioni utilizzabili**</u>: `#4`.
    - <u>**Miglior funzione utilzzabile**</u>: la funzione `#4` perché l'oggetto chiamate è modificabile e la variabile sulla quale verrà restituito il risultato è `const`.

- **Chiamata C**:
    - <u>**Funzioni candidate**</u>: `#1`, `#2`.
    - <u>**Funzioni utilizzabili**</u>: `#2`.
    - <u>**Miglior funzione utilzzabile**</u>: nessuna funzione utilizzabile, perché l'oggetto sulla quale verrà restituito il risultato è modificabile.

- **Chiamata D**:
    - <u>**Funzioni candidate**</u>: `#3`, `#4`.
    - <u>**Funzioni utilizzabili**</u>: `#3`, `#4`.
    - <u>**Miglior funzione utilzzabile**</u>: la funzione `#4` perché l'oggetto chiamante è `const` e l'oggetto sulla quale verrà salvato il risultato è `const`.

- **Chiamata E**:
    - <u>**Funzioni candidate**</u>: nessuna
    - <u>**Funzioni utilizzabili**</u>: nessuna
    - <u>**Miglior funzione utilzzabile**</u>: nessuna perché non esistono funzioni `bar` nello scope globale.