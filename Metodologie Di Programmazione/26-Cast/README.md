# Cast

## **Cos'è il casting e a cosa serve**

Il <font color="#aa2356">**casting**</font>, o <u>conversione esplicita di tipo</u>, è un meccanismo del C++ che permette di convertire un'espressione da un tipo di dato a un altro. A differenza delle conversioni implicite, che avvengono automaticamente in determinate situazioni, il casting è un'operazione esplicita richiesta dal programmatore.

Il casting è utile in diverse circostanze, ad esempio:

*   Quando si vuole **forzare una conversione** che il compilatore non permetterebbe implicitamente. Questo si verifica quando la conversione potrebbe portare a una perdita di informazioni o a un comportamento inatteso, come nel caso della conversione da `double` a `int`. In queste situazioni, il programmatore si assume la responsabilità della correttezza della conversione.
*   Quando si vuole **controllare a tempo di esecuzione** se una conversione è valida, utilizzando `dynamic_cast`. Questo tipo di cast è utile nelle gerarchie di classi, dove si può verificare la reale natura di un oggetto a runtime.
*   Quando si vuole **documentare esplicitamente** una conversione di tipo, anche se non strettamente necessaria, per migliorare la leggibilità del codice. Questo rende più chiaro al lettore del codice che una conversione è stata effettuata intenzionalmente.
*   Quando si vuole **"scartare" il valore di un'espressione**, convertendola a `void`. Questo utilizzo è spesso legato alla soppressione di warning del compilatore.

## **Vari tipi di casting in C++**

Il C++ offre diverse sintassi per effettuare il casting, ognuna con uno scopo specifico:

1.  **`static_cast`**: È il **cast più frequentemente utilizzato** e serve per effettuare conversioni di tipo tra tipi correlati.
    *   È usato per conversioni implicite ammissibili.
    *   È usato per la conversione inversa a una sequenza di conversioni implicite.
    *   **Implementa downcast** in gerarchie di classi.
    *   Converte tra tipi numerici e enumerazioni.
    *   Converte un'espressione a `void`.

2.  **`dynamic_cast`**: È usato principalmente per i **downcast** e i **mixed-cast** nelle gerarchie di classi con ereditarietà, con la verifica a runtime della validità della conversione. Richiede che la classe base sia polimorfa (ovvero, che contenga almeno una funzione virtuale).
    *   Se il cast ha successo, restituisce un puntatore o riferimento al tipo derivato.
    *   Se il cast fallisce:
        *   Per i puntatori, restituisce `nullptr`.
        *   Per i riferimenti, genera un'eccezione di tipo `std::bad_cast`.
    *   Può essere utilizzato per eseguire upcast ma raramente.
    *   Non è applicabile a tipi non polimorfici.

3.  **`const_cast`**: Viene usato per rimuovere o aggiungere il qualificatore `const` ad un riferimento o puntatore.
    *   Permette di modificare un oggetto che era stato dichiarato `const`.
    *   Il suo uso è considerato pericoloso perché può "rompere" il contratto di non modificabilità dell'oggetto.
    *   Un suo uso è per metodi di una classe che modificano la rappresentazione interna di un oggetto, senza modificarne il significato logico.

4.  **`reinterpret_cast`**: È un cast a basso livello che converte tra tipi non correlati, ad esempio tra puntatori e interi.
    *   È il tipo di cast più pericoloso perché non esegue controlli di tipo.
    *   È usato per convertire tra puntatori di tipi non correlati.
    *   Non può essere usato per rimuovere il qualificatore `const`.
    *   La correttezza del cast è completamente a carico del programmatore.

5.  **Cast "funzionale"**: La sintassi `T(expr)` o `T()`, dove `T` è un tipo, è detta cast funzionale e corrisponde alla costruzione di un oggetto di tipo `T`.
    *   Si applica sia a tipi built-in che user-defined.
    *   Nel caso di un tipo built-in, `T()` produce la zero-initialization.

6.  **Cast stile C**: La sintassi `(T)expr` è ereditata dal C e permette di simulare `static_cast`, `const_cast` e `reinterpret_cast`, ma non `dynamic_cast`.
    *   È considerato un cattivo stile perché non esplicita il tipo di conversione.
    *   Non permette di distinguere tra i vari tipi di casting.
    *   È difficile da individuare nel codice.
    *   Non effettua controlli a run-time come `dynamic_cast`.

**Cattivi usi del casting**

L'uso improprio del casting può portare a bug e comportamenti inattesi. Ecco alcuni esempi di cattivo uso:

*   **Utilizzare `reinterpret_cast` per conversioni non sicure**. L'uso di `reinterpret_cast` dovrebbe essere limitato a situazioni di basso livello, in quanto non effettua controlli di tipo e può portare a errori difficili da individuare.
*   **Utilizzare `const_cast` per modificare dati che dovrebbero essere `const`**. Questo può compromettere l'integrità del programma e rendere il codice più difficile da comprendere.
*   **Utilizzare cast stile C al posto dei cast C++**. I cast stile C sono difficili da individuare nel codice e non specificano il tipo di conversione, rendendo il codice meno leggibile e più soggetto a errori.
*   **Utilizzare `static_cast` per downcast non sicuri**. Mentre `static_cast` è utile per i downcast, non effettua controlli a runtime. In caso di downcast rischiosi, `dynamic_cast` è preferibile.
*   **Usare cast non necessari**. In molti casi, le conversioni implicite sono sufficienti e l'utilizzo di cast espliciti rende il codice inutilmente complicato. L'utilizzo eccessivo di casting può essere segno di un problema di design.

**Esempi di casting**

*   **`static_cast` per la conversione da `double` a `int`:**

```cpp
double d = 3.14;
int i = static_cast<int>(d); // i conterrà 3
```
*   **`dynamic_cast` per un downcast sicuro in una gerarchia di classi:**

```cpp
struct Base { virtual ~Base() { } };
struct Derived : public Base { int x; };

Base* b = new Derived();
Derived* d = dynamic_cast<Derived*>(b);
if (d) {
    d->x = 10; // sicuro: d punta a un oggetto Derived
}
```

*   **`const_cast` per rimuovere `const` (con cautela):**

```cpp
void foo(const int& x) {
    int& y = const_cast<int&>(x);
    //ATTENZIONE: y ora permette di modificare l'oggetto, che
    //era stato definito const!
    // Evitare, quando possibile, questi utilizzi.
}
```
*   **`reinterpret_cast` per convertire un puntatore ad un indirizzo di memoria:**

```cpp
int* ptr;
unsigned int addr = reinterpret_cast<unsigned int>(ptr);
```

*   **Cast funzionale per la creazione di un oggetto temporaneo:**

```cpp
int x = int(3.14);
```
*   **Cast stile C (da evitare):**

```cpp
int x = (int)3.14;
```
