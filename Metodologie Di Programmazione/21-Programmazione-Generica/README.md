# Programmazione Generica

## Contenitori sequenziali

### `std::vector<T>` Vettori 

I **vettori** hanno le stesse caratteristiche degli array per quanto riguarda l'inserimento, l'accesso ad un singolo elemento e l'elimina; la cosa fondamentale che li differenzia è la gestione in memoria. \
Sia gli array che i vettori usano una porzione di memoria contigua (ovvera _attaccata_), ma i vettori (che d'altronde è una classe della libreria standard) possono variare la loro dimensione in maniera dinamica. 

#### Esempio di implementazione di un `vector<T>`
```c++
template <typename T>
class Vector {
    public:
        using value_type = T;
        using size_type = std::size_t;
    
    private:
        value_type* _data;
        size_type size;

        Vector() = default;
        value_type opreator[](const int& index) const; // Per permettere l'operazione di accesso ad una singola cella
        /* altre implementazioni ... */
}
```

#### Nozioni importanti sui vector

- **tempo costante** per fornire l'accesso ad un qualsiasi elemento del vettore.
- <u>inserimento ed elimina</u> sono efficienti se eseguiti in **fondo alla sequenza**, altrimenti hanno tempo di esecuzione lineare.

### `std::deque<T>` Code a doppia entrata

Anche le **code con doppia entrata** beneficiano anche loro di una memorizzazione dinamica, a differenza dei vettori però vengono memorizzati <u>non in maniera contigua</u> ma a **blocchi**.

#### Nozioni importanti sui deque

- <u>inserimento e rimozione</u> efficienti sia **in fondo** alla squenza (come nei vettori) che **all'inizio**.
- accesso agli elementi in **tempo costante**.

### `std::list<T>` Lista

La **lista** è una sequenza di dimensione variabile, memorizzata in modo non contiguo (come per le code) ed ha una struttura doppiamente concatenata; per doppiamente concatenata si intende il fatto che <u>può essere visitata sia andando in "avanti" che "all'indietro"</u>.

#### Nozioni importanti sulle list

- il tempo di esecuzione per l'accesso ad un elemento è lineare, perché va raggiunto tramite i link di ogni "blocco" (più comunemente chiamato _nodo_).
- <u>inserimento e rimozione</u> in **tempo costante**

### `std::forward_list<T>` Lista (scorrimento solo in avanti)

Le **forward list** sono identiche alle liste, l'unica differenza è che possono eseguire lo scorrimento della sequenza solo in avanti.

### "pseudo" contenitori sequenziali

#### `std::array<T, N>`

Sono array con una dimensione fissa (da notare che `N` non è un typename ma un **parametro template valore**)

#### `std::bitset<N>`

E' una sequenza di esattamente **`N` bit** (anche qui, `N` è un **parametro templatico valore**)

#### `std::string`

E' un <u>alias per l'istanza `std::basic_string<char>`</u> del template `std::basic_string`, infatti esistono anche gli alias `std::wstring`, `std::u16string`, `std::u32string`, ecc.


