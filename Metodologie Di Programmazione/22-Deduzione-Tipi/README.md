# Deduzione Tipi

## Deduzione automatica del tipo (Template Type Deduction)

La deduzione automatica del tipo è un meccanismo in C++ che permette al compilatore di dedurre i tipi di dato per i parametri dei template, sia per le funzioni che per le classi. Questo semplifica il codice e riduce la ridondanza, rendendo più agevole l'utilizzo dei template.

### Deduzione per le funzioni template

Consideriamo una funzione template dichiarata come:

```c++
template <typename TT>
void f(PT param);
```

dove:

* `TT` è il nome del parametro del template.
* `PT` è un'espressione sintattica che definisce il tipo del parametro `param`.

Quando la funzione `f` viene chiamata con un argomento `arg` di tipo `targ`, il compilatore deduce:

* Un tipo specifico `tt` per il parametro template `TT`.
* Un tipo specifico `pt` per il tipo del parametro `PT`.

Questo processo porta all'istanziazione del template di funzione con i tipi dedotti, risultando nella funzione:

```c++
void f<tt>(pt param); 
```

**E' importante notare che i tipi dedotti `tt` e `pt` sono correlati, ma spesso non identici.**

Il processo di deduzione si divide in tre casi a seconda della natura di `PT`:

1. **`PT` è una "universal reference":** `PT` è sintatticamente uguale a `TT&&`.
2. **`PT` è un puntatore o un riferimento (ma non una "universal reference").**
3. **`PT` non è né un puntatore né un riferimento.**

### Universal Reference

Una "universal reference" si ha quando l'espressione `PT` è costituita solamente dal nome di un parametro template `typename` seguito da `&&`, senza altri modificatori. 

Ad esempio, dato `TT` come parametro `typename`:

* `TT&&` è una **"universal reference"**.
* `const TT&&` è un riferimento a rvalue (non "universal").
* `std::vector<TT>&&` è un riferimento a rvalue (non "universal").

**Il termine "universal"  indica la capacità di dedurre un riferimento sia a rvalue che a lvalue per `PT`, in base al tipo `targ` dell'argomento passato alla funzione.**

Sebbene non sia una terminologia ufficiale dello standard, il termine **"universal reference"** è stato introdotto da Scott Meyers per semplificare la comprensione di questa regola di deduzione.

#### Caso 1: PT come "universal reference"

Consideriamo il template di funzione:

```c++
template <typename TT>
void f(TT&& param);
```

* **Esempio 1.1 (deduzione di un rvalue):**

```c++
f(5); // targ = int
// deduco pt = int&&, tt = int
```

In questo caso, `targ` è un `int`. Il compilatore deduce `pt` come `int&&` (un riferimento a rvalue) e `tt` come `int`.

### Deduzione del tipo per `auto`

Introdotta in C++11, la parola chiave `auto` permette di definire variabili senza specificarne esplicitamente il tipo. **Il compilatore deduce il tipo in base all'inizializzatore della variabile.**

Esempi:

* `auto i = 5;` // `i` ha tipo `int`
* `const auto d = 5.3;` // `d` ha tipo `const double`
* `auto ii = i * 2.0;` // `ii` ha tipo `double`
* `const auto p = "Hello";` // `p` ha tipo `const char* const`

La deduzione del tipo con `auto` segue in gran parte le stesse regole della "template type deduction".

#### Esempio di deduzione del tipo con `auto`

Analizzando la definizione:

```c++
auto& ri = ci;
```

possiamo associarla alla chiamata `f(arg)` del template di funzione:

```c++
template <typename TT> 
void f(PT param);
```

dove:

* `auto` corrisponde al parametro template `TT`.
* `auto&` corrisponde a `PT`.
* L'inizializzatore `ci` (di tipo `const int&`) corrisponde all'espressione `arg`.

Questo esempio ricade nel secondo caso di deduzione dei parametri template. Per `auto` viene dedotto il tipo `const int`, mentre per `ri` viene dedotto il tipo `const int&`.

#### Attenzione: un caso particolare

La deduzione del tipo con `auto` differisce dalla "template type deduction" quando l'inizializzatore usa le parentesi graffe (sintassi uniforme di inizializzazione).

Esempio:

```c++
auto i = { 1 };
```

In questo caso, l'argomento si considera di tipo `std::initializer_list<T>`. Alcune linee guida suggeriscono di usare `auto` quasi sempre per inizializzare le variabili, ad eccezione dei casi con inizializzatori tra parentesi graffe.

### Conclusione

La deduzione automatica del tipo è uno strumento potente che semplifica l'utilizzo dei template in C++. La comprensione delle "universal reference" e dei diversi casi di deduzione è fondamentale per evitare errori e scrivere codice efficiente e leggibile.
