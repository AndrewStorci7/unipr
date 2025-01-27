# Soluzioni esame del 23 Gennaio 2024

## Esercizio 1:

> **(Risoluzione overloading)** Mostrare il processo di risoluzione dell’overloading per le seguenti chiamate di funzione. Per ogni chiamata, indicare: l’insieme delle funzioni candidate; l’insieme delle funzioni utilizzabili; la migliore funzione utilizzabile (se esiste).

```c++
struct Base {
    void foo(int, double); // funzione #1
    void foo(double, int) const; // funzione #2
    void bar(double); // funzione #3
    void print(std::ostream&) const; // funzione #4
};

struct Derived : public Base {
    void foo(double, double); // funzione #5
    using Base::bar;
    void bar(double) const; // funzione #6
};

int main() {

    Derived der;
    der.foo(1.2, 0); // chiamata (a)
    der.bar(1.2); // chiamata (b)
    der.print(std::cout); // chiamata (c)

    const Base& bas = der;
    bas.foo(1.2, 0); // chiamata (d)
    bas.bar(1.2); // chiamata (e)
    bas.print(std::cout); // chiamata (f)
}
```

#### Soluzione

- **Chiamata A**:
    - <u>**Funzioni candidate**</u>: #5, #1, #2
    - <u>**Funzioni utilizzabili**</u>:
        - **Funzione #5**: il numero dei parametri coincide (nel caso del secondo parametro avviene una **conversione standard (implicita)** da `int` a `double`).
        - **Funzione #1**: il numero di parametri coincide (nel caso del primo parametro avviene una **conversione standard (implicita)**  da `double` a `int`).
    - <u>**Miglior funzione utilizzabile**</u>:
        - **Funzione #5**: il compilatore preferisce la funzione #5 perché effettua una converiosne in meno.

- **Chiamata B**:
    - <u>**Funzioni candidate**</u>: #6, #3
    - <u>**Funzioni utilizzabili**</u>:
        - **Funzione #3**: il numero di parametri coincide e il tipo del parametro all'interno della chiamata coincide.
    - <u>**Miglior funzione utilizzabile**</u>:
        - **Funzione #3**: viene utilizzata questa funzione per **match identico** (perfetto).

- **Chiamata C**:
    - <u>**Funzioni candidate**</u>: #4
    - <u>**Funzioni utilizzabili**</u>: nessuna perché la funzione #4 è chiamabile solamente su un oggetto istanziato con `const`.
    - <u>**Miglior funzione utilizzabile**</u>: nessun, il compilatore genererà un errore a compile time: `undefined reference`.

- **Chiamata D**:
    - <u>**Funzioni candidate**</u>: #1, #2.
    - <u>**Funzioni utilizzabili**</u>:
        - **Funzioni #2**: il numero dei parametri coincide e l'oggetto chiamante è `const`.
    - <u>**Miglior funzione utilizzabile**</u>:
        - **Funzione #2**: viene utilizzata questa funzione per **match identico** (perfetto).

- **Chiamata E**:
    - <u>**Funzioni candidate**</u>: #3.
    - <u>**Funzioni utilizzabili**</u>: nessuna perchè la funzione #3 può essere chiamata solo su oggetti `const`
    - <u>**Miglior funzione utilizzabile**</u>: nessuna, il compilatore genera un errore a compile-time: `undefined reference`.

- **Chiamata F**:
    - <u>**Funzioni candidate**</u>: #4.
    - <u>**Funzioni utilizzabili**</u>:
        - **Funzioni #4**: il numero dei parametri coincide e l'oggetto chiamante è `const`.
    - <u>**Miglior funzione utilizzabile**</u>:
        - **Funzione #4**: viene utilizzata questa funzione per **match identico** (perfetto).

## Esercizio 2

> **(Conversioni implicite)** Le conversioni implicite del C++ si classificano in **<u>corrispondenze esatte</u> (E)**, **<u>promozioni</u> (P)**, **<u>conversioni standard</u> (S)**, **<u>conversioni definite dall’utente</u> (U)**. Assumendo che le variabili `f`, `d` e `ul` abbiano tipo, rispettivamente, `float`, `double` e `unsigned long`, per ognuno dei seguenti accoppiamenti argomento/parametro indicare (se esiste) la categoria della corrisponente conversione implicita.

| Indice | Argomento | Parametro formale    | Soluzione |
|--------|-----------|----------------------|-----------|
| (1)    | "Hello"   | const char*          | **E**     |
| (2)    | "Hello"   | std::string          | **U**     |
| (3)    | f         | int                  | **S**     |
| (4)    | (f - d)   | double               | **S**     |
| (5)    | ul        | const unsigned long& | **E**     |

## Esercizio 3

> **(Funzione generica)** Definire la funzione generica `contains` che prende in **input** <u>due sequenze</u>, non necessariamente dello stesso tipo, e restituisce in **output** <u>un booleano</u>: la funzione restituisce il valore `true` se e solo se ogni elemento della seconda sequenza compare, in una posizione qualunque, nella prima sequenza. Implementare la funzione usando, in maniera appropriata, l’algoritmo generico `std::find`; elencare quindi i requisiti imposti dall’implementazione sui parametri della funzione.

```c++
#include <algorithm>

template <typename T, typename C = T>
struct IsEqual {
    using value_type = T;
    // using value_type2 = C;
    using ref = value_type&;
    // using ref2 = value_type2&;
    using cref = const ref;

    value_type val;
    // value_type2 val2;

    IsEqual(value_type val) : val(val) {}
    
    bool operator()(cref v) const {
        return val == v;
    }
};

template <typename InputIt1, typename InputIt2 = InputIt1>
bool contains(
    InputIt1 first1, InputIt1 last1,
    InputIt2 first2, InputIt2 last2
) {

    for ( ; first2 != last2; ++first2) {    
        if (std::find_if(first1, last1, IsEqual(*first2)) == last1)
	        return false;
    }
    return true;
}
```

## Esercizio 4

> **(Gestione risorse)** La classe seguente contiene errori inerenti la corretta gestione delle risorse. Individuare due problemi logicamente distinti, indicando la sequenza di operazioni che porta alla loro occorrenza. Fornire quindi una versione alternativa della classe che risolva i problemi individuati, spiegando i motivi per i quali tale soluzione si può ritenere corretta.

```c++
class C {
    int* pi; 
    int* pj; 
    std::string str;

public:
    C(const std::string& s) : pi(new int), pj(new int), str(s) { }
    ~C() { delete pi; delete pj; }
};
```

#### Soluzione

- **Costruttore**: il costruttore è implementato in maniera errata, perché non si può effettuare un