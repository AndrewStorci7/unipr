# Analisi scritta della soluzione

### Consegna:

> Adattare l'algoritmo di Needleman-Wunsch per ottenere un confronto 
> tra versioni diverse di un codice sorgente. 
> Preparare un test con un file C++ da almeno 100 righe. 
> L'obiettivo è quello di **dare priorità alla struttura dei 
> blocchi del codice** e poi ai caratteri, per ipotizzare un 
> matching strutturale dei vari body annidati. 
> E' possibile processare i token e considerarli 
> come singoli caratteri con una adeguata funzione di scoring. 
> **L'obiettivo è essere tolleranti a testi modificati 
> (es. rinomina di variabili) ma non confondere 
> un identificatore con un numero.** 
> Opzionale: gli spazi/tab invece possono essere aggiunti 
> o tolti senza penalità. 
> L'output deve indicare i cambiamenti effettuati, 
> come lista di azioni o stringa di cambiamento 
> (- per cancellazione e caratteri aggiunti o modificati) 

## Fasi dell'analisi

### Fase 1

La consegna richiede di **dare priorita' ai blocchi del codice** ed osservando
un qualsiasi codice si puo' intuire una strtuttura dati ad albero, dove il padre sara' l'intero file
e i blocchi annidati saranno le definizioni di funzioni, di classi o di strutture;
a sua volta i blochi annidati potranno essere dei cicli o dei blocchi `if/else` 
o ulteriori funzioni (solo per le classi/strutture).
```c++
/// Blocco 1

int main(...) { /// Blocco 2
    
    if (...) { /// Blocco 3
        /// ... istruzioni
    }
}

void foo(...) { /// Blocco 4
    
}
```

Una volta ottenuta la struttura dell'albero, per ogni nodo avremo la sua **matrice di Needleman-Wunsch**.

I blocchi potranno avere uno di questi identificativi:
```c++
enum STM_TYPE {
    FUNCTION,   /// Funzione
    CLASS,      /// Classe
    STRUCT,     /// Struttura
    
};
```

Il nodo conterra' i seguenti dati:

- **Blocchi Figli**: una lista dei blocchi figli inseriti in ordine di lettura (up-to-bottom)
- **Tokens**: che sono semplicemnete le istruzioni presenti allo stesso livello:
  - ```c++
    /// Blocco GLOBAL
    int a = 10; // istruzione (token)
    void foo() { // altra istruzione ma allo stesso tempo un blocco
        if (...) { // istruzione e blocco IF del blocco FUNCTION
            ...
        }
    } 
    ```
- **Tipo del blocco**: tipo del blocco
 
[//]: # (- **Nome**: identificatore del blocco)

[//]: # (- **Tipo**: il tipo della funzione, `NULL` negli altri casi)

[//]: # (- **Contesto**: Il contesto non e' altro che il contenuto all'interno delle parentesi tonde)

[//]: # (  - Il contesto avra' a sua volta un tipo, per differenziare tra lista di parametri ed espressione logica)

[//]: # (- **Matrice di Needleman-Wunsch**)

### Fase 2

I token verranno "parsati" da un'apposita funzione di parsing per identificare il tipo di token e il suo valore.
```c++
enum TOKEN_TYPE {
    /// Valori testuali/generici
    DIRECTIVES, // #include <libreria>, #define <qualcosa>
    IDENTIFIER, // nome della variabile o funzione
    NUMBER,     // valore numerico
    STRING,     // valore testuale
    // POINTER,    // puntatore
    OPERATOR,   // +, -, *, /, ==, =, ...

    /// Parole chiave del linguaggio
    TYPE,       // tipo della variabile: int, float, double, ...
    // KEYWORD,    // if, else, for, while, return, class, ...

    UNKNOWN,    // da cpaire come gestire
    EMPTY = -1,
};
```

Per identificare un blocco, la stringa letta deve sempre terminare con `{`. \
Leggo ogni singolo carattere fino ad arrivare al simbolo di termine; tutto il contenuto letto prima mi serve
per determinare il tipo del blocco.

> :warning: La stessa stringa che utilizzo per identificare 
> il tipo del blocco far' parte dei tokens

### Fase 3

Fase dove richiamo l'algoritmo ricorsivamente di Needleman-Wunsch per formare le varie matrici 







