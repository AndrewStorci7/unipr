# Esame del 9 Gennaio 2024

## Esercizio 1 

> **(Progettazione tipo concreto)** La classe templatica `Set` è intesa rappresentare un insieme di elementi di tipo `T`. L’implementazione della classe si basa sulla manipolazione di liste ordinate (senza
duplicati). L’interfaccia della classe presenta numerosi problemi; cercare di individuarne il maggior
numero e indicare come possono essere risolti (riscrivendo l’interfaccia).

```c++
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

};
```

#### Soluzione

```c++
template <typename T>
struct Set {
    
    std::list<T> my_list; // ok

    Set() : my_list() {}; // ok

    Set(T t) : my_list(t) {}; // Ho inserito : my_list(t) per effettuare lo spostamento ed evitare la copia

    unsigned int size() const; // ho aggiunto ritorno costante per evitare la modifica (anche se viene passato per valore) 

    bool contains(const Set& y); // ho modificato il tipo del parametro a riferimento costante, dato che non devo poter permettere la modifica (essendo un confronto)

    T min() const; // ho tolto il ritorno per riferimento ed ho aggiunto const per evitare la modifica inovlontaria

    void erase_min(); // ok

    void swap(Set& y); // ho inserito il parametro a riferimento, altrimenti non avviene nessuno scambio

    void print(std::ostream& os); // funzione dichiarata per poterla chiamare all'interno dell'overload dell'operatore di lettura (operator<<)

}

template <typename T>
std::ostream operator<<(std::ostream& os, const Set<T>& set); 
/**
 * Ridefinizione dell'overload dell'operatore di lettura:
 * Questa funzione particolare non può essere definita all'interno di una classe (si potrebbe 
 * fare utilizzando friend, che è sconsigliato).
 * Perciò va definita al di fuori della classe
 */
```