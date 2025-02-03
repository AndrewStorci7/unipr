# Override Vs Overloading

La differenza principale tra `overriding` e `overloading` risiede nel loro scopo e nel meccanismo con cui vengono implementati.

### **Overriding (sovrascrittura)**

*   L'**overriding** si verifica quando una **classe derivata ridefinisce un metodo virtuale** (o, in alcuni casi, un metodo non virtuale ma questo porta a *hiding* invece che *overriding*) della sua classe base.
*   Il metodo ridefinito nella classe derivata deve avere la **stessa firma** (stesso nome, stesso numero e tipo di parametri) del metodo della classe base.
*   L'overriding è fondamentale per il **polimorfismo dinamico**, poiché consente di chiamare la versione corretta di un metodo a *runtime* in base al tipo dinamico dell'oggetto a cui un puntatore o un riferimento si riferisce.
*   Quando si chiama un metodo virtuale tramite un puntatore o riferimento alla classe base, il compilatore determina a *runtime* quale implementazione del metodo deve essere eseguita in base al tipo effettivo dell'oggetto.
*   L'overriding è strettamente legato all'**ereditarietà** e ai **metodi virtuali**.
*   La parola chiave `override` (introdotta in C++11) è usata per indicare esplicitamente che un metodo di una classe derivata intende sovrascrivere un metodo virtuale della classe base, consentendo al compilatore di verificare che l'intenzione sia corretta.

### **Overloading (sovraccarico)**

*   L'**overloading** si verifica quando **più funzioni o metodi con lo stesso nome sono definiti nello stesso scope**, ma con **firme diverse** (diverso numero o tipo di parametri).
*   L'overloading permette di usare lo stesso nome di funzione per operazioni concettualmente simili ma che operano su tipi di dati diversi.
*   Il compilatore seleziona quale versione della funzione o del metodo chiamare in base al numero e al tipo di argomenti forniti al momento della chiamata.
*   L'overloading è una forma di **polimorfismo statico** o "compile-time" poichè la scelta della funzione corretta è fatta a tempo di compilazione, non a runtime.
*   L'overloading non è strettamente legato all'ereditarietà, e può essere applicato anche a funzioni e metodi non virtuali e/o non appartenenti a gerarchie di classi.
*   L'overloading può verificarsi sia all'interno di una classe, sia tra funzioni non membri o tra funzioni appartenenti a namespace diversi.
*   L'overloading delle funzioni template permette di definire diverse versioni di una funzione template in base ai tipi di parametri template.

#### **Esempio Concreto**

Per chiarire ulteriormente, si può pensare all'esempio dei metodi `print()` nelle classi `Printer`, `FilePrinter` e `NetworkPrinter` nella precedente lezione:

*   **Overriding:** il metodo `print()` nelle classi `FilePrinter` e `NetworkPrinter` fa l' *overriding* del metodo `print()` della classe base `Printer` in quanto hanno la stessa firma, questo permette il polimorfismo dinamico.
*   **Overloading:** Se la classe `Printer` avesse più metodi `print()` con lo stesso nome ma con firme differenti, quello sarebbe *overloading*. Ad esempio:

```cpp
class Printer {
public:
    virtual void print(const std::string& doc);
    virtual void print(int doc_id); // Overloading
};
```

#### **Tabella Riassuntiva**

| Caratteristica   | Overriding                                                                          | Overloading                                                                         |
| :--------------- | :---------------------------------------------------------------------------------- | :---------------------------------------------------------------------------------- |
| **Scopo**        | Ridefinire l'implementazione di un metodo della classe base in una classe derivata.  | Fornire più versioni di una funzione o metodo con lo stesso nome.                       |
| **Firma**        | Stessa firma (nome e parametri) del metodo della classe base (metodo virtuale).     | Firme diverse (numero o tipo di parametri) per funzioni con lo stesso nome nello stesso scope. |
| **Polimorfismo** | Dinamico (a runtime).                                                               | Statico (a compile-time).                                                        |
| **Ereditarietà** | Necessaria (relazione tra classe base e classi derivate).                              | Non necessaria.                                                                      |
| **Parola chiave** | `override` (opzionale, ma consigliata)                                                | Nessuna parola chiave specifica.                                                |
| **Selezione**      | A runtime, in base al tipo dinamico dell'oggetto.                                     | A compile-time, in base al tipo e numero di argomenti.                                |

In sintesi, l'overriding consente di specializzare il comportamento ereditato tramite il polimorfismo dinamico, mentre l'overloading permette di utilizzare lo stesso nome per funzioni con funzionalità simili ma che operano su tipi di dati diversi, effettuando la selezione a tempo di compilazione.
