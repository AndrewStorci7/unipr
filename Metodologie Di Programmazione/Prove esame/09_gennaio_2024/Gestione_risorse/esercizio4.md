# Esercizio 4 della prova del 09 Gennaio 2024

## Gestione risorse

> **Nell’ipotesi che eventuali errori siano segnalati tramite eccezioni, il seguente codice non ha un comportamento corretto. Individuare almeno un problema, indicando la sequenza di operazioni che porta alla sua occorrenza. Fornire quindi una soluzione basata sull’utilizzo dei blocchi `try/catch`.**
> 
> ```cpp
> void load_and_process(const std::string& conn_params, const std::string& query) {
>     Connection conn; // costr. default: non lancia eccezioni
>     conn.open(conn_params); // acquisizione connessione
>     Results res; // costr. default: non lancia eccezioni
>     res.init(); // acquisizione buffer per risultati
>     conn.execute(query, res); // caricamento dati
>     process(res); // elaborazione dati
>     res.finish(); // rilascio buffer: non lancia eccezioni
>     conn.close(); // rilascio connessione: non lancia eccezioni
> }
> ```

### Soluzione

```cpp
void load_and_process(const std::string& conn_params, const std::string& query) {
    try {
        Connection conn; // costr. default: non lancia eccezioni
        conn.open(conn_params); // acquisizione connessione
        Results res; // costr. default: non lancia eccezioni
        res.init(); // acquisizione buffer per risultati
        conn.execute(query, res); // caricamento dati
        process(res); // elaborazione dati
        res.finish(); // rilascio buffer: non lancia eccezioni
        conn.close(); // rilascio connessione: non lancia eccezioni
    } catch (...) {}
}
```

- Il **primo problema** si può verificare durante la chiamata di `open()` dell'oggetto `conn` di tipo `Connection`, ad esempio se la funzione è ben gestista, in caso di parametri errati per la conessione essa restituirà un eccezione che nel codice originale non viene gestita.

- Il **secondo problema** si può verificare durante la chiamata di `execute()` nel caso in cui ci sia un errore nella query.

### <font color="62fa31">Soluzione di NotebookLM</font>

La tua analisi del problema e la soluzione proposta sono un buon punto di partenza, ma ci sono alcuni aspetti da precisare e migliorare, soprattutto per quanto riguarda la gestione delle eccezioni e la garanzia di rilascio delle risorse. Ecco una risposta più dettagliata e corretta, basata sui principi di gestione delle eccezioni e RAII (Resource Acquisition Is Initialization) discussi nelle fonti:

### **Problemi nel Codice Originale**

*   **Mancanza di gestione delle eccezioni:** Come hai correttamente identificato, le funzioni `conn.open()` e `conn.execute()` potrebbero lanciare eccezioni in caso di errori. Nel codice originale, queste eccezioni non vengono gestite, portando a una potenziale terminazione anomala del programma e, peggio, a una perdita di risorse. Ad esempio, se `conn.open()` lancia un'eccezione, la funzione `conn.close()` non verrà mai chiamata, lasciando potenzialmente una connessione aperta. Allo stesso modo, se `conn.execute()` genera un errore, `res.finish()` non sarà eseguita, causando una perdita del buffer di risultati.
*   **Rilascio delle risorse:** Anche se le funzioni `res.finish()` e `conn.close()` sono dichiarate "non lanciare eccezioni", è fondamentale assicurarsi che vengano sempre chiamate, **indipendentemente dal flusso di esecuzione**, per evitare perdite di risorse.

### **Soluzione Migliorata con `try/catch` e RAII**

Ecco una versione corretta e più robusta della funzione `load_and_process`, che include la gestione delle eccezioni e principi RAII, usando il costrutto try-catch:

```cpp
void load_and_process(const std::string& conn_params, const std::string& query) {
    Connection conn; // costruttore di default: non lancia eccezioni
    Results res; // costruttore di default: non lancia eccezioni
    try {
        conn.open(conn_params); // acquisizione connessione
        res.init(); // acquisizione buffer per risultati
        conn.execute(query, res); // caricamento dati
        process(res); // elaborazione dati
    } catch (...) {
        // Gestione dell'eccezione: rilascio delle risorse prima di rilanciare l'eccezione
        try {
            res.finish(); // Rilascio del buffer (se allocato)
        } catch (...) {
            // in caso di errore in finish() dobbiamo comunque rilasciare conn
        }
        try {
             conn.close(); // Rilascio connessione
        } catch (...) {
            // non possiamo fare altro qui
        }
        throw; // Rilancio dell'eccezione per una gestione a livello superiore
    }
    // Rilascio risorse in caso di successo
    try {
        res.finish();
    } catch (...){
        // possiamo solo ignorare, non possiamo fare altro
    }
    try {
        conn.close();
    } catch (...) {
        // possiamo solo ignorare, non possiamo fare altro
    }
}
```

### **Spiegazione della Soluzione Migliorata**

1.  **Blocco `try`:** Il codice che potrebbe lanciare eccezioni (ovvero `conn.open()`, `res.init()`, `conn.execute()`, e `process(res)`) è racchiuso in un blocco `try`.
2.  **Blocco `catch (...)`:** Se un'eccezione viene lanciata all'interno del blocco `try`, il controllo passa al blocco `catch (...)`. Il `catch(...)` intercetta qualsiasi tipo di eccezione, assicurando che nessuna eccezione non gestita possa propagarsi.
3. **Rilascio delle Risorse nel `catch`:** All'interno del `catch`, le funzioni di rilascio delle risorse (`res.finish()` e `conn.close()`) sono chiamate in blocchi `try-catch` nidificati. Questo assicura che se, per esempio,  `res.finish()` lancia un'eccezione, `conn.close()` venga comunque chiamata. Inoltre se `conn.close()` lancia un'eccezione non si può fare altro che ignorare, visto che non è possibile recuperare la situazione. Questo è essenziale per evitare perdite di risorse.
4.  **Rilancio dell'eccezione (`throw;`):** Dopo aver gestito localmente le risorse (rilasciandole), l'eccezione viene rilanciata usando `throw;`. Questo permette a un gestore di livello superiore (ad esempio, la funzione chiamante di `load_and_process`) di gestire l'errore in modo appropriato. È fondamentale non sopprimere l'eccezione, a meno che non si abbia una strategia specifica per la gestione locale dell'errore.
5.  **Rilascio delle risorse alla fine del blocco:** Anche in caso di successo, il rilascio delle risorse `res.finish()` e `conn.close()` va comunque fatto in blocchi `try/catch`, poiché esse potrebbero fallire per svariate ragioni.

### **Miglioramenti Aggiuntivi (RAII)**

Per una soluzione ancora più robusta e concisa, si potrebbe usare il pattern RAII, creando delle classi "wrapper" che gestiscono automaticamente l'acquisizione e il rilascio delle risorse:

```cpp
#include <string>
#include <iostream> //per cerr
class Connection {
public:
    Connection() { } // Costruttore di default

    void open(const std::string& conn_params) {
        // Simula l'apertura della connessione
        if (conn_params.empty()) {
            throw std::runtime_error("Impossibile aprire connessione: parametri vuoti");
        }
        std::cout << "Connessione aperta con: " << conn_params << std::endl;
    }

    void execute(const std::string& query, class Results& results) {
        // Simula l'esecuzione della query
        if (query.empty()){
            throw std::runtime_error("Impossibile eseguire query: query vuota");
        }
        std::cout << "Eseguo query: " << query << std::endl;
        results.set_data("Dati di test");
    }

    void close() {
        // Simula la chiusura della connessione
        std::cout << "Connessione chiusa" << std::endl;
    }
};

class Results {
    std::string data_;
public:
    Results() {}
    void init() {
        // Simula l'allocazione del buffer
        std::cout << "Buffer risultati allocato" << std::endl;
    }

    void finish() {
        // Simula la deallocazione del buffer
        std::cout << "Buffer risultati rilasciato" << std::endl;
    }
    void set_data(const std::string& data) { data_ = data; }
    std::string get_data() { return data_; }
};


// Wrapper per Connection (RAII)
class ScopedConnection {
public:
    Connection conn; // Membro che contiene l'oggetto Connection
    ScopedConnection(const std::string& conn_params)
    {
        conn.open(conn_params);
    }
    ~ScopedConnection()
    {
        try{
            conn.close();
        } catch (...) {
            //non possiamo fare altro
        }
    }

    Connection& get(){ return conn; }
};

// Wrapper per Results (RAII)
class ScopedResults {
public:
    Results res;
    ScopedResults()
    {
        res.init();
    }
    ~ScopedResults()
    {
        try {
            res.finish();
        } catch (...) {
            // non possiamo fare altro
        }
    }
    Results& get() { return res; }
};

void process(Results& res) {
    std::cout << "Elaborazione dati: " << res.get_data() << std::endl;
}

void load_and_process(const std::string& conn_params, const std::string& query) {
    try{
      ScopedConnection conn{conn_params};
      ScopedResults res;
      conn.get().execute(query, res.get());
      process(res.get());
    } catch (const std::exception& e) {
        std::cerr << "Errore durante load_and_process: " << e.what() << std::endl;
        //gestisco l'eccezione a questo livello
    }
}
```

In questa versione migliorata:

*   `ScopedConnection` e `ScopedResults` sono classi RAII che acquisiscono risorse nei loro costruttori e le rilasciano nei distruttori.
*   L'uso di `try-catch` all'interno del main permette di gestire eventuali errori lanciati in `load_and_process`.
*   Il codice della funzione `load_and_process` diventa più semplice e leggibile, perché la gestione delle risorse è delegata ai wrapper RAII.
*   Anche qualora le funzioni di rilascio (`~ScopedConnection` e `~ScopedResults`) dovessero lanciare eccezioni, queste sono intercettate e gestite, e non sono perciò in grado di propagarsi al di fuori del distruttore.

#### **Punti Chiave**

*   **Gestione delle eccezioni**:  è fondamentale per la robustezza del software.
*   **RAII**:  è una tecnica essenziale per la gestione automatica delle risorse in C++, prevenendo perdite di risorse e semplificando il codice.
*   **Rilascio delle risorse**: le risorse devono sempre essere rilasciate, anche in caso di eccezioni.
*   **Separazione delle responsabilità**: la gestione delle risorse deve essere delegata a classi o funzioni specializzate, rendendo il codice più modulare e leggibile.

In conclusione, la tua soluzione originale aveva individuato correttamente i potenziali problemi, ma la soluzione migliorata, che include la gestione delle eccezioni con `try-catch` e i principi RAII, offre una maggiore robustezza, leggibilità e manutenibilità.
