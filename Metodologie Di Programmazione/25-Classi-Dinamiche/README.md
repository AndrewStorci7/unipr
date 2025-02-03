# Classi Dinamiche

## **Classi Dinamiche e Up-cast**

Le <font color="#00f3ff">classi dinamiche</font> sono classi che contengono **<u>almeno</u> un metodo virtuale**. La presenza di un metodo virtuale abilita la **risoluzione dell'overriding a tempo di esecuzione** e la **RTTI** <u>(Run-Time Type Identification)</u>. Per gli oggetti di classi dinamiche, il compilatore associa un puntatore che permette al <u>**sistema di supporto a tempo di esecuzione (RTS)**</u> di accedere alle informazioni di tipo della classe. Questo puntatore è noto come **vptr**, e permette di effettuare la chiamata corretta alla funzione virtuale di una classe derivata.

Quando si ha una classe base e una classe derivata pubblicamente dalla classe base, è possibile effettuare un up-cast. **L'up-cast** è la conversione implicita di un puntatore o riferimento da un oggetto della classe derivata a un puntatore o riferimento a un oggetto della classe base. Questo è possibile grazie alla relazione "IS-A".
Ad esempio, se abbiamo una classe `Base` e una classe `Derived` che deriva pubblicamente da `Base`:

```cpp
class Base {
    /* ... */
};

class Derived : public Base {
    /* ... */
};
```
Possiamo scrivere:
```cpp
Base* base_ptr = new Derived;
```

Questo codice è valido perché un oggetto `Derived` "è un" tipo di `Base`. L'up-cast permette di usare un oggetto derivato come se fosse un oggetto della classe base, ignorando le caratteristiche specifiche della classe derivata e concentrandosi sulle caratteristiche che condivide con la classe base. L'utente vuole lavorare con oggetti di tipo `Base`, astraendo dalle differenze tra le possibili concretizzazioni.

## **Relazioni IS-A e HAS-A**
Le relazioni tra classi possono essere di due tipi principali: **IS-A** e **HAS-A**.
*   **Relazione IS-A (è un):** Questa relazione si manifesta attraverso l'ereditarietà pubblica. Indica che una classe derivata è una specializzazione o un tipo particolare della classe base.  Un oggetto della classe derivata può essere trattato come un oggetto della classe base.  Ad esempio, un `Professore_Ordinario` "è un" `Docente`. L'up-cast è tipico di questa relazione e permette di trattare gli oggetti di tipo specifico come oggetti del tipo più generale. In questo contesto l'utente è interessato ad utilizzare gli oggetti concreti tramite l'interfaccia della classe base.
    *   **Esempio:** Come menzionato in precedenza, possiamo avere una classe base `Docente` e classi derivate come `Professore_Ordinario`, `Professore_Associato`, `Ricercatore` ecc.. Un utente che non è interessato alle specifiche differenze tra questi tipi di docenti, può trattarli tutti come `Docente` e interagire con essi usando solo l'interfaccia fornita dalla classe base.

*   **Relazione HAS-A (ha un):** Questa relazione si manifesta attraverso il contenimento o l'ereditarietà privata. Indica che una classe "ha un" oggetto di un altro tipo come parte della sua implementazione. L'utente della classe non è interessato a convertire un oggetto della classe che "ha" un altro oggetto in un oggetto del tipo posseduto.
    *   **Esempio:** Un `Automezzo` "ha un" `Motore`. In questo caso, l'utente è interessato ad utilizzare gli automezzi concreti (come `Utilitaria`), e non i motori. Convertire un `Automezzo` in un `Motore` non è una operazione significativa per l'utente, quindi l'ereditarietà pubblica non è appropriata. In questi casi si preferisce l'uso dell'ereditarietà privata o del contenimento. \
        *   **Esempio con contenimento:**
            ```cpp
            class Motore { /* ... */ };
            class Utilitaria {
                Motore motore; // Utilitaria "ha un" Motore
                /* ... */
            };
            ```
        *   **Esempio con ereditarietà privata:**
            ```cpp
            class Motore { /* ... */ };
            class Utilitaria : private Motore {
                /* ... */
            };
            ```
            Tra le due opzioni, il contenimento è spesso preferibile in quanto più intuitivo e flessibile.

### **Esempi concreti per chiarire ulteriormente le idee:**
1.  **Relazione IS-A:** Si consideri un sistema di gestione di figure geometriche.
    *   Si potrebbe avere una classe base `Forma` con metodi virtuali come `calcolaArea()` e `disegna()`.
    *   Classi derivate come `Cerchio`, `Quadrato`, e `Triangolo` ereditano da `Forma` e forniscono implementazioni specifiche per `calcolaArea()` e `disegna()`.
    *   Un utente del sistema può creare un vettore di puntatori a `Forma`, aggiungendo oggetti di tipo `Cerchio`, `Quadrato`, e `Triangolo` e chiamare `calcolaArea()` o `disegna()`: la funzione virtuale corretta viene eseguita in base al tipo dinamico dell'oggetto.
2.  **Relazione HAS-A:** Si consideri un sistema per la gestione di veicoli.
    *   Si potrebbe avere una classe `Veicolo` e una classe `Motore`, `Ruota`, `Telaio`.
    *   La classe `Veicolo` "ha un" `Motore`, "ha un" `Telaio` e "ha"  `Ruota`, implementati come membri della classe.
    *   L'utente del sistema interagisce con gli oggetti `Veicolo`, ma non è interessato a manipolare direttamente i motori, i telai o le ruote che sono dettagli implementativi del veicolo.

## **Metodi Virtuali e Overriding**

Un <font color="da4545">**metodo virtuale**</font> è una funzione membro di una classe base dichiarata con la parola chiave `virtual`. La caratteristica principale di un metodo virtuale è che può essere **ridefinito (override)** nelle classi derivate.

*   Quando una classe derivata ridefinisce un metodo virtuale della classe base con la stessa firma (stesso nome e stessi tipi di parametri), si parla di **overriding**.
*   L'overriding consente alle classi derivate di fornire una implementazione specifica di un comportamento definito nella classe base.
*   Se un metodo non è dichiarato virtual nella classe base, una ridefinizione nelle classi derivate non è un override, ma un **hiding**. In questo caso, il metodo della classe derivata nasconde il metodo con lo stesso nome della classe base.

I metodi virtuali sono fondamentali per il polimorfismo dinamico, perché permettono di chiamare il metodo appropriato a runtime in base al tipo dinamico dell'oggetto, anche quando si utilizza un puntatore o un riferimento alla classe base.

## **Polimorfismo Dinamico**

Il **polimorfismo dinamico** (o polimorfismo a runtime) è la capacità di un oggetto di assumere diverse forme (tipi) durante l'esecuzione di un programma. In C++, il polimorfismo dinamico è reso possibile attraverso l'uso di metodi virtuali e l'ereditarietà.

*   Quando si chiama un metodo virtuale tramite un puntatore o riferimento a una classe base, il compilatore determina a runtime quale implementazione del metodo deve essere eseguita in base al tipo effettivo (dinamico) dell'oggetto puntato o referenziato.
*   Questo significa che un puntatore o un riferimento alla classe base può puntare a oggetti di diverse classi derivate, e la chiamata al metodo virtuale si adatterà al tipo specifico dell'oggetto a cui punta o a cui fa riferimento.
*   Il polimorfismo dinamico consente di scrivere codice più flessibile e riutilizzabile, in quanto permette di trattare oggetti di classi diverse in modo uniforme attraverso l'interfaccia della classe base.

### **La Parola Chiave `override` e l'Overriding di una Funzione Virtuale**

La parola chiave `override` è stata introdotta in C++11 per indicare esplicitamente che una funzione membro di una classe derivata intende sovrascrivere (override) una funzione virtuale della classe base.

*   `override` si usa alla fine della dichiarazione di un metodo.
*   L'uso di `override` è opzionale ma altamente consigliato, in quanto il compilatore verifica che il metodo marcato con `override` esista effettivamente come metodo virtuale nella classe base.
*   Se si usa `override` e il compilatore non trova un metodo virtuale corrispondente nella classe base, genera un errore di compilazione.
*   Questo aiuto è fondamentale per evitare errori di override accidentali o per problemi di refactoring.
*   L'uso di `override` rende il codice più chiaro e meno soggetto ad errori.

#### **Esempio Concreto**

Consideriamo un esempio di un sistema di gestione di stampanti:

```cpp
#include <iostream>
#include <vector>

class Printer {
public:
    virtual void print(const std::string& doc) {
        std::cout << "Stampante generica: " << doc << std::endl;
    }
    virtual ~Printer() {} // Distruttore virtuale
};

class FilePrinter : public Printer {
public:
    void print(const std::string& doc) override {
        std::cout << "Stampante su file: " << doc << std::endl;
    }
};

class NetworkPrinter : public Printer {
public:
    void print(const std::string& doc) override {
        std::cout << "Stampante di rete: " << doc << std::endl;
    }
};

void stampa_tutti(const std::vector<std::string>& docs, Printer* printer) {
    for (const auto& doc : docs) {
        printer->print(doc);
    }
}

int main() {
    std::vector<std::string> documenti = {"Documento 1", "Documento 2", "Documento 3"};

    FilePrinter filePrinter;
    NetworkPrinter networkPrinter;

    stampa_tutti(documenti, &filePrinter);
    stampa_tutti(documenti, &networkPrinter);

    Printer* genericPrinter = new NetworkPrinter();
    stampa_tutti(documenti, genericPrinter);
    delete genericPrinter;


    return 0;
}
```

In questo esempio:

*   `Printer` è una classe base con un metodo virtuale `print()`.
*   `FilePrinter` e `NetworkPrinter` sono classi derivate che ridefiniscono (override) il metodo `print()` con implementazioni specifiche usando la parola chiave `override`.
*   La funzione `stampa_tutti()` accetta un puntatore a `Printer`, quindi è in grado di operare su oggetti di qualsiasi classe derivata da `Printer`.
*   Il polimorfismo dinamico assicura che venga chiamata l'implementazione corretta di `print()` in base al tipo dinamico dell'oggetto `Printer` (filePrinter o networkPrinter), senza che la funzione `stampa_tutti` debba conoscerlo a compile time.
*   Nella funzione main, il puntatore `genericPrinter` punta a un oggetto di tipo `NetworkPrinter`, e la chiamata a `print` eseguirà la versione corretta, quella di `NetworkPrinter`.

Questo esempio dimostra l'importanza dei metodi virtuali, dell'overriding e del polimorfismo dinamico. L'uso di `override` rende più chiara l'intenzione del programmatore e aiuta a prevenire errori.

## **Metodi Virtuali Puri**

Un **metodo virtuale puro** è una funzione membro di una classe base dichiarata con la parola chiave `virtual` seguita da `= 0`. La peculiarità di un metodo virtuale puro è che **non ha implementazione** nella classe base in cui è dichiarato.

*   Un metodo virtuale puro **deve essere ridefinito (override)** in ogni classe derivata concreta. Se una classe derivata non esegue l'override di un metodo virtuale puro, anch'essa sarà considerata una classe astratta.
*   I metodi virtuali puri sono utilizzati per definire **interfacce** che le classi derivate sono tenute a implementare. Essi rappresentano operazioni che tutte le classi derivate devono essere in grado di eseguire, ma la cui implementazione specifica è lasciata alle singole classi.
*   L'uso di metodi virtuali puri consente di creare classi base che fungono da **scheletri o modelli** per altre classi, garantendo che le classi derivate rispettino un certo contratto (interfaccia).
*   Una classe che contiene almeno un metodo virtuale puro è detta **classe astratta**.

## **Classi Astratte**

Una **classe astratta** è una classe che <u>**contiene almeno un metodo virtuale puro**</u>. Le classi astratte sono progettate per essere utilizzate come **classi base** per altre classi.

*   Non è possibile creare oggetti direttamente di una classe astratta. Le classi astratte possono essere usate solamente come classi base per derivare altre classi (astratte o concrete).
*   Le classi astratte servono a definire un'interfaccia, lasciando alle classi derivate il compito di implementare i dettagli specifici.
*   Le classi astratte rappresentano concetti generali e spesso non hanno una implementazione completa di tutti i loro metodi.
*   Le classi astratte sono fondamentali per il polimorfismo dinamico, in quanto permettono di trattare oggetti di diverse classi derivate in modo uniforme attraverso l'interfaccia definita dalla classe astratta.
*   Le classi astratte spesso non hanno un costruttore perché non hanno dati da inizializzare, ma hanno sempre un distruttore virtuale.
*   L'interfaccia di una classe dinamica astratta dovrebbe tipicamente avere una struttura che include metodi virtuali puri e un **distruttore virtuale non puro**.

### **Distruttori delle Classi Astratte**

I **distruttori delle classi astratte** dovrebbero sempre essere dichiarati `virtual` e non dovrebbero mai essere metodi puri. Questo significa che è necessario fornire una implementazione del distruttore, anche se l'implementazione è vuota.

*   La ragione principale per questa regola è legata alla necessità di consentire una corretta distruzione degli oggetti delle classi concrete derivate dalla classe astratta.
*   Quando si distrugge un oggetto di una classe derivata tramite un puntatore alla classe base, il distruttore della classe base deve essere `virtual` per garantire che venga chiamato il distruttore appropriato della classe derivata.
*   Se il distruttore della classe base non fosse `virtual`, verrebbe invocato solo il distruttore della classe base, causando **memory leak** se la classe derivata ha allocato delle risorse, come la memoria, che non verrebbero deallocate.
*   Il distruttore della classe concreta invoca (implicitamente) il distruttore delle sue classi base, quindi il distruttore della classe astratta deve essere definito.
*   **Un distruttore virtuale non puro (ovvero con una implementazione) in una classe astratta garantisce che la catena di distruzione degli oggetti, dal più derivato al più astratto, avvenga correttamente, prevenendo memory leak e altri errori di gestione delle risorse.**

#### **Esempio di Memory Leak Dovuto alla Cattiva Distruzione di una Classe Astratta**

Consideriamo il seguente esempio, che illustra un memory leak causato da un distruttore non virtuale in una classe astratta:

```cpp
#include <iostream>
#include <vector>

class Astratta {
public:
    virtual void print() const = 0;
    ~Astratta() {} // Distruttore errato: non è virtuale.
};

class Concreta : public Astratta {
    std::vector<std::string> vs;
public:
    Concreta() : vs(20, "stringa") {}
    void print() const override {
        for (const auto& s : vs)
            std::cout << s << std::endl;
    }
    // Nota: il distruttore di default sarebbe OK; lo ridefiniamo solo
    // per fargli stampare qualcosa, così che sia evidente il fatto che
    // non è stato invocato.
    ~Concreta() { std::cout << "Distruttore Concreta" << std::endl; }
};

int main() {
    Astratta* a = new Concreta;
    a->print();
    // memory leak: non viene distrutto il vector nella classe concreta.
    delete a; // invoca il distruttore di Astratta (che non è virtuale)
    return 0;
}
```

In questo esempio:

*   `Astratta` è una classe astratta con un metodo virtuale puro `print()` e un distruttore **non virtuale**.
*   `Concreta` è una classe derivata che esegue l'override di `print()` e ha un distruttore che stampa un messaggio quando viene chiamato.
*   Nel `main()`, viene creato un oggetto `Concreta` tramite un puntatore `Astratta*`.
*   Quando si esegue `delete a;`, il distruttore chiamato è quello della classe base `Astratta` e **non quello della classe derivata `Concreta`**, perché il distruttore della classe base non è virtuale.
*   Di conseguenza, il vettore `vs` di `Concreta` non viene deallocato correttamente, causando un **memory leak**. Il messaggio "Distruttore Concreta" non viene stampato.

#### **Per correggere il memory leak, è necessario dichiarare il distruttore della classe base `Astratta` come virtual:**

```cpp
class Astratta {
public:
    virtual void print() const = 0;
    virtual ~Astratta() {} // Distruttore virtuale
};
```
Con questa modifica, quando viene eseguito `delete a;`, verrà chiamato il distruttore di `Concreta`, che deallocherà correttamente il vettore `vs`, evitando il memory leak, e poi verrà chiamato il distruttore di `Astratta`. Il messaggio "Distruttore Concreta" verrà stampato.

In sintesi:

*   I **metodi virtuali puri** sono utilizzati per definire **interfacce** in classi astratte, forzando le classi derivate a fornire un'implementazione specifica.
*   Le **classi astratte** non possono essere istanziate e servono come base per altre classi.
*   I **distruttori delle classi astratte** devono essere sempre **virtual** per prevenire memory leak quando si lavora con puntatori alla classe base.
*   La parola chiave `override` rende esplicito l'overriding di una funzione virtuale e previene errori.
