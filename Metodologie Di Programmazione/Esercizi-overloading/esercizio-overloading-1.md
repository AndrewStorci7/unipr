# Esercizio preso dalla prova esame del 10 Settembre 2024

> :pushpin:  **(Risoluzione overloading)** Mostrare il processo di risoluzione dell’overloading per le seguenti chiamate di funzione. Per ogni chiamata, indicare: l’insieme delle funzioni candidate; l’insieme delle funzioni utilizzabili; la migliore funzione utilizzabile (se esiste).


```c++
namespace N {

     struct S { S(int); };

     void foo(int i); // funzione #1

     void foo(double d, S s_obj); // funzione #2

     void bar(const char* pc); // funzione #3

} // namespace N

void bar(char c); // funzione #4

void bar(unsigned long ul); // funzione #5

void foo(double d); // funzione #6

void test(const N::S& s_obj) {
     bar(123); // chiamata A
     bar("123"); // chiamata B
     foo(4, s_obj); // chiamata C
     N::foo(4.5, s_obj); // chiamata D
}
```

### Soluzione

```bash
/// Chiamata A
/* Funzioni candidate:
 * - funzione #4
 * - funzione #5
 *
 * Funzioni utilizzabili: tutte e due
 * Miglior funzione utilizzabile: #5 perché il compilatore preferisce la conversione da int a long piuttosto che la conversione da int a short

/// Chiamata B
/* Funzioni candidate:
 * - funzione #4
 * - funzione #5
 * 
 * Funzioni utilizzabili: nessuna delle due perché non è possibile effettuare una conversione da const char* a char oppure unsigned long
 * Perciò darà errore

/// Chiamata C
/* Funzioni candidate:
 * - funzione #1
 * - funzione #2
 * - funzione #6
 *
 * Funzioni utilizzabili: solo la funzione #2 perché il numero di parametri coincide; avverrà una conversione standard da int a double invece per l'oggetto s_obj avverrà un match identico
 * Miglior funzione utilizzabile: #2

/// Chiamata D
/* Funzioni candidate:
 * - funzione #1
 * - funzione #2
 *
 * Funzioni utilizzabili: solo la #2 perché il numero di parametri conincide
 * Miglior funzione utilizzabile: #2

```