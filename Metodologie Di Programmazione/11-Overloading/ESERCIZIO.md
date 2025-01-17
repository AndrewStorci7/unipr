## Esercizi sull'Overloading di Funzione in C++

Esercizi creati con **NotebookLM**

### Domande a Risposta Multipla

1.  **Quale affermazione sull'overloading di funzione è FALSA?**
    - [ ] Permette di definire più funzioni con lo stesso nome ma con parametri diversi.
    - [x] Il compilatore sceglie la funzione corretta in base al tipo di ritorno.
    - [ ] L'overloading semplifica la scrittura di codice generico.
    - [ ] L'overloading può rendere il codice più leggibile e intuitivo.

    **Risposta Corretta:** Il compilatore sceglie la funzione corretta in base al **tipo e numero degli argomenti**, non al tipo di ritorno.

2.  **Cos'è l'ADL (Argument-Dependent Lookup)?**
    - [ ] Un meccanismo per definire funzioni con lo stesso nome in spazi dei nomi diversi.
    - [x] Una regola di ricerca dei nomi che considera gli spazi dei nomi associati ai tipi degli argomenti.
    - [ ] Un modo per specificare il comportamento di default di una funzione.
    - [ ] Una tecnica per ottimizzare le chiamate di funzione a tempo di compilazione.

    **Risposta Corretta:** ADL è una **regola di ricerca dei nomi che considera gli spazi dei nomi associati ai tipi degli argomenti**.

3.  **Cosa succede se il compilatore non riesce a trovare una funzione univoca che corrisponda agli argomenti passati?**
    - [ ] Il programma si compila con un warning.
    - [ ] Il programma si compila ma genera un errore a runtime.
    - [x] Il compilatore genera un errore di ambiguità.
    - [ ] Il compilatore sceglie la funzione con il minor numero di parametri.

    **Risposta Corretta:** Il **compilatore genera un errore di ambiguità**.

### Esercizi di Codifica

1.  **Crea una classe `Punto` che rappresenta un punto in un piano cartesiano. Definisci due costruttori:**
    - Un costruttore che prende due coordinate `x` e `y` come argomenti.
    - Un costruttore di default che inizializza il punto all'origine (0, 0).

    **Soluzione:**

    ```c++
    class Punto {
    public:
        double x;
        double y;

        Punto(double x, double y) : x(x), y(y) {} 
        Punto() : x(0), y(0) {}
    };
    ```

2.  **Definisci l'operatore di addizione `+` per la classe `Punto`. L'operatore deve restituire un nuovo `Punto` che rappresenta la somma dei due punti operandi.**

    **Soluzione:**

    ```c++
    Punto operator+(const Punto& p1, const Punto& p2) {
        return Punto(p1.x + p2.x, p1.y + p2.y);
    }
    ```

3.  **Crea una funzione `stampa` overloaded che può stampare un `int`, un `double` o una `stringa`.**

    **Soluzione:**

    ```c++
    #include <iostream>
    #include <string>

    void stampa(int i) {
        std::cout << "Intero: " << i << std::endl;
    }

    void stampa(double d) {
        std::cout << "Double: " << d << std::endl;
    }

    void stampa(const std::string& s) {
        std::cout << "Stringa: " << s << std::endl;
    }
    ```

4.  **Data la classe `Vettore` che rappresenta un vettore numerico:**

    ```c++
    template <typename T>
    class Vettore {
    private:
        T* dati;
        int dimensione;
    public:
        // Costruttori, distruttore e altri metodi...

        T& operator[](int indice) {
            return dati[indice];
        }
    };
    ```

    **Definisci l'operatore di moltiplicazione `*` per la classe `Vettore` che esegue il prodotto scalare tra due vettori.**

    **Soluzione:**

    ```c++
    template <typename T>
    T operator*(const Vettore<T>& v1, const Vettore<T>& v2) {
        // Verifica che i vettori abbiano la stessa dimensione

        T risultato = 0;
        for (int i = 0; i < v1.dimensione; ++i) {
            risultato += v1[i] * v2[i];
        }
        return risultato;
    }
    ```

**Ricorda:** questi sono solo alcuni esempi. Per approfondire la tua conoscenza dell'overloading di funzione, sperimenta con diversi tipi di dati, operatori e scenari. Le fonti fornite trattano l'overloading in dettaglio, ma in un contesto più ampio di programmazione C++. 
