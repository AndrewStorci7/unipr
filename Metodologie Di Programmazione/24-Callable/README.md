# Callable

## **Cos'è un "callable"?**

In C++, il termine <font color="#ff45145">**"callable"**</font> si riferisce a qualsiasi entità che può essere invocata come una funzione. Questo concetto è fondamentale perché permette di generalizzare algoritmi, accettando diverse forme di "funzioni" come argomenti. Molti algoritmi generici della libreria standard sono infatti disponibili in versioni che accettano un "callable" come parametro, permettendo all'utente di personalizzare il comportamento dell'algoritmo. 

I tipi di dati che rientrano nel concetto di "callable" sono:

*   **Puntatori a funzione**
*   **Oggetti funzione** (o funtori)
*   **Espressioni lambda** (a partire da C++11)

## **Puntatori a Funzione**

Un puntatore a funzione è una variabile che memorizza l'indirizzo di una funzione. Questo consente di passare funzioni come argomenti ad altre funzioni, o di memorizzarle in strutture dati.  Ad esempio, data la funzione `bool pari(int i);`, il suo nome può essere usato per istanziare il predicato unario di un algoritmo come `std::find_if`, legando il parametro `UnaryPred` al tipo concreto `bool (*)(int)`. Questo tipo rappresenta un puntatore a una funzione che prende un intero come argomento e restituisce un booleano.

*   Tecnicamente, sarebbe possibile passare le funzioni per riferimento invece che per valore, ma questo è considerato un pessimo stile perché non porta alcun beneficio e complica la comprensione del codice.
*   I puntatori a funzione permettono di invocare una funzione attraverso l'indirizzo a cui puntano.

## **Oggetti Funzione (Funtori)**

Un oggetto funzione è un'istanza di una classe che ha l'**operatore di chiamata di funzione `operator()`** definito. Questo operatore permette di invocare l'oggetto come se fosse una funzione. 

Ad esempio, una `struct Pari` può essere definita con un `operator()` che restituisce `true` se un numero è pari e `false` altrimenti. 

```cpp
struct Pari {
    bool operator()(int i) const {
        return i % 2 == 0;
    }
};
```
Un oggetto di tipo `Pari`, come `pari`, può essere utilizzato nella sintassi di una chiamata di funzione, come `pari(12345)`.

*   L'operatore `operator()` può essere marcato `const` perché spesso gli oggetti funzione sono "stateless", ovvero non modificano lo stato dell'oggetto.
*   Gli oggetti funzione forniscono al compilatore maggiori opportunità per l'ottimizzazione del codice, rispetto alle normali funzioni. Usando oggetti funzione con tipi distinti, si possono ottenere più istanze di un template di funzione, con codice ottimizzato per ogni specifica invocazione.
*   Gli oggetti funzione sono spesso chiamati "policy objects" quando specificano il significato di operazioni chiave di un algoritmo.
*   Un oggetto funzione può "portare con sé" dei dati che usa per la sua operazione, senza necessità di variabili globali.

## **Espressioni Lambda**

Le espressioni lambda sono un modo conciso per definire oggetti funzione "anonimi" direttamente nel punto in cui vengono utilizzati. Sono state introdotte con C++11.

Un'espressione lambda ha la seguente sintassi:

```cpp
[](/*lista catture*/) (/*lista parametri*/) { /*corpo*/ }
```

Ad esempio, per implementare un predicato che controlla se un numero è pari si può usare la seguente espressione lambda:

```cpp
[](const long& i) { return i % 2 == 0; }
```

*   La **lista delle catture** `[]` permette di specificare le variabili locali che la lambda può usare nel suo corpo.
    *   `[soglia]` cattura la variabile `soglia` per valore.
    *   `[&soglia]` cattura la variabile `soglia` per riferimento.
    *   `[=]` cattura tutte le variabili locali usate nel corpo per valore.
    *   `[&]` cattura tutte le variabili locali usate nel corpo per riferimento.
    *   È consigliabile usare sempre catture esplicite per una maggiore leggibilità del codice.
*   Il modificatore `mutable` permette di modificare le variabili catturate anche se il metodo `operator()` è `const`.
*   Le espressioni lambda possono essere utilizzate per definire oggetti funzione "al volo", senza dover dichiarare una classe apposita. In pratica, una lambda viene convertita dal compilatore in una classe anonima con un `operator()` corrispondente.
*   Una lambda può accedere ai membri di un oggetto usando `this` nella lista di cattura.
*   Le espressioni lambda possono essere assegnate ad una variabile usando `auto` per la deduzione del tipo.

**Riepilogo**

*   I "callable" sono tipi di dati che possono essere invocati come funzioni.
*   I puntatori a funzione memorizzano l'indirizzo di una funzione.
*   Gli oggetti funzione (funtori) sono istanze di classi con `operator()` definito.
*   Le espressioni lambda sono un modo conciso per definire oggetti funzione anonimi.
*   L'uso di "callable" permette di generalizzare algoritmi e personalizzare il loro comportamento.
*   Oggetti funzione e lambda possono migliorare le prestazioni grazie all'ottimizzazione del codice da parte del compilatore.
*   Le lambda offrono un modo più conciso e flessibile per definire oggetti funzione, soprattutto quando sono usati solo una volta.
