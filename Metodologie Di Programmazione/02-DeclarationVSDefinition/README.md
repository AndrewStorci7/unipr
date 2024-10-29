# Declaration VS. Definition

## Dichiarazione (declaration)

La dichiarazione di un entità è il processo di **creazione di un nome identificativo** di un entità senza definire la sua struttura/contenuto.

```cpp
int a;
char b;
string c;
```

## Definizione (definition)

La definizione invece è il processo di **creazione della struttura** della nostra entità.

```cpp
/// FILE header.h
int a;    
/// EOF

/// FILE main.c
#include header.h

extern int a = 4; // Definizione di un'entità esterna
char b = 'F'; // Definizione e dichiarazione inline
```

> la parola chiave `extern` viene utilizzata per indicare al compilatore che la seguente variabile/entità verrà definita in un'altro file ed è già esistente, così da non far allocare ulteriore memoria.

> :bulb: \
> Tutte le funzioni di impostazione predefinita sono dichiarate con `extern` in maniera implicita

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

## Dichiarazione pura (possibile da C++11)

La dichiarazione pura, come indicato nel primo paragrafo di questo file, è la creazione di un'entità senza andarla a definire. Serve per dire al compilatore che esiste questa variabile ma che verrà definita _"più avanti"_ nel file

> :bulb:
> In `C++03` la dichiarazione pura degli enumerator non poteva avvenire. \
> Dal `C++11` in poi questo è possibile.











