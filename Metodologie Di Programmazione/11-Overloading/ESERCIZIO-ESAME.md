# Esercizio sull'overloading preso dall'esame del 9 Gennaio 2024

```c++
#include <string>

namespace N {

    struct C {

        std::string& first(); // funzione #1

        const std::string& first() const; // funzione #2

        std::string& last(); // funzione #3

        const std::string& last() const; // funzione #4

    }; // class C

    void bar(double); // funzione #5

    std::string& bar(int); // funzione #6

} // namespace N

void foo(N::C& cm, const N::C& cc) {

    std::string& s1 = cm.first(); // chiamata A
    // Funzioni candidate: #1, #2
    // chiama la funzione #1 perché viene salvata in una variabile di tipo riferiemnto a string

    const std::string& s2 = cm.last(); // chiamata B
    // Funzioni candidate: #3, #4
    // chiama la funzione #4 perché viene salvata in una variabile di tipo riferimento costante a stringa

    std::string& s3 = cc.first(); // chiamata C
    // Funzioni candidate: #1, #2
    // viene generato un errore per ambiguità, perché cc è un riferimento costante ad un oggetto C

    const std::string& s4 = cc.last(); // chiamata D
    // Funzioni candidate: #3, #4
    // chiama la funzione #4 perché viene salvato in una variabile di tipo riferimento costante a stringa e l'oggetto è un riferimwnto costante

    bar(s4.size()); // chiamata E
    // Genera un errore perche non e presente nessuna dichiarazione dellonscope locale/interno della funzione bar()
}
```

## Risoluzione esercizio di NotebookLM

Analizziamo le chiamate di funzione nel codice che hai fornito, tenendo conto delle regole di overload resolution e del concetto di hiding in C++:

**Chiamata A:** `std::string& s1 = cm.first();`

*   **Funzioni candidate:**  `#1 std::string& first();` e `#2 const std::string& first() const;`.
*   **Risoluzione:** La funzione `#1` è la migliore corrispondenza perché `cm` è un riferimento non-costante a un oggetto `N::C`.  Il compilatore privilegia una funzione membro non-costante quando l'oggetto è non-costante.

**Chiamata B:** `const std::string& s2 = cm.last();`

*   **Funzioni candidate:** `#3 std::string& last();` e `#4 const std::string& last() const;`.
*   **Risoluzione:** Entrambe le funzioni `#3` e `#4` potrebbero essere candidate, ma poiché il risultato viene assegnato a un riferimento costante (`const std::string&`), il compilatore sceglie la versione `#4` che restituisce un riferimento costante. Questo evita una conversione implicita da riferimento non-costante a riferimento costante.

**Chiamata C:** `std::string& s3 = cc.first();`

*   **Funzioni candidate:** Solo `#2 const std::string& first() const;` è una candidata valida, poiché `cc` è un riferimento costante a un oggetto `N::C`. 
*   **Risoluzione:** La chiamata genera un **errore di compilazione**. La funzione `#2` restituisce un riferimento costante, ma `s3` è un riferimento non-costante. Non è possibile convertire implicitamente un riferimento costante a un riferimento non-costante.

**Chiamata D:** `const std::string& s4 = cc.last();`

*   **Funzioni candidate:** Solo `#4 const std::string& last() const;` è una candidata valida, poiché `cc` è un riferimento costante.
*   **Risoluzione:** La chiamata è corretta. La funzione `#4` restituisce un riferimento costante, compatibile con il tipo di `s4`.

**Chiamata E:** `bar(s4.size());`

*   **Funzioni candidate:** Nessuna delle funzioni `bar()` dichiarate è accessibile in questo scope. Le funzioni `#5` e `#6` sono definite nello scope del namespace `N`, ma non sono state rese visibili nello scope di `foo()` tramite using-declaration o qualificazione esplicita. 
*   **Risoluzione:** La chiamata genera un **errore di compilazione** perché il nome `bar` non è definito nello scope corrente. 

Per risolvere l'errore nella chiamata E, è necessario rendere le funzioni `bar()` visibili nello scope di `foo()`. Puoi farlo in due modi:

*   **Utilizzando una using-declaration:**

```c++
using N::bar; 
```

*   **Qualificando esplicitamente il nome della funzione:**

```c++
N::bar(s4.size()); 
```

In entrambi i casi, il compilatore cercherà la funzione `bar()` nel namespace `N` e, grazie all'overloading, selezionerà la versione appropriata in base al tipo dell'argomento (`s4.size()` restituisce un valore di tipo `size_t`, che verrà convertito in `double` per la chiamata a `N::bar(double)`).
