# Esercizio 4

## Domanda 1

> **Fornire un esempio di violazione della <u>ODR (One Definition Rule)</u> che genera un errore diagnosticabile in fase di collegamento, ma non diagnosticabile in fase di compilazione.**

### Soluzione

#### File: `file1.hh`

```c++
#include <iostream>

struct StrutturaPersonalizzata {

    void foo(const int& i) {
        // ...
    }
};
```

#### File: `file2.hh`

```c++
#include <iostream>

struct StrutturaPersonalizzata {

    void foo(int i) {
        // ...
    }

    void bar(const int& i) {
        // ...
    }
};
```

#### File: `main.cpp`

```c++
#include <iostream>
#include "file1.hh"
#include "file2.hh"

using namespace std;

int main() {

    const int i = 10;

    StrutturaPersonalizzata sp;
    StrutturaPersonalizzata sp1;

    sp.foo(i);
    sp1.foo(i);
}
```

### <font color="4188fe">Soluzione di NotebookLM</font>

L'esempio fornito viola la <font color="effe65">**One Definition Rule (ODR)**</font>, ma l'errore **non è un tipico errore di collegamento** come richiesto dalla query. L'errore presente nell'esempio <u>si manifesta in fase di compilazione e non di linking</u>. Questo è dovuto al fatto che, includendo entrambi gli header (`file1.hh` e `file2.hh`) nel `main.cpp`, il compilatore si trova a gestire **due definizioni differenti della stessa struct `StrutturaPersonalizzata` all'interno della stessa unità di traduzione**, il file `main.cpp`. Di conseguenza, il compilatore rileva un errore di ridefinizione, in quanto le due definizioni della struct sono in conflitto.

Per fornire un esempio corretto di violazione della ODR che generi un errore in fase di linking, ma non in compilazione, è necessario che le **definizioni in conflitto siano presenti in diverse unità di traduzione**.

Ecco un esempio corretto:

**File: `file1.cpp`**
```cpp
// file1.cpp
#include "struttura.h"

void StrutturaPersonalizzata::foo(const int& i) {
  // ...
}
```

**File: `file2.cpp`**
```cpp
// file2.cpp
#include "struttura.h"

void StrutturaPersonalizzata::foo(int i) {
  // ...
}
```
**File: `struttura.h`**
```cpp
// struttura.h
struct StrutturaPersonalizzata {
    void foo(const int& i);
};
```

**File: `main.cpp`**
```cpp
// main.cpp
#include "struttura.h"

int main() {
  StrutturaPersonalizzata sp;
  int i = 10;
  sp.foo(i);
}
```

**Spiegazione:**

*   **`struttura.h`**: Definisce la struct `StrutturaPersonalizzata` con un membro funzione `foo` che accetta un riferimento const a int.
*   **`file1.cpp`**: Implementa il metodo `foo` della struct `StrutturaPersonalizzata` come definito in `struttura.h`.
*   **`file2.cpp`**: Implementa il metodo `foo` della struct `StrutturaPersonalizzata`, **ma con una firma diversa (accetta un `int` per valore anziché un riferimento const)**.
*   **`main.cpp`**: Include `struttura.h` e crea un'istanza della struct, chiamando il metodo `foo` con un intero.

In questo caso:

*   **Compilazione:** La compilazione di `file1.cpp` , `file2.cpp` e `main.cpp` avviene senza errori, in quanto il compilatore verifica che la struttura e i suoi metodi siano dichiarati e implementati correttamente *all'interno di ogni singola unità di traduzione*. Il compilatore compila ogni file `.cpp` separatamente, creando degli object files.
*   **Linking:**  **L'errore si verifica in fase di linking**. Il linker (collegatore) cerca di unire gli object files in un eseguibile e si accorge che ci sono **due definizioni del metodo `foo` con firme diverse per la stessa struct** `StrutturaPersonalizzata`. Questo costituisce una **violazione della ODR**, che richiede che ci sia una singola definizione per ogni entità nel programma finale.  Il linker rileva la **duplicazione/incongruenza delle definizioni** e genera un errore.

**Cosa hai sbagliato:**

*   Hai incluso le definizioni *in conflitto* all'interno dello stesso file, quindi il compilatore ha rilevato l'errore immediatamente. La violazione della ODR, perché si manifesti in fase di link, deve coinvolgere *più* file.

**Ulteriori note:**

*   La ODR (One Definition Rule) è una regola fondamentale del C++ per garantire la consistenza del programma.
*   La compilazione separata permette di dividere il codice in file più piccoli e compilare solo quelli che sono stati modificati, ma richiede che le dichiarazioni siano coerenti tra le diverse unità di traduzione.
*   Gli header files (come `struttura.h` in questo esempio) sono usati per condividere le dichiarazioni tra file diversi.
*   La keyword `extern` viene usata per indicare che una variabile è definita in un'altra unità di traduzione.
*   Le funzioni `inline`, i `template`, `const`, e `constexpr` devono avere una sola definizione per tutto il programma. 

## Domanda 2

> **Scrivere le dichiarazioni dei metodi `operator[]` e `at` del template di classe `std::vector`. Fornire esempi di invocazione dei metodi suddetti e spiegarne brevemente la semantica (evidenziando le differenze).**

### Soluzione 

L'overload del metodo `operator[]` della classe `std::vector` serve per visualizzare o modificare un elemento in una posizione della sequenza.
Il metodo `at()` della classe `std::vector` ha la stessa identica funzione di `operator[]` ma evita l'overflow, ovvero, evita di accedere ad un posizione che va oltre la dimensione della sequenza.

```c++
#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
    std::vector<int> vi = {1, 2, 3, 4, 5, 6};
    
    try {
        std::cout << vi[3] << std::endl;    // stampa correttamente 4
        std::cout << vi.at(3) << std::endl; // stampa correttamente 4
        std::cout << vi.at(6) << std::endl; // l'eccezzione viene catturata dal blocco catch
    } 
    catch (std::out_of_range e) { 
        std::cerr << "Error: " << e.what() << std::endl;
    } 
    catch (...) {}
    
    std::cout << vi[6] << std::endl; // in questo caso stampera un valore casuale, perché stiamo accedendo una zona di memoria che va oltre la dimensione della sequenza  
    
    std::cout << vi.at(6) << std::endl; // in questo caso il programma termina con un errore
}
```

### <font color="4188fe">Soluzione di NotebookLM</font>

Le dichiarazioni dei metodi `operator[]` e `at` del template di classe `std::vector`, insieme ad esempi di invocazione e spiegazione della loro semantica, sono le seguenti:

**Dichiarazioni**

Le dichiarazioni di `operator[]` e `at` per la classe `std::vector` si trovano all'interno della definizione della classe stessa. Poiché `std::vector` è un template, le dichiarazioni includono parametri template per il tipo di elementi contenuti nel vettore e per l'allocatore.

*   `reference operator[](size_type pos);`
*   `const_reference operator[](size_type pos) const;`
*   `reference at(size_type pos);`
*   `const_reference at(size_type pos) const;`

Dove:
* `reference` e `const_reference` sono rispettivamente un riferimento modificabile e un riferimento non modificabile al tipo di elemento contenuto nel vettore.
* `size_type` è un tipo senza segno che rappresenta le dimensioni del vettore.
* `pos` è l'indice dell'elemento a cui si vuole accedere.

**Esempi di invocazione e semantica**

Consideriamo un `std::vector<int>` di esempio:

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {10, 20, 30};

    // Utilizzo di operator[]
    int x = v;  // Accesso all'elemento in posizione 1 (valore 20)
    std::cout << "v: " << x << std::endl;

    v = 40;    // Modifica dell'elemento in posizione 2
    std::cout << "v dopo la modifica: " << v << std::endl;

    // Utilizzo di at()
    int y = v.at(0); // Accesso all'elemento in posizione 0 (valore 10)
    std::cout << "v.at(0): " << y << std::endl;


    try {
        int z = v.at(5); // Tentativo di accesso ad un elemento fuori dai limiti
    } catch (const std::out_of_range& e) {
        std::cerr << "Eccezione: " << e.what() << std::endl;
    }

    // Attenzione: operator[] non esegue controlli di range
    // v = 100; // Questo potrebbe causare un comportamento indefinito (accesso fuori dai limiti).

    return 0;
}
```

**Spiegazione:**

*   `operator[]`:
    *   Fornisce un accesso diretto all'elemento nella posizione specificata tramite l'indice `pos`.
    *   **Non esegue controlli di validità sull'indice**. Se si tenta di accedere a un elemento al di fuori dei limiti del vettore (ovvero se `pos` è maggiore o uguale alla dimensione del vettore), si ha un **comportamento indefinito**, che potrebbe portare a un crash del programma o a risultati errati.
    *   È disponibile sia in versione modificabile (restituisce un `reference`) che in versione `const` (restituisce un `const_reference`).
    *   L'accesso tramite `operator[]` è generalmente più efficiente di `at()` in quanto non comporta l'overhead dei controlli.
*   `at()`:
    *   Fornisce un accesso all'elemento nella posizione specificata tramite l'indice `pos`.
    *   **Esegue un controllo di validità sull'indice**. Se `pos` è fuori dai limiti del vettore, viene lanciata un'eccezione di tipo `std::out_of_range`.
    *   È disponibile sia in versione modificabile (restituisce un `reference`) che in versione `const` (restituisce un `const_reference`).
    *   L'accesso tramite `at()` è più sicuro di `operator[]` perché previene l'accesso a posizioni non valide, ma ha un piccolo costo aggiuntivo di performance dovuto ai controlli eseguiti.

**Differenze chiave**

La principale differenza tra i due metodi è che `operator[]` non esegue controlli di validità sull'indice, mentre `at()` li esegue lanciando un'eccezione nel caso di indice non valido. Questo rende `at()` più sicuro per il debug, ma `operator[]` potenzialmente più efficiente se si è certi che l'indice è sempre valido.

In sintesi:

*   Utilizzare `operator[]` quando la performance è critica e si è certi che l'indice è sempre valido.
*   Utilizzare `at()` quando la sicurezza e la robustezza del codice sono prioritarie, per prevenire errori di accesso fuori dai limiti che possono portare a comportamenti indefiniti.

Si noti che la funzione `at()` è disponibile anche per altri contenitori della libreria standard, come ad esempio `std::array`. Questa uniformità dell'interfaccia dei contenitori permette di utilizzare gli stessi algoritmi e le stesse tecniche in maniera coerente con diversi tipi di contenitori.


