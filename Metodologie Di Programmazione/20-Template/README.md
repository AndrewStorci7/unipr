# Template

## Istanziazione

Prima di parlare delle entità **templatiche** dobbiamo spiegare cosa significa **istanza**. \
L'**istanza** di un entità templatica è la vera e propria concretizzazione dell'oggetto con un determinato tipo, cioè, il compilatore quando vede un istruzione di **istanza di template** va a creare in memoria l'oggetto. 

```cpp
MyClass<int> m_int;         // istanza MyClass di tipo int
MyClass<double> m_double;   // istanza MyClass di tipo double
```

## Definizione vs Istanziazione

Il compilatore quando deve compilare le entità templatiche deve analizzare due fasi distinte:
- Definizione
- Instanziazione

### Definizione

La definizione di una entità templatica è la creazione della struttura interna, **ma non l'assegnamento di memoria**.

**Classe templatica**
```cpp
template <typename T>
class Stack {
    private:
        T _data;

    public:
        Stack(const T& d);
}
```

**Funzione templatica**
```cpp
template <typename T>
T& foo(const T& a, const T& b) const;
```

> Nell'esempio sopra viene creata la definizione della classe templatica, ma non viene assegnata nessuna memoria poiché il compilatore non ne conosce il tipo.

### Istanziazione

L'istanza, invece, è la creazione di un entità templatica con l'assegnamento in memoria ed avviene una volta sola per tipo e per entità.

```cpp
MyClass<int> m_int = {5};           // istanza con tipo int
MyClass<double> m_double = {4.78};  // istanza con tipo double

MyClass<int> m_int_2 = {7};         // nessuna istanza di MyClass di tipo int perché è già stata istanziata in precedenza
```
> **L'istanza avviene a tempo di compilazione**.




