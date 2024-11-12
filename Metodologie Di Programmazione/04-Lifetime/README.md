# Tempo di vita (Lifetime)

## Introduzione

In programmazione, il tempo di vita (o lifetime) di un’entità si riferisce al periodo durante il quale una variabile, un oggetto o una funzione esiste ed è accessibile nel programma. In altre parole, è il tempo compreso tra la creazione e la distruzione dell’entità stessa. Il tempo di vita può essere classificato principalmente in:

- **Automatic Storage Duration** (memoria automatica): le variabile locali, come quelle dichiarate all'interno delle funzioni hanno vita breve e vengono istanziate nello _stack_.
- **Static Storage Duration** (memoria statica): le varibiali statiche (al contrario delle varibaili locali) duranto per tutta la durata del proramma, ovvero, dalla loro istanza fino al termine del programma.
- **Dynamic Storage Duration** (memoria dinamica): le entità create dinamicamente durante l'esecuzione del programma. Queste vengono salvate all'interno dello _heap_

## Creazione degli oggetti in memoria

### Stack

Le variabili memorizzate all'interno dello _stack_ sono di breve durata e veloci da inserire e da reperire. L'accesso allo _stack_ è di tipo **LIFO** (**L**ast **I**n **F**irst **O**ut).

```cpp
void funzione() {
    int valore = 42; // Memoria allocata nello stack
} // "valore" viene distrutto quando la funzione termina
```

### Heap

Le variabili memorizzate all'interno dello _heap_ sono quelli la quale non si conosce a priori il tipo o la dimensione e quelle entità che possono variare durante il ciclo di vita di tutto il programma. \
La gestione dello memoria inserita nello _heap_ è interamente del programmatore. Le parole chiave per l'inserimento nello heap sono: `new` o `malloc` (per l'inserimento e allocazione in memoria) e `delete` o `free` (per la deallocazione in memoria).

```cpp
void funzione() {
    int* ptr = new int(42); // Memoria allocata nello heap
    // ...
    delete ptr; // Memoria liberata
}
```

## Concetto del Tempo di Vita di un Oggetto in Due Fasi Distinte: Costruzione e Distruzione

### Costruzione di un oggetto

Il processo di costruzione di un oggetto è suddiviso in due fasi:

- **Allocazione della memoria "grezza"**:

