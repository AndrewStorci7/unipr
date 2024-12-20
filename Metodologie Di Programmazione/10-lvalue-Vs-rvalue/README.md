# Lvalue & Rvalue

> :punchpin: In questo documento vediamo la differenza tra `lvalue` e `rvalue` e ne capiamo il senso

In C++, ogni espressione è caratterizzata da un tipo e da una categoria di valore. **Capire le categorie di valore è fondamentale perché influenza come le espressioni vengono valutate e utilizzate in diversi contesti, in particolare in relazione alla gestione della memoria e all'ottimizzazione delle prestazioni.**

Esistono tre categorie di valore primarie: prvalue, xvalue e lvalue.

**Le categorie di valore classificano le espressioni, non i valori.**

### Categorie di valore primarie

*   **lvalue:**  Un'espressione lvalue (locator value) è un'espressione la cui valutazione determina l'identità di un oggetto o di una funzione. **In sostanza, un lvalue rappresenta un oggetto che ha un'ubicazione specifica in memoria e a cui è possibile fare riferimento.**
    *   Esempi di espressioni lvalue:
        *   Il nome di una variabile, come `std::cin` o `std::endl`.
        *   Una chiamata di funzione che restituisce un riferimento lvalue.
        *   Espressioni di assegnazione e assegnazione composta, come `a = b` o `a += b`.
        *   Espressioni di pre-incremento e pre-decremento, come `++a` e `--a`.
        *   L'espressione di dereferenziazione `*p`.
        *   Espressioni di accesso ai membri, come `a.m` (con alcune eccezioni).
*   **prvalue:** Un'espressione prvalue (pure rvalue) è un'espressione la cui valutazione:
    *   Calcola il valore di un operando di un operatore built-in, oppure
    *   Inizializza un oggetto.
    *   **In generale, un prvalue rappresenta un valore temporaneo o un valore letterale che non ha un'ubicazione fissa in memoria.**
    *   Esempi di espressioni prvalue:
        *   Letterali (eccetto i letterali stringa), come `42`, `true` o `nullptr`.
        *   Chiamate di funzione che restituiscono un valore non riferimento.
        *   Espressioni di post-incremento e post-decremento, come `a++` e `a--`.
        *   Espressioni aritmetiche, come `a + b` o `a % b`.
        *   Espressioni logiche, come `a && b`, `a || b` o `!a`.
        *   Espressioni di confronto, come `a < b` o `a == b`.
        *   L'espressione di indirizzo `&a`.
*   **xvalue:** Un'espressione xvalue (expiring value) è un'espressione glvalue che denota un oggetto le cui risorse possono essere riutilizzate. **In pratica, un xvalue rappresenta un oggetto che sta per essere distrutto o il cui stato non è più necessario.**
    *   Esempi di espressioni xvalue:
        *   `std::move(x)`: Questa funzione restituisce un riferimento rvalue all'oggetto `x`, rendendolo un xvalue.
        *   Espressioni di accesso ai membri di un rvalue, come `a.m` dove `a` è un rvalue e `m` è un membro dati non statico.
        *   Cast a un riferimento rvalue, come `static_cast<char&&>(x)`.

### Categorie di valore miste

*   **glvalue:** Un'espressione glvalue (generalized lvalue) è un'espressione che è sia un lvalue sia un xvalue.
*   **rvalue:** Un'espressione rvalue è un'espressione che è sia un prvalue sia un xvalue.

### Importanza delle categorie di valore

La distinzione tra le diverse categorie di valore è importante per diversi motivi:

*   **Ottimizzazione delle prestazioni:**  Conoscendo la categoria di valore di un'espressione, il compilatore può ottimizzare il codice generato. Ad esempio, se un'espressione è un xvalue, il compilatore può utilizzare la *move semantics* per spostare le risorse dell'oggetto anziché copiarle, migliorando le prestazioni.
*   **Risoluzione dell'overload:** Le categorie di valore influenzano la selezione delle funzioni in caso di overload. Ad esempio, se una funzione ha due overload, uno che accetta un riferimento lvalue e l'altro che accetta un riferimento rvalue, il compilatore sceglierà l'overload appropriato in base alla categoria di valore dell'argomento passato alla funzione.
*   **Gestione della memoria:**  Le categorie di valore influenzano il ciclo di vita degli oggetti temporanei. Ad esempio, un prvalue che rappresenta un oggetto temporaneo verrà distrutto alla fine dell'istruzione in cui viene utilizzato, mentre un xvalue può avere una durata estesa se viene associato a un riferimento.

In sintesi, comprendere le categorie di valore è essenziale per scrivere codice C++ efficiente, corretto e leggibile.
