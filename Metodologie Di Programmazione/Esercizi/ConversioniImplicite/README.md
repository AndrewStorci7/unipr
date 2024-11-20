# Progettazione di un Tipo di Dato Concreto e Programmazione per Contratto

### Introduzione alla Progettazione di un Tipo di Dato Concreto
La progettazione di un tipo di dato concreto è fondamentale per creare software robusti e manutenibili. Prendiamo come esempio la classe `Razionale`, un tipo di dato che rappresenta numeri razionali (frazioni). Questo esempio è scelto per la sua interfaccia intuitiva e per l'assenza di problematiche legate alla gestione diretta delle risorse. Lo scopo principale non è la perfezione dell'implementazione ma la comprensione di un metodo di sviluppo software.

### Obiettivi della Lezione
- Apprendere il processo di progettazione di classi.
- Comprendere il concetto di **invariante di classe**.
- Imparare ad utilizzare il **Test Driven Design (TDD)**.
- Approfondire la **programmazione per contratto**.

## 1. Strutturazione del Codice
Per lo sviluppo della classe `Razionale`, dividiamo il codice in tre file:
- **Razionale.hh**: interfaccia della classe.
- **Razionale.cc**: implementazione della classe.
- **testRazionale.cc**: codice di test.

La suddivisione del codice permette una gestione modulare del progetto, facilitando il mantenimento e l'aggiornamento del software.

## 2. Test Driven Design (TDD)
Il **Test Driven Design (TDD)** è un approccio alla programmazione in cui i test vengono scritti prima dell'implementazione. I passaggi principali sono:
1. Scrivere il codice di test per le funzionalità desiderate.
2. Implementare il codice per soddisfare i test.
3. Eseguire i test e correggere eventuali errori.

Questo metodo garantisce che il codice sia sempre verificato rispetto ai requisiti e consente di correggere rapidamente errori di logica.

## 3. Invarianti di Classe
Un concetto fondamentale nella progettazione di classi è quello dell'**invariante di classe**, ovvero una proprietà che deve rimanere vera durante tutta la vita dell'oggetto, eccetto durante modifiche temporanee all'interno di un metodo.
- **Check delle Invarianti**: Si realizza un metodo `check_inv()` che verifica l'invariante e utilizza asserzioni per garantirne la correttezza.
- **Gestione delle Invarianti**: Durante l'esecuzione di un metodo, l'invariante può essere temporaneamente violata ma deve essere ripristinata alla fine.

## 4. Programmazione per Contratto
La **programmazione per contratto** definisce un accordo tra lo sviluppatore e l'utilizzatore di una classe. Si basa su:
- **Precondizioni**: Condizioni che devono essere vere prima di chiamare un metodo.
- **Postcondizioni**: Condizioni che devono essere vere dopo l'esecuzione del metodo.
- **Invarianti di Classe**: Proprietà che devono restare vere prima e dopo l'esecuzione dei metodi, ma possono essere temporaneamente violate durante l'esecuzione.

L'idea è di descrivere il contratto con la notazione:  
**precondizioni** :arrow_right: **postcondizioni**  
Se le precondizioni non sono soddisfatte, l'implementatore non è obbligato a garantire la correttezza delle postcondizioni.

## 5. Contratti Narrow e Wide
- **Contratti Narrow**: L'implementatore si assume la responsabilità solo quando le precondizioni sono soddisfatte. L'utilizzatore deve assicurarsi che i dati di input siano validi. Ad esempio, nel caso di una divisione tra numeri razionali, è responsabilità dell'utilizzatore assicurarsi che il denominatore non sia zero.
- **Contratti Wide**: L'implementatore gestisce i casi particolari come input non validi. Ad esempio, se il denominatore è zero, viene lanciata un'eccezione `DivByZero` all'interno del metodo. Questo approccio richiede più codice e può essere meno efficiente, ma è più sicuro per l'utilizzatore.

## 6. Esempi Pratici di Contratti nella Classe `Razionale`
- **Esempio di Contratto Narrow**:
  ```cpp
  Razionale operator /(const Razionale& x, const Razionale& y) {
      assert(x.check_inv() && y.check_inv());
      assert(y != Razionale(0)); // Precondizione: y diverso da zero
      Razionale res = x;
      res /= y;
      assert(res.check_inv());
      return res;
  }
  ```
  In questo caso, l'onere di controllare che `y` non sia zero è a carico dell'utilizzatore.

- **Esempio di Contratto Wide**:
  ```cpp
  Razionale operator /(const Razionale& x, const Razionale& y) {
      assert(x.check_inv() && y.check_inv());
      if (y == Razionale(0))
          throw DivByZero(); // L'implementatore gestisce il caso di `y == 0`.
      Razionale res = x;
      res /= y;
      assert(res.check_inv());
      return res;
  }
  ```
  In questo caso, è l'implementatore a gestire l'errore, garantendo un comportamento definito anche con input non validi.

## 7. Classificazione dei Comportamenti nello Standard C++
Nella programmazione in C++ e nella sua libreria standard, i comportamenti vengono descritti in base a:
- **Specified behavior**: Comportamento descritto dallo standard, a cui tutte le implementazioni devono conformarsi.
- **Implementation-defined behavior**: Comportamento che varia tra implementazioni, ma deve essere documentato (es. dimensione dei tipi interi).
- **Unspecified behavior**: Comportamento che varia tra implementazioni, senza obbligo di documentazione (es. ordine di valutazione degli argomenti di una funzione).
- **Undefined behavior (UB)**: Situazioni non gestite dallo standard, come accedere a memoria non valida. È imprevedibile e può portare a comportamenti errati del programma.

### Conclusioni
La progettazione di tipi di dati concreti e la programmazione per contratto sono pilastri della programmazione orientata agli oggetti in C++. Utilizzare il TDD e seguire rigorosamente le invarianti di classe e i contratti tra implementatore e utilizzatore permette di sviluppare software affidabile e facile da mantenere. Questa lezione fornisce una base solida per affrontare problemi complessi di progettazione e implementazione, ponendo l'accento sulla qualità del processo e della struttura del codice.

---

### Esercizi per Casa
1. Implementare la classe `Razionale` seguendo la metodologia TDD.
2. Definire le invarianti di classe e scrivere il metodo `check_inv()`.
3. Realizzare un esempio di contratto wide per un'operazione tra oggetti `Razionale` e testare il comportamento in caso di input non valido.

### Domande di Verifica
1. Qual è la differenza tra un contratto narrow e un contratto wide?
2. Come si utilizza il metodo `check_inv()` per verificare un'invariante di classe?
3. Perché il TDD può migliorare la qualità del codice?
