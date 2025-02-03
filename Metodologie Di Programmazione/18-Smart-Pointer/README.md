#  Smart Pointer

## **Cosa sono e a cosa servono gli smart pointer?**

Gli <font color="25ff25">**smart pointer**</font> sono puntatori **"intelligenti"** forniti dalla libreria standard C++ <u>per gestire automaticamente l'allocazione dinamica della memoria</u>, riducendo la probabilità di errori di programmazione. I puntatori **"raw"** o **"naked"** (quelli forniti direttamente dal linguaggio) <u>sono invece più soggetti a errori</u>, anche per programmatori esperti.

La gestione delle risorse, in particolare della memoria allocata dinamicamente, è un aspetto cruciale della programmazione in C++. L'uso corretto dei puntatori "raw" richiede attenzione per evitare **memory leak** o **dangling pointer**, e questo può diventare complicato in presenza di eccezioni o di codice che gestisce diverse risorse. L'idioma **RAII (Resource Acquisition Is Initialization)** è pensato per neutralizzare questi errori, ma scrivere una classe RAII per ogni tipo `T` può essere ripetitivo e soggetto a errori. La libreria standard C++ fornisce quindi delle classi template per gestire in modo sicuro la memoria allocata dinamicamente: `unique_ptr`, `shared_ptr` e `weak_ptr`.

## **I puntatori "raw" (o "naked")**

Un **puntatore "raw"** è un puntatore fornito direttamente dal linguaggio C++ che memorizza l'indirizzo di memoria di una variabile. I puntatori raw permettono di manipolare direttamente la memoria, ma richiedono una gestione manuale della stessa.
    *   L'allocazione avviene con `new` e il rilascio con `delete`.
    *   Se si dimentica di rilasciare la memoria allocata con `new` si genera un memory leak.
    *   Se si rilascia la memoria con `delete` e si continua a utilizzare il puntatore si genera un dangling pointer.
    *   L'uso di puntatori raw è considerato "cattivo stile" nelle più recenti linee guida di programmazione in C++.

### Puntatore unico: **`std::unique_ptr`**

Un `std::unique_ptr` è un puntatore smart che rappresenta il **possesso esclusivo** di una risorsa.
*   **È l'unico puntatore che può gestire quella risorsa** e, quando l'oggetto `unique_ptr` viene distrutto, la risorsa viene automaticamente rilasciata.
*   Non può essere copiato, ma solo spostato. Lo spostamento trasferisce la proprietà della risorsa a un altro `unique_ptr`.
*   Fornisce metodi per interagire con puntatori "raw", come `reset()`, `get()` e `release()`:
    *   `reset()` prende in gestione una nuova risorsa, rilasciando la precedente.
    *   `get()` restituisce un puntatore "raw" alla risorsa gestita, ma senza cederne la proprietà.
    *   `release()` restituisce il puntatore "raw" e cede la proprietà della risorsa, rendendo lo smart pointer non responsabile del rilascio.
*   È un meccanismo leggero, senza overhead di spazio o tempo rispetto all'uso corretto di un puntatore built-in.
*   È utile per passare oggetti allocati nello heap dentro e fuori dalle funzioni.
*   `unique_ptr` è utile per riferirsi ad oggetti di tipo polimorfico.

#### **Esempio di utilizzo di `unique_ptr`:**

```cpp
#include <memory>

void foo() {
  std::unique_ptr<int> pi(new int(42));
  std::unique_ptr<double> pd(new double(3.1415));

  *pd *= *pd; // si dereferenzia come un puntatore
} // qui termina il tempo di vita di pi e pd e viene rilasciata la memoria
```

### Puntatore condiviso: **`std::shared_ptr`**

Un `std::shared_ptr` è un puntatore smart che implementa il concetto di **proprietà condivisa** di una risorsa.
*   Ogni volta che un `shared_ptr` viene copiato, l'originale e la copia condividono la responsabilità della gestione della stessa risorsa.
*   Mantiene un contatore di riferimenti (`reference counter`) alla risorsa. La copia incrementa il contatore, mentre la distruzione lo decrementa.
*   La risorsa viene rilasciata solo quando il contatore arriva a zero, cioè quando l'ultimo `shared_ptr` che puntava alla risorsa viene distrutto.
*   È copiabile e spostabile.
*   Fornisce i metodi `reset()` e `get()`, con una semantica simile a `unique_ptr`.
*   È utile quando la proprietà di un oggetto non è singola, ma condivisa tra più entità.

#### **Esempio di utilizzo di `shared_ptr`:**

```cpp
#include <memory>

void foo() {
  std::shared_ptr<int> pi;
  {
    std::shared_ptr<int> pj(new int(42)); // ref counter = 1
    pi = pj; // condivisione risorsa, ref counter = 2
    ++(*pi); // uso risorsa condivisa: nuovo valore 43
    ++(*pj); // uso risorsa condivisa: nuovo valore 44
  } // distruzione pj, ref counter = 1
  ++(*pi); // uso risorsa condivisa: nuovo valore 45
} // distruzione pj, ref counter = 0, rilascio risorsa
```

### Puntatore debole: **`std::weak_ptr`**

Un `std::weak_ptr` è un puntatore a una risorsa condivisa che **non partecipa alla gestione della risorsa**.
*   Non incrementa il contatore di riferimenti.
*   Non può accedere direttamente alla risorsa. Per farlo, deve controllare se la risorsa è ancora disponibile usando il metodo `lock()`.
*   Il metodo `lock()` restituisce uno `shared_ptr`. Se la risorsa non è disponibile, lo `shared_ptr` ottenuto conterrà un puntatore nullo.
*   È utile per evitare cicli di riferimenti che causerebbero memory leak.

#### **Esempio di utilizzo di `weak_ptr`:**

```cpp
#include <memory>
#include <iostream>

void maybe_print(std::weak_ptr<int> wp) {
  if (auto sp2 = wp.lock())
    std::cout << *sp2;
  else
    std::cout << "non più disponibile";
}

void foo() {
  std::weak_ptr<int> wp;
  {
    auto sp = std::make_shared<int>(42);
    wp = sp; // wp non incrementa il reference count della risorsa
    *sp = 55;
    maybe_print(wp); // stampa 55
  } // sp viene distrutto, insieme alla risorsa
  maybe_print(wp); // stampa "non più disponibile"
}
```

##### **Funzioni `make_shared` e `make_unique`**

*   La funzione `std::make_shared` alloca sia la risorsa che il blocco di controllo del `shared_ptr` con una singola operazione, migliorando l'efficienza e la sicurezza.
*   La funzione `std::make_unique` (disponibile da C++14) crea un `unique_ptr`.
*   L'uso di queste funzioni è raccomandato per evitare errori di exception safety e per ridurre la necessità di usare direttamente `new` e `delete`.

In sintesi, gli smart pointer sono strumenti essenziali per una gestione efficiente e sicura della memoria in C++, contribuendo a rendere il codice più robusto e facile da mantenere.
