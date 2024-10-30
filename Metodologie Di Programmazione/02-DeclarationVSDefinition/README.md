# Declaration VS. Definition

## Dichiarazione (declaration)

La dichiarazione di un entità è il processo di **creazione di un nome identificativo** di un entità senza definire la sua struttura/contenuto.

In altre parole la dichiarazione informa al compilatore che esiste (o esisterà) nel programma un entità con quello specifico nome e quello specifico tipo.

```cpp
extern int a;   // DICHIARAZIONE PURA
int b;          // Dichiarazione e definizione
```

> :bulb: Nell esempio sopra, il compilatore con l'istruzione `int b` esegue sia la dichiarazione che la definizione, ovvero, va ad allocare memoria per quella determinata variabile e gli assegna un valore o casuale oppure 0.

## Dichiarazione pura

### Variabili

La dichiarazione pura, come indicato nel primo paragrafo di questo file, è la creazione di un'entità senza andarla a definire. Serve per dire al compilatore che esiste questa variabile ma che verrà definita _"più avanti"_ nel file

> :bulb: \
> In `C++03` la dichiarazione pura degli enumerator non poteva avvenire. \
> Dal `C++11` in poi questo è possibile.

### Funzioni

Introduce la funzione al compilatore, specificandone la **firma** (il nome, il tipo di ritorno e i parametri) <u>senza fornire il corpo della funzione</u>, cioè senza descrivere cosa essa fa. La dichiarazione fornisce solo le informazioni necessarie per poter chiamare la funzione altrove nel programma.

```cpp
int somma(int a, int b);    // Dichiarazione pura di una funzione
```

> :bulb: \
> Tutte le **funzioni** di impostazione predefinita sono dichiarate con `extern` in maniera implicita

#### Enumerator

La parola chiave `enum` (che sta per **enumerator**) serve per dichiarare delle costanti.

```cpp
/// file.h
enum Colors {
    Primary,
    Secondary,
    Footer,
    ...
}
```

##### Underlying type

In `C++11` possiamo definire il tipo di dato del nostro **enumerator**, in `C++03` veniva impostato in modo predefinito `int`.

```cpp
enum class Colors: unsigned int { Primary, Seocndary, Title, ... }
```

## Definizione (definition)

### Variabili

La definizione invece è il processo di **creazione della struttura** della nostra entità.

In altre parole quando andiamo a definire una variabile stiamo dicendo al compilatore di allocare memoria per quella specifica entità di quello specifico tipo.

```cpp
/// FILE header.h
#include <iostream>

int a = 4756;
/// EOF

/// FILE main.cpp
#include "header.h"

extern int a;       // Definizione di un'entità esterna
std::cout << a;     // Stamperà 4756
char b = 'F';       // Dichiarazione e definizione
```

> la parola chiave `extern` viene utilizzata per indicare al compilatore che la seguente variabile/entità verrà definita in un'altro file ed è già esistente, così da non far allocare ulteriore memoria.

### Funzioni

Include la dichiarazione della funzione, ma aggiunge anche il corpo della funzione, ovvero il blocco di codice che ne implementa la logica. È qui che il compilatore può generare il codice per l’esecuzione effettiva della funzione.

```cpp
int somma(int a, int b) {
    return a + b;
}
```

### Tipi di dato opachi

I tipi di dato **opachi** sono definiti in modo anonimo, ovvero, la loro definizione/implementazione è nascosta all'esterno. Esistono funzioni utilizzabili dall'esterno che servono per interagire con il tipo in questione ma la struttura rimane sconosiuta (e deve rimanere così). \
**Questi tipi di dato servono per mantenere il codice pulito e facile da manutenere**.

#### Puntatore opaco

Un puntatore **opaco** è una forma di tipo opaco. Un puntatore opaco è un puntatore a un tipo di dato la cui definizione completa non è visibile al codice che lo usa. Tipicamente, nel file di intestazione (header) si dichiara solo un puntatore a una struttura (senza definire la struttura stessa), permettendo così di usare il puntatore per riferirsi al tipo, ma senza conoscere la struttura interna.

```cpp
// file.h
typedef struct MyStruct* MyOpaqueType;
```

Qui `MyOpaqueType` è un puntatore opaco, dato che `struct MyStruct` non è definita nel file di intestazione. La struttura viene effettivamente definita nel file sorgente (ad esempio `file.c`) e può essere manipolata solo tramite funzioni specifiche, rendendo così la struttura interna non accessibile al codice che include `file.h`.

## Tipi di Alias

Gli alias in quasiasi linguaggio di programmazione servono per dare un nome identificativo ad un variabile e serve per renderlo più leggibile.

### Alias in `C++03`

In `C++03` per definire un alias veniva utilizzata la parola chiave `typedef`.

```cpp
typedef int Intero;         // int
typedef long InteroLungo;   // long
typedef int* PtrIntero;     // puntatore a int
```

### Alias in `C++11`

In C++11 per definire un alias si utilizza la parola chiave `using`.

```cpp
using Parola = std::string;
using IntContenitore = std::vector<int>;
```

#### Alias per i template

```cpp
/// Template
template <typename T>
using Ptr = T*;
```

In questo modo possiamo richiamare `Ptr` in questo modo:
- `Ptr<int>`
- `Ptr<std::string>`
- `Ptr<char>`

#### Alias di namespace

I namespace sono dei nomi identaificativi per un _"spazio di lavoro"_. Questi servono per raggruppare porzioni di codice in modo più intuitivo e logico.

```cpp
namespace Numerical {
    class Rational { /* ... */ };
    class Irrational { /* ... */ };
    // ...
}
```

è quindi possibile anche dare un **alias** al nostro namespace

```cpp
namespace Numerical = num;
```