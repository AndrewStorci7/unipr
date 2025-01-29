# Esercizio 1

> Mostrare il processo di risoluzione dell’overloading per le seguenti chiamate di funzione. Per
ogni chiamata, indicare: l’insieme delle funzioni candidate; l’insieme delle funzioni utilizzabili;
la migliore funzione utilizzabile (se esiste).

```c++
namespace N {
    void foo(int, double); // funzione #1
    void foo(double, int); // funzione #2
} // namespace N

void foo(double, double); // funzione #3

int main() {
    
    foo(42, 3.14); // chiamata A
    N::foo(42, 3.14); // chiamata B

    using namespace N;
    foo(3.14, 42); // chiamata C
    
    using N::foo;
    foo(42, 3.14); // chiamata D
}
```

#### Soluzione 

- **Chiamata A**:
    - <u>**Funzioni candidate**</u>: `#3`.
    - <u>**Funzioni utilizzabili**</u>: `#3`.
    - <u>**Miglior funzione utlizzabile**</u>: `#3`, perché è l'unica disponibile tra i candidati e soprattutto l'unica visibile. In più per il primo parametro avviene una conversione standard da `int` a `double`.

- **Chiamata B**:
    - <u>**Funzioni candidate**</u>: `#2`, `#1`, `#3`.
    - <u>**Funzioni utilizzabili**</u>: `#2`, `#1`.
    - <u>**Miglior funzione utlizzabile**</u>: il compilatore sceglie la funzione `#1` per corrispondenza esatta.

- **Chiamata C**:
    - <u>**Funzioni candidate**</u>: `#2`, `#1`, `#3`.
    - <u>**Funzioni utilizzabili**</u>: `#3`, `#2`, `#1`.
    - <u>**Miglior funzione utlizzabile**</u>: il compilatore sceglie la funzione `#2` per corrispondenza esatta.

- **Chiamata D**:
    - <u>**Funzioni candidate**</u>: `#2`, `#1`.
    - <u>**Funzioni utilizzabili**</u>: `#2`, `#1`.
    - <u>**Miglior funzione utlizzabile**</u>: il compilatore sceglie la funzione `#1` per corrispondenza esatta
