# Differenze tra `static_cast`, `dynamic_cast` e `const_cast`

I cast in C++ sono conversioni esplicite di tipo che il programmatore richiede per convertire un'espressione in un tipo potenzialmente diverso. I cast dovrebbero essere usati solo quando necessario, quando la conversione implicita non è consentita dal linguaggio. I cast in C++ si dividono in varie tipologie tra cui `static_cast`, `dynamic_cast` e `const_cast`.

`static_cast` è probabilmente il cast più frequentemente utilizzato. La sintassi è `static_cast<T>(expr)` dove `T` è il tipo in cui convertire l'espressione `expr`.
*   Il `static_cast` esegue conversioni tra tipi correlati, come ad esempio da un puntatore a un altro nella stessa gerarchia di classi, da un tipo integrale a un'enumerazione, o da un tipo floating point a un tipo integrale. Esegue anche conversioni definite da costruttori e operatori di conversione.
*   Il `static_cast` può essere utilizzato per effettuare un downcast in una gerarchia di classi, o per convertire da un tipo numerico ad un tipo enumerazione.
*   Il `static_cast` è utilizzato per le conversioni che il compilatore può verificare a tempo di compilazione.
*   Il `static_cast` non esegue controlli a tempo di esecuzione, quindi è responsabilità del programmatore assicurarsi che la conversione sia valida.

`dynamic_cast` è utilizzato per effettuare conversioni all'interno di una gerarchia di classi legate da ereditarietà, sia singola che multipla. Questo cast si basa sulla RTTI (Run-Time Type Identification) per verificare se la conversione è consentita a tempo di esecuzione.
*   Il `dynamic_cast` può essere utilizzato per effettuare up-cast, down-cast e mixed-cast.
    *   L'up-cast, ovvero la conversione da classe derivata a classe base, non necessita della RTTI, in quanto è una conversione consentita implicitamente.
    *   Il down-cast, ovvero la conversione da classe base a classe derivata, è il caso più frequente di utilizzo di `dynamic_cast`, in quanto si sfrutta la RTTI per verificare che la conversione sia legittima.
    *   Il mixed-cast si verifica in caso di ereditarietà multipla ed è una combinazione di up-cast e down-cast.
*   Il `dynamic_cast` si applica a puntatori e riferimenti, con importanti differenze semantiche. Se il `dynamic_cast` su un puntatore fallisce, restituisce un puntatore nullo; se il `dynamic_cast` su un riferimento fallisce, genera un'eccezione di tipo `std::bad_cast`.
*  Il `dynamic_cast` è usato per una navigazione type-safe all'interno di una gerarchia di classi.

`const_cast` viene utilizzato per rimuovere o aggiungere l'attributo `const` ad un riferimento o puntatore.
*   Il `const_cast` si applica a puntatori o riferimenti ad oggetti qualificati `const` per ottenere un puntatore o riferimento ad un oggetto non qualificato, e quindi modificabile.
*   Usando `const_cast` si potrebbe "rompere" il contratto stipulato con l'utente.
*   L'uso legittimo di `const_cast` include i metodi di una classe che devono modificare la rappresentazione interna di un oggetto, senza però alterarne il significato logico.
*   Alcuni usi di `const_cast` si potrebbero eliminare mediante l'utilizzo del modificatore `mutable` su alcuni dati membro di una classe.

In sintesi:
*   **`static_cast` esegue conversioni tra tipi correlati a tempo di compilazione**.
*   **`dynamic_cast` esegue conversioni tra tipi in gerarchie di classi, con controlli a tempo di esecuzione**.
*   **`const_cast` aggiunge o rimuove l'attributo `const` a puntatori o riferimenti**.
