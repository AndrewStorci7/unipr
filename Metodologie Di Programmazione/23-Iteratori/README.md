# Iteratori

## Introduzione

Un'**iteratore** è un _oggetto_ che serve per visitare tutti gli elementi di un _altro oggetto_ senza badare alla sua implementazione (non mi interessa conoscerla). \
Un'iteratore è considerato un tipo di puntatore specializzato (concetto astratto) per la visita che fornisce un punto di **accesso sequenziale**, infatti molti degli algoritmi della **STL** utilizzano le sequenze.

#### Cosa fa un iteratore

- **Iterazione**: fornisce un interfaccia uniforme per l'accesso sequenziale.
- **Astrazione**: nasconde i dettagli dell'implementazione, così da poter essere utilizzata con oggeti di diverso tipo.
- **Manipolazione**: permette di modificare gli oggetti della collezione.

## Tipi di iteratori

Esistono diversi tipi di iteratori, ed ognuno di essi ha operazioni e caratteristiche diverse:
- **Iteratori di Input** (InputIt):
- **Iteratori Forward** (ForwardIt)
- **Iteratori bidirezionali** (BidiretionalIt)
- **Iteratori Random Access** (RandomAccessIt)
- **Iteratori di Output** (OutputIt)

### Iteratori di Input

Gli **iteratori di input** sono iteratori **monodirezionali**, ovvero, che vanno solo _"in avanti"_ e servono per leggere i dati (**una sola volta**) di una collezione.

#### Operazioni consentite:

- `++iter`: avanzamento di una posizione.
- `iter++`: avanzamento postfisso (**DA EVITARE**).
- `*iter`: accesso (**in sola lettura**) dell'elemento corrente.
- `iter->m`: accesso al membro `m` della classe `iter` (<u>solo se `iter` è una classe e se `m` è effettivamente un dato membro</u>).
- `iter1 == iter2`: confronto di **uguaglianza**, utilizzato per confrontare se il nostro iteratore è giunto alla fine.
- `iter1 != iter2`: confronto di **disuguaglianza**.

#### Esempio di input iterator

##### `std::istream_iterator<T>`

```cpp
#include <iterator>
#include <iostream>

int main() {
    // Utilizzo di iteratore per leggere una sequenza di double
    std::istream_iterator<double> i(std::cin);
    std::istream_iterator<double> iend;

    for ( ; i != iend; ++i)
        std::cout << *i << std::endl;

}
```

- `std::istream_iterator<double> i(std::cin)`: costruisco il mio iteratore passando l'input stream.
- `std::istream_iterator<double> iend`: la fine della sequenza la ottengo chiamando il costruttore di **default**.

> :warning: Bisogna tenere conto che l'operazione di incremento potrebbe **invalidare** gli altri iteratori definiti nella nostra sequenza.
> ```cpp
> std::istream_iterator<double> i(std::cin);
> auto j = i;                                   
> 
> std::cout << *i;  // Stampa il valore correttamente
> std::cout << *j;  // Stampa il valore correttamente
> ++i;              // Incremento della posizione
> std::cout << *j;  // UB: undefined behavior 
> ```

### Iteratori Forward

Gl'**iteratori forward** supportano tutte le operazioni degl'iteratori di input ma quando incremento la posizione non va ad invalidare ulteriori iteratori (**sono "riavvolgibili"**) e possono essere utilizzati anche per **scrivere**.

#### Esempio di forward iterator

```cpp
#include <forward_list>
#include <iostream>

int main() {
    std::forward_list<int> lista = {1, 2, 3, 4, 5};

    for (auto i = lista.begin(); i != lista.end(); ++i)
        *i += 10;

    for (auto i = lista.cbegin(); i != lista.cend(); ++i)
        std::cout << *i << std::endl;
}
```
- Nela caso del **primo `for`**, `auto` prende come tipo `std::forward_list<int>::iterator`, perciò è modificabile.
- Nel caso del **secondo `for`**, `auto` prende come tipo `std::forward_list<int>::const_iterator`, perciò è solo lettura.

### Iteratori bidirezionali

Gl'**iteratori bidirezionali** supportano tutte le operazioni dei **forward iterator** ma, in più, accettano il decremento di posizione, ovvero, possono **tornare "indietro"**.

#### Operazioni aggiuntive supportate:

- `--iter`: decremento della posizione.
- `iter--`: decremento postfisso (**DA EVITARE**).

#### Esempio di bidirectional iterator

##### `std::list<T>`

```cpp
#include <list>
#include <iostream>
int main() {
    std::list<int> lista = {1, 2, 3, 4, 5};

    for (auto i = lista.begin(); i != lista.end(); ++i) 
        *i += 10;

    for (auto i = lista.cend(); i != lista.cbegin(); ) {
        --i; // IMPORTANTE: decrementare prima di leggere, altrimenti overflow
        std::cout << *i << std::endl;
    }

    for (auto i = lista.crbegin(); i != lista.crend(); ++i)
        std::cout << *i << std::endl;
}
```
- Nel **terzo `for`**, `auto` prende come tipo `std::list<int>::const_reverse_iterator`, ovvero, **stampa la sequenza al contrario** e **non modificabile**.

### Iteratori ad accesso casuale

I **random access iterator** supportano tutte le operazioni dei **bidirectional iterator** ma possono **spostarsi** in **posizioni più lunghe**.

#### Operazioni aggiuntive supportate:

- `iter += n`: sposta iter di `n` posizioni (<u>se positivo sposta in avanti, se negativo all'indietro</u>).
- `iter -= n`: analogo, ma in direzione opposta.
- `iter + n`: calcola un iteratore spostato di `n` posizioni (**non modifica iter**).
- `n + iter`: equivale a `iter + n`.
- `iter - n`: analogo, ma in direzione opposta.
- `iter[n]`: equivale a scrivere `*(iter + n)`.
- `iter1 - iter2`: calcola la "distanza" tra i due iteratori, ovvero il numero di elementi che dividono le due posizioni.
- `iter1 > iter2`: restituisce `true` se `iter1` viene prima di `iter2`, altrimenti false.
- `iter1 < iter2`, `iter1 >= iter2`, `iter1 <= iter2`: analoghi.

#### Esempio di random access iterator

##### `std::vector<T>`

```cpp
#include <vector>
#include <iostream>
int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};

    for (auto i = vec.begin(); i != vec.end(); i += 2)
        *i += 10;

    for (auto i = vec.cbegin(); i != vec.cend(); ++i)
        std::cout << *i << std::endl;
}
```

### Iteratori di output

Gl'**output iterator** 