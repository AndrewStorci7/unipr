# Esercizio 3 prova del 07 Febbraio 2024

### Funzione generica

> **Scrivere l’implementazione dell’algoritmo generico min_element, che prende come input una sequenza ed un criterio di ordinamento (un predicato binario) e restituisce l’iteratore all’elemento della sequenza di valore minimo (secondo tale criterio di ordinamento); l’algoritmo si comporta in modo standard nel caso di sequenza vuota. Elencare in modo esaustivo i requisiti imposti dall’implementazione sui parametri di tipo e sugli argomenti della funzione. In particolare, individuare le categorie di iteratori che nonpossono essere utilizzate per istanziare il template, motivando la risposta.**

#### Soluzione breve

> :warning: La soluzione completa si trova nei file `min_elem.h` e `esercizio.cpp`

```c++
template <typename T>
struct LowerThan {

    using value_type = T;
    using const_reference = const value_type&;

    LowerThan() = default;

    bool operator()(const_reference val1, const_reference val2) {
        return val1 < val2;
    }

    bool operator()(const char*& val1, const char*& val2) {
        return strcmp(val1, val2) >= 0;
    }

};

template <typename Iter, typename BinaryPred>
Iter min_element(Iter first, Iter last, BinaryPred pred) {

    Iter min = first;

    for ( ; first != last; ++first ) {
        std::cout << *min << " is minor than " << *first << "?" << std::endl;
        if (not pred(*min, *first)) {
            min = first;
        }
    }

    return (min != first) ? min : last; 
}
```