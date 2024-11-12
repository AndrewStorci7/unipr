# Campo di azione (scope)

## Introduzione

Lo **scope** è una porzione di codice dichiarata con un certo nome identificativo e serve per raggruppare una serie di entità (funzioni, classi, variabili, ecc...). \
Gli scope hanno dunque lo scopo di facilitare la realizzazione di un codice modulare e facile da mantenere (e facile da _"correggere"_).

## Scope di `namespace`

Lo **scope di namespace** ha una visibilità interna, ovvero, qualsiasi entità dichiarata o definita al suo interno è visibile se viene chiamata con il prefisso del namespace.

```cpp
/// Numbers.hh
namespace Numbers {
    int a = 10;         // Visibile all interno di Numbers 
}

/// main.cpp
...
std::cout << Numbers::a << std::endl;   // Stamperà 10
std::cout << a << std::endl;            // Darà errore perché non è stata dichiarata nessuna variabile a all interno di main.cpp
```

### Scope Globale (caso speciale)

Le entità che vengono dichiarate al di fuori di qualsiasi scope, sono dette **globali**.

```cpp
/// header.hh
int a = 10;

/// main.cpp
std::cout << a << std::endl;    // Stamperà 10
```

## Scope di blocco

Il **block scope** si riferisce agli elementi dichiarati all'interno di un blocco delimitato da parentesi graffe `{}`. Le variabili hanno una durata limitata al blocco e non possono essere richiamate o utilizzate al di fuori di esso (<u>al contrario dei namespace</u>).

```cpp
{
    int a = 20;
    int z = 4;
}

std::cout << a << std::endl;    // Errore: a non è visibile
```

## Scope di classe

Lo **scope di classe** è il contesto in cui i membri dichiarati all interno di essa cambiano visibilità in base ai qualificatori (**public, private, protected**). \
Per i membri `private`, la visibilità è solo all interno della classe e per i membri `protected` la visibilità è anche nelle sottoclassi; per i membri `public`, invece, sono visibili anche al di fuori di essa.

```cpp
class Pippo {
    public:
        void foo();
    private:
        int a;
    protected:
        int b;
}

Pippo p;
p.foo()     // legittimo perché la funzione è public
p.a         // illegittimo perché l attributo è private
```

## Scope di funzioni

Lo **scope di funzione** è la porzione di codice che sta al suo interno; le entità definite al suo interno **"nascono" al richiamo di essa** e **"muoiono" al termine del suo ciclo**.

```cpp
int foo(int b) {
    int a = 10;                  // visibile solo all interno della funzione
    return a + b; 
}
```

## Scope di enumerazioni (`enum class`)

Quando si definisce un'enumerazione, le costanti definite all'interno hanno uno scope limitato all'enumerazione stessa, ma si può qualificare l'accesso usando il nome dell'enumerazione (o possono essere importate direttamente nel loro scope di dichiarazione se non si utilizza `enum class`).

```cpp
enum class Colors { Red, Green, Blue };
// Colors::Red, Colors::Green, Colors::Blue
```

## Scope Potenziale vs Scope Effettivo

- **Scope Potenziale**: Si riferisce alla porzione di codice in cui un identificatore potrebbe essere visibile e utilizzabile, a patto che non ci siano ostacoli (come il name hiding). Per esempio, una variabile definita all'inizio di una funzione ha potenzialmente l'intera funzione come ambito di visibilità.

- **Scope Effettivo**: È la parte di codice dove _**l'identificatore è effettivamente accessibile**_. Se altri identificatori nascondono la variabile (vedi il concetto di name hiding), l'ambito effettivo è ristretto rispetto all'ambito potenziale.

- **Differenza**: Lo scope potenziale è un'area più ampia e rappresenta il "dove l'identificatore potrebbe agire", mentre lo scope effettivo rappresenta la porzione di codice "dove l'identificatore effettivamente agisce". Le differenze emergono quando meccanismi come il name hiding limitano la visibilità.

## Modifiche di scope

### 1. Name Hiding

Il **name hiding** avviene quando una variabile dichiarata in uno scope globale con un certo nome viene dichiarata all interno di un altro scope con  lo stesso nome.

```cpp
int a = 7;      // scope globale
{
    int a = 19; // name hiding
    std::cout << a << std::endl; // stamperà 19
}
```

### 2. ADL (Argument-Dependent Lookup)

In C++, la **Argument-Dependent Lookup (o Koenig Lookup)** è il <u>processo in cui il compilatore cerca di risolvere il nome di una funzione basandosi sugli argomenti passati</u>. Questo meccanismo è utile per identificare le funzioni corrette in base al namespace associato agli argomenti.

```cpp
namespace N {
    struct A {};
    void f(A) {}
}
N::A a;
f(a); // L'ADL trova N::f poiché "a" è nel namespace N.
```

### 3. Uso di nomi qualificati

Un nome qualificato è un nome preceduto dal nome del suo namespace o della classe a cui appartiene. Questo è utile per chiarire quale identificatore deve essere utilizzato, evitando ambiguità:

```cpp
namespace A {
    int value = 10;
}
int value = 5;

void example() {
    int value = 20;
    std::cout << value;     // Stampa 20 (locale)
    std::cout << ::value;   // Stampa 5 (globale)
    std::cout << A::value;  // Stampa 10 (namespace A)
}
```

### 4. Dichiarazione e direttive di `using`

- **`using` dichiarazione**: Importa un singolo nome da un namespace nel contesto corrente, evitando la necessità di specificare il namespace completo.

```cpp
using std::cout;
cout << "Hello, World!";
```

- **`using` direttive**: Importa tutti i nomi di un namespace in un contesto, rendendoli direttamente accessibili.

```cpp
using namespace std;
cout << "Hello, World!";
```

- **Differenza tra dichiarazione e direttiva di `using`**: La dichiarazione `using` importa un singolo simbolo e mantiene un migliore controllo sull'ambito, mentre la direttiva `using` può introdurre ambiguità se utilizzata con troppi nomi, specialmente in grandi progetti.

## Linee guida sull utilizzo di Dichiarazione/Direttiva di `using`

- **“rompono”** il meccanismo di separazione dei nomi fornito dai namespace
- vanno usate solo se **davvero utili**
- **preferire le using declaration rispetto alle using directive**, perché introducono meno nomi (i.e., meno sorprese)
- in tutti i casi, **limitare al massimo lo scope delle using declaration/directive** (e.g., scope di blocco o scope di classe);
- **NON** usarle a scope di namespace/globale, in particolare in un header file


