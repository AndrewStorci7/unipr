# Algoritmi della `stdlib`

## Oggetto funzione (Funtore)

Un **oggetto funzione** (o funtore) è semplicemente un oggetto che può essere utilizzato come funzione. 
> :bulb: Prassi passarli per **valore**

```cpp
struct MaggioreDiN {
    int N;

    MaggioreDiN(int n) : N(n) {}

    bool operator() (int i) const {
        return i > N;
    }
}

void pippo (const std::vector<int>& vi) {
    if (std::all_of(vi.begin(), vi.end(), MaggioreDiN(10000)))
        std::cout << "Numero non valido";
}
```

### Algoritmo di ricerca (`find_if`)

La seguente definizione di `find_if` che è un algoritmo di ricerca, è progettato per ricercare in qualsiasi contenitore iterabile. \
I suoi parametri sono:
- **`Iter first`**: iteratore del primo elemento
- **`Iter last`**: iteratore dell'ultimo elemento
- **`UnaryPred pred`**: predicato unario

> :bulb: Nelle funzioni che ricercano con iteratori, nel caso affermativo restituiscono l'iteratore, altrimenti restituiscono l'ultimo, che sta ad inidicare che non è stato trovato l'oggetto ricercato. 


```cpp
template<typename Iter, typename UnaryPred>
Iter find_if(Iter first, Iter last, UnaryPred pred) {
    for ( ; first != last; ++first ) {
        if (pred(*first))
            return first;
    }
    return last;
}

void foo (const std::vector<int>& vi) {
    if (std::find_if())
}
```

## Algoritmo `find_first_of`

> :bulb: Fino a qualche anno fa in tutti gli algoritmi che richiedevano iteratori, accettavano solo coppie di iteratori dello stesso tipo

```cpp
template<typename Iter, typename Iter2, typename BinaryPred>
Iter find_first_of (Iter f1, Iter l1, Iter2 f2, Iter2 l2, BinaryPred pred) {
    for ( ; f1 != l1; ++f1 ) {
        for ( Iter2 it2 = f2; it2 != l2; ++it2) {
            if (pred(*f1, *it2))
                return f1;
        }
    }
    return l1;
}

template<typename Iter, typename Iter2>
bool binary_pred(Iter iter1, Iter2 iter2) const {
    return iter == iter2;
}
```
Nel secondo `for` abbiamo bisogno di creare una variabile temporanea che itera l'**Iteratore `f2`** perché esso non deve essere modificato per il fatto che viene utilizzato all'interno di un ciclo.

> :bulb: Un **predicato Binario** è un predicato che accetta due parametri.

## Algoritmo `copy` & `copy_if`

```cpp
template <typename InputIt, typename OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first) {
    for ( ; first != last; ++first ) {
        *d_first = *first;
        ++d_first;
    }
    return d_first;
}

template <typename InputIt, typename OutputIt, typename UnaryPred>
OutputIt copy_if(InputIt first, InputIt last, OutputIt d_first, UnaryPred pred) {
    for ( ; first != last; ++first ) {
        if (pred(*first)) {
            *d_first = *first;
            ++d_first;
        }
    }
    return d_first;
}

void foo(std::vector<int>& vi) {
    std::vector<double> vd(vi.size(), 0.0);
    std::copy_if(vi.begin(), vi.end(), vd.begin(), MaggioreDiN(40)); // Undefined behavior

    std::copy(vi.begin(), vi.end(), vd.begin()); // Undefined behavior
}
```
Gli algoritmi di **copia** della `stdlib` di default vanno a **sovrascrivere** il dato.


> :bulb: all'iterno del `for` è possibile eseguire questa cosa:
> ```cpp
> for ( int i = 0; i < n; ++i, ++y, ... )
> ```
> l'ultima parte permette di raggruppare tutte le variabili che vengono incrementate all'interno del `for` (**solamente quelle che hanno uno scope al di fuori della funzione**).

## Analisi classe `back_insert_iterator`

La class `back_insert_iterator` accetta come tipo di dato un contenitore.

L'overload dell'operatore di assegnamento (`operator=`) agisce in questo modo:
- Come parametro accettare un dato **parametrico**.
- Al posto di sostituire il dato con un altro, lo aggiunge alla fine (`push_back`). \
L'operatore assegnamento della `back_insert_iterator` gestisce anche il caso in cui il dato passato è un vector e che si voglia inserire in mezzo al contenitore; esso non va a sovrascrivere ma sposta tutti gli elementi di una posizione e poi lo va ad inserire.

> :bulb: Questo è un esempio di funzione di copia che **non va a sovrascrivere**.
> :bulb: Le classi templatiche non supportano la deduzione automatica del tipo.