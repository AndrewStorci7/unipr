# Esercizio 5 della prova del 09 Gennaio 2024

## Domande a risposta aperta

- [**Fornire un esempio di violazione della ODR (One Definiton Rule) che non può essere rilevato nella fase di compilazione in senso stretto.**](#domanda-1)
- [**Spiegare cosa si intende quando si dice che una porzione di codice è neutrale rispetto alle eccezioni. Quali sono i casi in cui non si deve essere neutrali ?**](#domanda-2)
- [**Spiegare brevemente perché, nelle interfacce basate su polimorfismo dinamico, è opportuno definire i distruttori virtuali non puri.**](#domanda-3)
- [**Fornire un semplice esempio in cui l’uso dello specificatore override causa un errore a tempo di compilazione.**](#domanda-4)
- [**Aiutandosi con un semplice esempio, spiegare in cosa consiste il principio di separazione delle interfacce (ISP).**](#domanda-5)

## Domanda 1

> **Fornire un esempio di violazione della ODR (One Definiton Rule) che non può essere rilevato nella fase di compilazione in senso stretto.**

#### File: `header1.h`
```cpp
struct S {
    int i;
    S() = default;
    S(int& i_) : i(i_) {};
}
```

#### File: `header2.h`
```cpp
struct S {
    double d;
    std::string s;
    S() = default;
    S(double& d_, std::string& s_) : d(d_), s(s_) {};
}
```

#### File: `main.cpp`
```cpp
#include "header1.h"
#include "header2.h"

int main() {
    S s;
}
```

### Soluzione di NotebookLM

#### **Analisi della Violazione ODR**

Il problema principale nel tuo esempio è che **la struttura `S` è definita in modo diverso in `header1.h` e `header2.h`**, e queste definizioni conflittuali vengono incluse nello stesso file di traduzione `main.cpp`. Questo costituisce una **violazione della ODR**. Più precisamente:

*   In `header1.h`, `S` è una struct con un membro intero `i`, un costruttore di default e un costruttore che prende un riferimento ad un intero.
*   In `header2.h`, `S` è una struct con un membro `double` chiamato `d` e un membro `string` chiamato `s`, un costruttore di default e un costruttore che prende un riferimento a un double e un riferimento a una stringa.
*   Nel `main.cpp`, includendo entrambi gli header, si crea una situazione ambigua dove il compilatore non sa quale delle due definizioni di `S` usare.

Questo tipo di violazione della ODR **non è rilevabile durante la compilazione "in senso stretto"**, ovvero quando il compilatore analizza ogni file sorgente (translation unit) separatamente. Il compilatore, infatti, non ha conoscenza delle definizioni di altri file, a meno che non siano inclusi tramite `#include`. La violazione si manifesta solo **durante la fase di linking**, quando il linker cerca di combinare le diverse unità di traduzione in un unico eseguibile. Poichè, però, entrambe le definizioni di `S` sono incluse nello stesso `main.cpp`, questo errore non è rilevabile dal linker, ed è uno dei casi per i quali la ODR non garantisce rilevazione dell'errore.

**Motivo per cui non viene rilevato in fase di compilazione**

Il compilatore tratta ogni file `.cpp` (o translation unit) in isolamento. Quando compila `main.cpp`:

1.  Il pre-processore include `header1.h` e `header2.h` nel file `main.cpp`.
2.  Il compilatore non è in grado di determinare quale definizione di S sia corretta.
3.  Il compilatore genera il codice oggetto corrispondente, presumibilmente con una definizione ambigua di S.
4.  L'errore si rivela **nel momento della compilazione** di `main.cpp`, o quando si utilizza la struct `S` (e.g., la definizione di s nel `main()` `S s;`).

**Correzione dell'Esempio**

La correzione più semplice è **evitare definizioni multiple della stessa entità** (in questo caso `S`) in diversi header che possono essere inclusi nello stesso file sorgente. La soluzione più corretta sarebbe quella di:
*   Definire una sola struct `S` (per esempio in `header1.h`).
*   Includere tale definizione in tutti i file che la necessitano.

Ecco un esempio di come si potrebbe correggere, creando un singolo header `S.h`:

#### File: `S.h`
```cpp
#include <string>

struct S {
    int i;
    double d;
    std::string s;
    S() = default;
    S(int& i_) : i(i_), d(0.0), s("") {};
    S(double& d_, std::string& s_) : i(0), d(d_), s(s_) {};
};
```

#### File: `main.cpp`
```cpp
#include "S.h"

int main() {
    S s;
    int a = 1;
    double b = 2.2;
    std::string c = "test";
    S s1 {a};
    S s2 {b,c};
}
```
In questo modo non si viola la ODR.

**Punti chiave sulla ODR**

*   **Definizione Unica:** La ODR impone che ci sia una sola definizione per ogni classe, struct, template, enumerazione, etc. in un programma.
*   **Inclusione tramite Header:** La ODR permette che la definizione di una classe venga inclusa in diverse unità di traduzione tramite `#include`, **a patto che la definizione sia identica in tutte le unità**.
*   **Violazione tramite Header Multipli:** Includere lo stesso header in più file è lecito, ma includere definizioni diverse della stessa entità tramite header diversi nello stesso file, è una violazione della ODR.
*   **Problemi di Linkage:** La ODR riguarda anche le variabili globali e le funzioni non-inline, le quali devono essere definite esattamente una volta nel programma.
*   **Rilevabilità:** Alcune violazioni della ODR sono rilevabili in fase di compilazione, altre (come l'esempio presentato) solo in fase di linking o addirittura a runtime.

**Perché questo tipo di violazione è pericoloso?**
Questo tipo di violazione della ODR è particolarmente insidioso perché:

*   **Non sempre produce errori evidenti:** Il codice potrebbe compilare e linkare senza errori, ma il comportamento a runtime potrebbe essere imprevedibile.
*   **Difficile da debuggare:**  Individuare questo tipo di errori è difficile, soprattutto in progetti grandi con molti file header.
*   **Problemi di Manutenibilità:**  Modificare una delle due definizioni di `S` potrebbe introdurre bug difficili da individuare.

## Domanda 2

> **Spiegare cosa si intende quando si dice che una porzione di codice è neutrale rispetto alle eccezioni. Quali sono i casi in cui non si deve essere neutrali ?**

Una porzione di codice si dice **neutrale rispetto alle eccezioni** quando non gestisce direttamente le eccezioni, ma le propaga al chiamante. In altre parole, il codice non cattura le eccezioni (con `try` e `catch`), ma lascia che esse si propaghino verso l'alto nella pila delle chiamate. Questo comportamento è tipico del codice di libreria, che non dovrebbe prendere decisioni sul modo in cui le eccezioni vengono gestite dall'applicazione che utilizza la libreria.

Ecco alcuni punti chiave per capire meglio il concetto:

*   **Propagazione delle Eccezioni:** Il codice neutrale rispetto alle eccezioni semplicemente permette che le eccezioni lanciate al suo interno si propaghino verso il codice chiamante, senza tentare di gestirle direttamente.
*   **Nessun `try-catch`:** Tipicamente, una funzione o una porzione di codice neutrale rispetto alle eccezioni non contiene blocchi `try-catch`. Se un'eccezione viene lanciata, essa non viene intercettata localmente.
*   **Flessibilità per il Chiamante:** La neutralità rispetto alle eccezioni offre al chiamante la flessibilità di gestire le eccezioni nel modo più appropriato al contesto della sua applicazione. Il chiamante potrebbe scegliere di loggare l'errore, mostrare un messaggio all'utente, o tentare di recuperare in qualche modo.
*   **Codice di Libreria:** Le librerie dovrebbero essere generalmente neutrali rispetto alle eccezioni, in modo da non imporre una particolare politica di gestione degli errori all'utente della libreria.

**Casi in cui non si deve essere neutrali rispetto alle eccezioni**

Ci sono situazioni in cui la neutralità rispetto alle eccezioni non è appropriata, e il codice deve gestire le eccezioni in modo specifico. Questi casi includono:

*   **Gestione di Risorse:** Se una funzione alloca risorse (come memoria, file, o connessioni di rete), deve assicurarsi che queste risorse vengano rilasciate anche in caso di eccezione. Questo si ottiene tramite il pattern RAII (Resource Acquisition Is Initialization), in cui le risorse vengono gestite tramite oggetti la cui distruzione garantisce il rilascio della risorsa. In questo caso la gestione dell'eccezione è localizzata nel distruttore della risorsa.
*   **Punti di Recupero:** Se una funzione si trova in un punto in cui è possibile recuperare da un errore (ad esempio, riprovando un'operazione che ha fallito), dovrebbe catturare e gestire l'eccezione.
*   **Interfacce Utente:** Le interfacce utente dovrebbero gestire le eccezioni per fornire all'utente un'esperienza più amichevole e per evitare crash inaspettati. La gestione, in questo caso, consiste nel mostrare un messaggio di errore significativo all'utente.
*   **Transazioni:** Se il codice esegue operazioni che devono essere trattate come una transazione (tutte le operazioni devono completare con successo, o nessuna deve essere eseguita), è necessario un meccanismo di gestione delle eccezioni che garantisca l'atomicità della transazione.
*   **Funzioni `noexcept`:** Se una funzione è marcata con `noexcept`, non deve lanciare eccezioni, in tal caso il comportamento in caso di eccezione non è ben definito.  Quindi una funzione dichiarata `noexcept` non può essere neutrale rispetto alle eccezioni, nel senso che deve far di tutto per evitare di far propagare eccezioni.

**Perché la neutralità è importante?**

*   **Separazione delle Responsabilità:** Consente di separare la logica di business dalla logica di gestione degli errori, rendendo il codice più modulare.
*   **Riusabilità del Codice:** Il codice neutrale rispetto alle eccezioni è più riutilizzabile perché non è vincolato a una specifica politica di gestione degli errori.
*   **Maggiore Flessibilità:**  Offre al chiamante un maggiore controllo su come vengono gestiti gli errori.
*   **Prevenzione di "Blabbering":** Evita che le librerie producano messaggi di errore non contestualizzati, ma delega al chiamante la creazione di messaggi appropriati al contesto.

In sintesi, la neutralità rispetto alle eccezioni è un principio di progettazione fondamentale per il codice di libreria e per tutte quelle funzioni che non hanno una specifica competenza su come un errore debba essere gestito. La gestione locale delle eccezioni è essenziale quando si gestiscono risorse, si implementano meccanismi di recupero da errori, o si implementano interfacce con l'utente. La decisione se essere neutrali o meno deve essere presa caso per caso e deve considerare la responsabilità specifica della porzione di codice.

## Domanda 3

> **Spiegare brevemente perché, nelle interfacce basate su polimorfismo dinamico, è opportuno definire i distruttori virtuali non puri.**

Nelle interfacce basate sul polimorfismo dinamico, è opportuno definire i **distruttori virtuali non puri** per garantire una **corretta deallocazione della memoria** e **prevenire comportamenti indefiniti** quando si lavora con puntatori a oggetti di classi derivate.

Ecco una spiegazione più dettagliata:

*   **Polimorfismo e puntatori alla classe base:** Quando si utilizza il polimorfismo dinamico, è comune manipolare oggetti di classi derivate tramite puntatori o riferimenti alla classe base. Questo permette di trattare in modo uniforme oggetti di tipo diverso, a patto che condividano un'interfaccia comune definita nella classe base.
*   **Distruttori e gerarchie di classi:** Se la classe base ha un distruttore non virtuale, e si dealloca un oggetto di una classe derivata tramite un puntatore alla classe base, **verrà invocato il distruttore della classe base, ma non quello della classe derivata**. Questo può portare a una **deallocazione parziale** dell'oggetto e a **perdite di memoria** se la classe derivata ha acquisito risorse che devono essere rilasciate nel suo distruttore.
*   **Distruttori virtuali:** Dichiarando il distruttore della classe base come `virtual`, si garantisce che, quando si dealloca un oggetto tramite un puntatore alla classe base, **venga invocato il distruttore corretto per il tipo effettivo dell'oggetto**, ovvero il distruttore della classe più derivata.
*   **Distruttori virtuali non puri:** Un distruttore virtuale non puro (ovvero, con un'implementazione) permette alle classi derivate di sovrascrivere il comportamento di distruzione, ma consente anche di avere un comportamento di distruzione di default per le classi astratte (che altrimenti dovrebbero essere dichiarate con un distruttore virtuale puro). Questo è importante per la corretta gestione delle risorse nel caso in cui si utilizzi l'ereditarietà di interfaccia, come nel caso di classi astratte.

**Esempio:**
Considera una gerarchia di classi con una classe base `Shape` e una classe derivata `Circle`:

```cpp
class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() {} // Distruttore virtuale non puro
};

class Circle : public Shape {
    int* radius;
public:
    Circle(int r) : radius(new int(r)) {}
    void draw() override { /* ... */ }
    ~Circle() override { delete radius; }
};
```

Se non ci fosse il distruttore virtuale in `Shape`, e deallocassi un `Circle` con un puntatore `Shape*`, il distruttore di `Circle` non verrebbe mai chiamato e si verificherebbe una perdita di memoria. Grazie al distruttore virtuale non puro,  il distruttore della classe derivata `Circle` viene chiamato tramite il meccanismo di *late binding*, garantendo così il corretto rilascio delle risorse acquisite dalla classe derivata.

**In sintesi:**

*   L'uso di distruttori virtuali non puri nelle classi base di gerarchie polimorfiche è fondamentale per una corretta gestione della memoria e delle risorse.
*   Garantiscono che il distruttore appropriato per il tipo effettivo dell'oggetto venga invocato anche quando si manipolano oggetti tramite puntatori alla classe base.
*   Previene perdite di memoria e comportamenti indefiniti che potrebbero manifestarsi se il distruttore corretto non venisse chiamato.
*   Anche le classi astratte hanno bisogno di un distruttore virtuale non puro per garantire una corretta deallocazione delle risorse che potrebbero essere state acquisite da classi derivate..

Definire un distruttore virtuale non puro nella classe base di una gerarchia di classi polimorfiche è una buona pratica di programmazione per evitare problemi legati alla gestione della memoria e a comportamenti indefiniti durante l'esecuzione del programma.

## Domanda 4

> **Fornire un semplice esempio in cui l’uso dello specificatore override causa un errore a tempo di compilazione.**

```cpp
class A {
    private:
        int a;

    public:
        void set(const int& i);
        virtual int calc(const int& i);
        void print(std::ostream& os) const; 
}

class B : public A {
    private:
        int b;

    public:
        int calc(const int& i) override;
        void print(std::ostream& os) const override;
}
```

Nella sovraccaricamento della funzione `print()` il compilatore genera un errore dovuto dall'utilizzo della parola chiave **override**. \
Infatti in questo caso ha il compito di segnalare quando una funzione non virtual viene ridefinita nella classe derivata.

## Domanda 5

> **Aiutandosi con un semplice esempio, spiegare in cosa consiste il principio di separazione delle interfacce (ISP).**

Il principio di separazione delle interfacce (ISP), parte dei principi SOLID della programmazione orientata agli oggetti, afferma che **un client non dovrebbe essere forzato a dipendere da interfacce che non usa**. In altre parole, è meglio avere interfacce piccole e specifiche per ruoli diversi, piuttosto che una singola interfaccia grande che copre troppe funzionalità.

Per capire meglio, consideriamo un esempio pratico che utilizza una versione semplificata del concetto di "forma" descritto nei sorgenti:

**Esempio senza ISP (violazione del principio):**

Immagina di avere una singola interfaccia `Forma` che definisce tutte le operazioni possibili che si possono fare con una forma geometrica:

```cpp
class Forma {
public:
    virtual void draw() = 0;       // Disegna la forma
    virtual double getArea() = 0;  // Calcola l'area della forma
    virtual void resize(double factor) = 0; // Ridimensiona la forma
};
```

Ora, considera due classi che implementano questa interfaccia: `Cerchio` e `Quadrato`. La classe `Cerchio` ha senso implementare le funzioni `draw()`, `getArea()` e `resize()`. Tuttavia, se avessi una classe `Testo`, quest'ultima potrebbe implementare `draw()`, ma non avrebbe senso implementare `getArea()` e `resize()`, forzandola ad implementare metodi che non le servono.

Questa è una violazione dell'ISP, perché la classe `Testo` è costretta a dipendere da metodi che non usa. Questo può portare a codice più complesso, difficile da mantenere e soggetto ad errori.

**Esempio con ISP (applicazione del principio):**

Per risolvere il problema, applichiamo ISP dividendo l'interfaccia `Forma` in interfacce più piccole e specifiche:

```cpp
// Interfaccia per oggetti disegnabili
class Disegnabile {
public:
    virtual void draw() = 0;
};

// Interfaccia per oggetti che hanno un'area
class CalcolabileArea {
public:
    virtual double getArea() = 0;
};

// Interfaccia per oggetti ridimensionabili
class Ridimensionabile {
public:
   virtual void resize(double factor) = 0;
};
```

Ora, le nostre classi possono implementare solo le interfacce di cui hanno bisogno:

```cpp
#include <cmath>
// Cerchio implementa le interfacce Disegnabile, CalcolabileArea e Ridimensionabile
class Cerchio : public Disegnabile, public CalcolabileArea, public Ridimensionabile {
private:
    double raggio;
public:
    Cerchio(double r) : raggio(r) {}
    void draw() override { /* ... */ }
    double getArea() override { return M_PI * raggio * raggio; }
    void resize(double factor) override { raggio *= factor; }
};


// Quadrato implementa le interfacce Disegnabile, CalcolabileArea e Ridimensionabile
class Quadrato : public Disegnabile, public CalcolabileArea, public Ridimensionabile {
private:
    double lato;
public:
    Quadrato(double l) : lato(l) {}
    void draw() override { /* ... */ }
    double getArea() override { return lato * lato; }
    void resize(double factor) override { lato *= factor; }
};


// Testo implementa solo l'interfaccia Disegnabile
class Testo : public Disegnabile {
private:
    std::string testo;
public:
    Testo(std::string t) : testo(t) {}
    void draw() override { /* ... */ }
};
```

In questo caso, la classe `Testo` implementa solo l'interfaccia `Disegnabile`, mentre le classi `Cerchio` e `Quadrato` implementano tutte e tre le interfacce. Nessuna classe è costretta a dipendere da interfacce che non usa.

**Vantaggi dell'ISP:**

*   **Flessibilità:** Le classi dipendono solo dalle interfacce che usano effettivamente, rendendo il sistema più flessibile ai cambiamenti.
*   **Manutenibilità:** Le modifiche ad una interfaccia hanno meno impatto sul resto del sistema, perché le classi sono meno accoppiate.
*   **Riutilizzabilità:** Le interfacce sono più specifiche e riutilizzabili in diversi contesti.
*   **Minore complessità:** Le classi sono più semplici e concentrate su uno specifico insieme di operazioni.
*   **Separazione delle responsabilità:** L'uso delle interfacce rende più esplicito il modo in cui i vari componenti interagiscono tra di loro, separando le logiche di business dalle dipendenze di interfaccia.

**In sintesi**, il principio di separazione delle interfacce promuove la creazione di interfacce più piccole e specifiche, riducendo l'accoppiamento tra le classi e rendendo il codice più flessibile, manutenibile e riutilizzabile. L'esempio delle forme illustra come la scomposizione di un'interfaccia grande e generica in più interfacce specifiche può migliorare la struttura del codice, evitando di imporre dipendenze inutili.

