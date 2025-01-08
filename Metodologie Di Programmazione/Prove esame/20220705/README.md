♠# Esame di Metodologie di Programmazione del 2022/07/05
## Soluzioni

### Esercizio 1:
> **(Progettazione tipo concreto)** La seguente presenta alcuni problemi che ne rendono l'utliizzo problematico. Individuare i problemi ed indicare una possibbile soluzione (riscrivendo l'interfaccia).

```c++
struct Matrix {
    // ...
    size_type num_rows();
    size_type num_cols();
    value_type& get(size_type row, size_type col);
    Matrix& operator-();
    Matrix& operator+=(Matrix y);
    Matrix& operator+(Matrix y);
    void print(ostream os);
    // ...
}
```

#### Soluzione

```c++
struct Matrix {
    // ...
    size_type num_rows() const;
    size_type num_cols() const;

    const value_type& get(size_type row, size_type col) const;
    void set(size_type row, size_type col);

    Matrix& operator+=(const Matrix& y);
    void print(ostream& os);
    // ...
};

// ostream& operator<<(ostream& os, const Matrix& m);
Matrix operator-(const Matrix& x, const Matrix& y);
Matrix operator+(const Matrix& x, const Matrix& y);
```

- **`size_type num_rows(); size_type num_cols()`**: per correttezza e per evitare che venga modificato inserire come tipo di ritorno costante [`size_type num_cols() const;`]
- **`value_type& get(size_type row, size_type col)`**: questo metodo ha lo scopo di ritornare il valore di una cella data una riga e una colonna, perciò il tipo di ritorno deve essere valore costante [`const value_type`] per evitarne la modifica. Se si vuole modificare il valore è più corretto creare una funzione membro apposita `set()`.
- **`Matrix& operator-()`**: questo metodo va a sovraccaricare l'operatore `-` in maniera errata e non convenzionale. In primis, la funzione `operator-()` che è un **operatore binario** è consigliabile definirla come funzione <u>non membro</u>. Come seconda errore non ha un parametro che rappresenterebbe l'`rvalue` con la quale effettuare l'operazione di sottrazione [`Matrix& operator-(const Matrix& y)`], il passaggio come parametro di un tipo di dato concreto come <u>`Matrix`</u> è consigliato passarlo per **riferimento costante** (<u>in questo caso costante perché non vogliamo modificarlo, riferimento perché passarlo per valore sarebbe costoso</u>); la seconda invece riguarda il tipo di ritorno: è sempre consigliato ritornare per valore per evitare gravi problemi di memoria [`Matrix operator-(const Matrix& y)`].
- **`Matrix& operator+=(Matrix y);`**: il tipo di ritorno a riferimento (anche se concettualmente parlando è errato) in questo caso è corretto perché restituiamo un puntatore a this [`*this`] per permette la concatenazione; il passaggio del parametro invece è corretto per riferimento ma per evitare di moficarlo intenzionalmente sarebbe meglio passarlo costante.
- **`Matrix& operator+(Matrix y)`**: questo metodo va a sovraccaricare l'operatore `+` in maniera errata e non convenzionale. In primis, essendo un operatore binario è meglio dichiararlo come funzione non membro; il tipo di ritorno: non deve essere per riferimento [`Matrix operator+(Matrix y)`]; infine il parametro deve essere un riferimento costante ad una matrice [`Matrix operator+(const Matrix& y)`].
- **`void print(ostream os)`**: questa è una funzione che serve per stampare il dato concreto. Il passaggio come parametro dell'oggetto ostream fa fatto per **riferimento** [`void print(ostream& os)`].

### Esercizio 2

> Definire la funzioen generica `all_of` che prende in input una sequenza ed un predicato unario e restituisce in output un booleano: la funzione restituisce il valore true se e solo se tutti gli elementi della sequenza soddisfano il predicato. Scrivere inoltre una funzione che prende in input un vettore di numeri interi e usando la funzione all_of appena definita, controlla se tutti gli interi contenuti nel vettore sono negativi

