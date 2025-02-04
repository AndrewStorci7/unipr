# Esercizio 2 della prova del 09 Gennaio 2024

## Progettazione di un tipo concreto

> **La classe templatica `Set` è intesa rappresentare un insieme di elementi di tipo `T`. L’implementazione della classe si basa sulla manipolazione di liste ordinate (senza duplicati). L’interfaccia della classe presenta numerosi problemi; cercare di individuarne il maggior numero e indicare come possono essere risolti (riscrivendo l’interfaccia).**

```cpp
template <typename T>
struct Set {
    std::list<T> my_set; // la lista ordinata di elementi
    Set(); // costruisce insieme vuoto.
    Set(T t); // costruisce singoletto {t}
    unsigned int size(); // numero elementi
    bool contains(Set y); // test di contenimento
    T& min(); // accesso a elemento minimo (primo)
    void erase_min(); // elimina elemento minimo
    void swap(Set y); // scambia *this con y
    std::ostream operator<<(std::ostream os); // output
    // ...
};
```

### Soluzione

```cpp
template <typename T>
struct Set {
    using value_type = T;
    using reference = value_type&;
    using const_reference = const reference;
    using size_t = unsigned int;

    std::list<value_type> my_set;

    Set(); // ok
    Set(const Set& s); // costruttore di copia
    Set(Set&& s); // Costruttore di spostamento

    size_t size() const; // reso const perché non deve modificare l'oggetto

    bool contains(const Set& s) const;  // reso const reference il parametro s, perché non deve poter essere modificato
                                        // reso const il metodo perché non deve modificare l'oggeto this

    value_type min() const; // restituisce per valore e resa const perché non deve poter modificare l'oggetto

    void erase_min(); // ok

    void swap(Set& y); // il parametro ora viene passato per reference

    // Due metodi: 
    //  Primo metodo:
    //      - il primo è richiamarlo all'interno della funzione come se fosse una funzione membro ma va inserita la parola chiave friend (sconsigliato)
    friend std::ostream& operator<<(std::ostream& os) const;

    //  Secondo metodo:
    //      - il secondo è dichiarare la funzione all'esterno dell'oggetto e delegare l'operazione ad una funzione membro (preferibile al primo metodo)
    void print(std::ostream& os) const;
}

std::ostream& operator<<(std::ostream& os, const Set& s) {
    s.print(os);
    return os;
}

std::ostream& operator<<(std::ostream& os, const Set* s) {
    s->print(os);
    return os;
}
```

#### <font color="c466f1">Soluzione di NotebookLM</font>

Analizzando la classe templatica `Set` fornita, si possono identificare diversi problemi e proporre soluzioni per migliorare l'interfaccia e la sua usabilità.

## **Problemi e Soluzioni:**

*   **Mancanza di `using` per tipi:** Per migliorare la leggibilità e la manutenibilità del codice, è utile definire degli alias di tipo all'interno della classe `Set`. Ad esempio, si possono usare `using value_type = T;`, `using reference = value_type&;`, `using const_reference = const reference;`, e `using size_t = unsigned int;`. Questo rende il codice più chiaro e meno dipendente da tipi specifici, facilitando modifiche future.
*   **Costruttore di Copia e Spostamento Mancanti**: La classe `Set` non dichiara un costruttore di copia o spostamento, e ciò può portare a problemi di gestione della memoria e a potenziali errori di compilazione. È fondamentale aggiungere:
    *   Un costruttore di copia: `Set(const Set& s);` per creare una copia profonda dell'oggetto `Set`.
    *   Un costruttore di spostamento: `Set(Set&& s);` per trasferire la proprietà delle risorse da un oggetto `Set` temporaneo a uno nuovo.
*   **`size()` non `const`:** Il metodo `size()` non è dichiarato `const`, ma è buona pratica dichiarare `const` tutti i metodi che non modificano lo stato dell'oggetto. La dichiarazione corretta è `size_t size() const;`.
*   **`contains()` con parametro non `const` reference:** Il metodo `contains()` prende un `Set` per valore, il che implica una copia non necessaria dell'oggetto. È preferibile passare un riferimento `const`: `bool contains(const Set& s) const;`. Inoltre, il metodo stesso dovrebbe essere `const` poiché non modifica l'oggetto su cui viene chiamato.
*   **`min()` che restituisce un riferimento:** Restituire un riferimento a un elemento interno (`T& min();`) può essere pericoloso, in quanto l'utente potrebbe modificare direttamente l'elemento minimo dell'insieme, potenzialmente invalidando l'ordine della lista. È più sicuro restituire una copia dell'elemento: `value_type min() const;`. Inoltre, il metodo deve essere `const` perché non modifica l'oggetto.
*   **`swap()` con parametro non reference:** Il metodo `swap()` riceve il parametro `y` per valore. È più efficiente passarlo per reference, `void swap(Set& y);`.
*   **Operatore di output `<<` come membro:** L'operatore di output `<<` è implementato come un metodo membro, ma tradizionalmente gli operatori di output sono implementati come funzioni `friend` o come metodi pubblici, dato che l'operatore di output agisce su due operandi, un `ostream` e l'oggetto `Set` e quindi non si adatta alla sintassi di un metodo membro.  Si possono usare due approcci per implementare l'output:
    1.  Definire un metodo `print(std::ostream& os) const` all'interno della classe `Set` e poi definire una funzione `friend std::ostream& operator<<(std::ostream& os, const Set& s)` che chiama `s.print(os)`. Questa funzione deve essere una `friend` per accedere ai membri privati della classe.
    2.  Definire una funzione `print(std::ostream& os) const;` membro della classe `Set` e poi definire un operatore `<<` non membro che la richiama: `std::ostream& operator<<(std::ostream& os, const Set& s){s.print(os);return os;}`.
*   **Metodo `erase_min()` che non gestisce l'insieme vuoto**: Il metodo `erase_min()` non gestisce il caso in cui l'insieme sia vuoto e ciò comporta un comportamento indefinito. È necessario sollevare un'eccezione quando si tenta di rimuovere il minimo da un set vuoto.

**Interfaccia Modificata:**

```cpp
template <typename T>
struct Set {
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_t = unsigned int;

    std::list<value_type> my_set;

    Set();                                  // Costruttore di default
    Set(const Set& s);                      // Costruttore di copia
    Set(Set&& s);                          // Costruttore di spostamento

    size_t size() const;                    // Restituisce il numero di elementi
    bool contains(const Set& s) const;   // Verifica se l'insieme contiene l'insieme passato come argomento
    value_type min() const;                  // Restituisce l'elemento minimo (per valore)
    void erase_min();                        // Elimina l'elemento minimo
    void swap(Set& y);                      // Scambia *this con y

    // Primo Metodo per l'output:
    friend std::ostream& operator<<(std::ostream& os, const Set& s){s.print(os);return os;}
    // Secondo Metodo per l'output:
    void print(std::ostream& os) const;
};
```

**Implementazione di Esempio (con alcune funzioni):**

```cpp
template <typename T>
Set<T>::Set() {}

template <typename T>
Set<T>::Set(const Set& s) : my_set(s.my_set) {}

template <typename T>
Set<T>::Set(Set&& s) : my_set(std::move(s.my_set)) {}

template <typename T>
typename Set<T>::size_t Set<T>::size() const {
    return my_set.size();
}

template <typename T>
bool Set<T>::contains(const Set& s) const {
  // Implementare la verifica di contenimento tra insiemi.
    return false; // Per ora non implementato
}

template <typename T>
typename Set<T>::value_type Set<T>::min() const {
    if(my_set.empty()) throw std::runtime_error("Set vuoto, non esiste il minimo");
    return *my_set.begin();
}

template <typename T>
void Set<T>::erase_min() {
    if(my_set.empty()) throw std::runtime_error("Set vuoto, non si può eliminare il minimo");
    my_set.erase(my_set.begin());
}


template <typename T>
void Set<T>::swap(Set& y){
    my_set.swap(y.my_set);
}


template<typename T>
void Set<T>::print(std::ostream& os) const {
    os << "{ ";
    for (const auto& elem : my_set) {
        os << elem << " ";
    }
    os << "}";
}

```
**Ulteriori Miglioramenti:**

*   Aggiungere un costruttore che prende un initializer\_list.
*   Implementare gli altri operatori di confronto, come `==`, `!=`, `<` .
*   Implementare metodi per l'inserimento e la rimozione di elementi (oltre a `erase_min()`).
*   Usare `std::move` per ottimizzare le operazioni di inserimento e rimozione quando possibile.
*   Gestire correttamente le eccezioni e validare gli input.

Questo approccio, basato sulle fonti fornite e sulle correzioni apportate, fornisce una base più solida e robusta per la classe `Set`.
