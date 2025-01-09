# Overloading

> :pushpin: In questa lezione affronteremo il concetto di **overload** in C++

## Cos'è l'overloading

L'**overloading** (in ingelse, _**sovraccaricamento**_) è quel meccanismo che permette la riscrittura di una funzione già definita cambiandone il tipo e il numero di parametri.

#### Esempio

```c++
/// Funzione per calcolare la radice quadrata

double sqrt(double val);
float sqrt(float val);
long double sqrt(long double val);

/// In C++ questo è possibile grazie all'verloading
/// In C non esiste perciò al posto di un unica funzione troveremo:

double sqrt(double val);
float sqrtf(float val);
long double sqrtl(long double val);
```

## A cosa serve ?

Serve per rendere il codice più leggibile e soprattutto a semplificare il lavoro dello sviluppatore (così da non dover ricordare tuttu i nomi delle funzioni). \
Come detto in precedenza, in C++ tutto questo è possibile perché il compilatore esegue la **risoluzione dell'overloading**.

## Risoluzione dell'overloading

La risoluzione dell'overloading è quel processo che determina quale funzione deve essere utilizzata in base alla chiamata fatta nel codice. Questo processo crea un insieme di **funzioni candidate**, ovvero un insieme di funzioni che hanno lo stesso nome della funzione chiamata. 

Il compilatore **analizza** quindi il numero di parametri e il tipo dei parametri (_e <u>non</u> il tipo di ritorno_) per scegliere la funzione giusta tra le funzioni candidate in base a certi criteri: 

- **Corrispondenza esatta**: il tipo e il numero dei parametri è identico.
- **Promozioni**: se non c'è una corrispondenza esatta avviene una _promozione integrale_ (es: da `bool` a `int`).
- **Conversione standard**: se nessuno dei due criteri precedenti viene soddisfatto, allora avviene una conversione implicita (es: da `int` a `double`).
- **Conversione esplicita (definita dall'utente)**: la converiosnedi tipo può avvenire in maniera esplicita dall'utente (es: da `double` a `complex<double>` )

Se più funzioni candidate corrispondono agli argomenti con lo stesso livello di priorità, si genera un **errore di ambiguità**.

#### Esempio

```c++
void stampa(float arg) { /* ... */ }
void stampa(double arg) { /* ... */ }
void stampa(string arg) { /* ... */ }

int main() {

    string str = "Hello World!";
    stampa(str); // Funzioni candidate:
                 // - void stampa(float arg)
                 // - void stampa(double arg)
                 // - void stampa(string arg) -> verrà chiamata questa definizione per il criterio di corrispondenza esatta
    
    double d = 4.07612;
    stampa(float(d)); // Funzioni candidate:
                      // - void stampa(float arg) -> verrà chiamata questa per il criterio di conversione esplicita
                      // - void stampa(double arg)
                      // - void stampa(string arg)

    long double ld = 34.912398938123243434535341;
    stampa(ld); // Funzioni candidate:
                // - void stampa(float arg)
                // - void stampa(double arg) -> verrà chiamata questa per il criterio di conversione implicita
                // - void stampa(string arg)
}
```

## Overloading vs Hiding

Prima di andare a spiegare le differenze, precisiamo cos'è l'**hiding** (in inglese, _**oscuramento**_). Il meccanismo di hiding tende ad **nascondere** una dichiarazione in uno scope esterno, tramite la dichiarazione locale (con lo stesso nome) in uno scope interno. \
L'hiding può riguardare variabili, funzioni ed oggetti.

#### Esempio

```c++
#include <iostream>

int x = 10;

int main() {
    int x = 5;
    std::cout << x << std::endl; // stamperà 5
}
```

#### Esempio 2

```c++
#include <iostream>

int f(); // funzione globale

int main() {
    void f(double); // in questo modo sto nascondendo la definizione globale di f()

    f(1); // chiamerà void f(double)
}
```

