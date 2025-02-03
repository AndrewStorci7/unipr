# Esercizio 4 della prova del 07 Febbraio 2024

### Gestione Risorse

> **Il codice seguente presenta alcuni problemi relativi alla gestione delle risorse. Evidenziare questi problemi, differenziando tra:**
> - **(a)** errori che si verificano in assenza di eccezioni. 
> - **(b)** errori che si verificano in presenza di eccezioni.
>
> ```c++
> void foo() {
>     A* a1 = new A(1);
>     A* a2 = new A(2);
> 
>     try {
>         job1(a1, a2);
>         job2(a1, new A(3));
>     } catch (...) {
>         delete a2;
>         delete a1;
>     }
> }
> ```
> **Fornire una soluzione basata sull’idioma <u>RAII</u> che si comporti correttamente sia in assenza che in presenza di eccezioni.**

### <font color="#45ae21">Soluzione NotebookLM</font>

Certamente, analizziamo il codice fornito e identifichiamo i problemi relativi alla gestione delle risorse, suddividendoli in base alla presenza o assenza di eccezioni, per poi proporre una soluzione basata su RAII.

### **Analisi del codice `foo()`**

Il codice presenta diversi problemi di gestione della memoria, in particolare riguardo all'uso di `new` e `delete` espliciti:

#### **(a) Errori in assenza di eccezioni:**

*   **Potenziale memory leak:** Se `job1(a1, a2)` o `job2(a1, new A(3))` completano con successo, la memoria allocata con `new A(1)`, `new A(2)` e `new A(3)` non viene deallocata con `delete`. Questo è un classico esempio di *memory leak*, dove la memoria viene allocata ma non rilasciata, portando a un consumo crescente di risorse nel tempo. In particolare, l'oggetto creato con `new A(3)` viene passato a `job2` e non viene gestito nel blocco `try`, e quindi la memoria corrispondente non verrà mai deallocata.

#### **(b) Errori in presenza di eccezioni:**

*   **Memory leak in caso di eccezione:** Se una delle funzioni `job1(a1, a2)` o `job2(a1, new A(3))` lancia un'eccezione, il blocco `catch` viene eseguito. Il blocco `catch` esegue `delete a2;` e `delete a1;`. Questo significa che in caso di eccezione, **solo** gli oggetti puntati da `a2` e `a1` vengono deallocati, mentre la memoria allocata con `new A(3)` (all'interno di `job2`) viene persa e non viene deallocata.
*   **Doppia deallocazione (potenziale):** Se la funzione `job1` lancia un'eccezione **dopo** aver modificato gli oggetti puntati da `a1` o `a2`  in modo da far puntare ad un altro indirizzo di memoria non precedentemente allocato con `new`,  allora il blocco `catch` eseguirà un `delete` su un indirizzo di memoria non valido, causando un *undefined behavior*, e, in particolare, una possibile *double deletion*.

**Soluzione con RAII**

Per risolvere questi problemi, possiamo utilizzare l'idioma **RAII (Resource Acquisition Is Initialization)**. L'idea è di **legare la gestione delle risorse alla durata di un oggetto**. In questo caso, useremo degli *smart pointer*, che gestiscono automaticamente la deallocazione della memoria. In particolare, useremo `std::unique_ptr`, appropriato per risorse che hanno un solo proprietario:

```c++
#include <memory>

void foo() {
    std::unique_ptr<A> a1(new A(1));
    std::unique_ptr<A> a2(new A(2));

    try {
        job1(a1.get(), a2.get()); // Passa i puntatori "grezzi" (raw pointers) alle funzioni job1 e job2.
        job2(a1.get(), std::unique_ptr<A>(new A(3)).get()); // Crea uno smart pointer temporaneo per A(3)
    } catch (...) {
        // Non c'è bisogno di deallocare nulla qui: gli smart pointer gestiscono
        // automaticamente la memoria quando escono dallo scope (anche in caso di eccezione)
    }
}
```

**Spiegazione della soluzione:**

*   **`std::unique_ptr<A> a1(new A(1));`**:  Invece di usare un puntatore `A*`, creiamo un `unique_ptr` che *possiede* la memoria allocata con `new A(1)`. Quando `a1` esce dallo scope (alla fine della funzione `foo`, o prima se un'eccezione viene lanciata e non gestita nel `try`), il distruttore di `unique_ptr` chiamerà automaticamente `delete` sull'oggetto puntato.
*    **`std::unique_ptr<A> a2(new A(2));`**: Stessa logica di `a1`, ma per l'oggetto `A(2)`.
*   **`job1(a1.get(), a2.get());`**: Per passare gli oggetti alle funzioni `job1` e `job2`, che presumibilmente si aspettano dei puntatori "grezzi" (cioè dei `A*`), usiamo il metodo `.get()` di `unique_ptr`, che restituisce il puntatore sottostante. Questo **non trasferisce la proprietà** della risorsa, la proprietà rimane al `unique_ptr`.
*   **`job2(a1.get(), std::unique_ptr<A>(new A(3)).get());`**: In questo caso, creiamo un oggetto `unique_ptr` temporaneo che gestisce la memoria di `new A(3)`. Anche questo `unique_ptr` temporaneo uscirà dallo scope alla fine dell'istruzione di chiamata di `job2`, e la memoria di `A(3)` sarà deallocata automaticamente.
*   **`catch (...) { ... }`**: Il blocco `catch` rimane vuoto. **Non è necessario chiamare `delete`**, perché gli `unique_ptr` si occupano della deallocazione, anche in caso di eccezione. Se un'eccezione viene lanciata dentro il blocco `try`, gli `unique_ptr` vengono distrutti, e rilasciano automaticamente la memoria che gestiscono. Questo garantisce che non ci saranno memory leak o double deletion.

**Vantaggi della soluzione RAII:**

*   **Gestione automatica della memoria:** Gli oggetti vengono automaticamente deallocati quando non più necessari, evitando *memory leak*.
*   **Eccezione-safety:** La deallocazione è garantita anche in caso di eccezioni, evitando *resource leak*.
*   **Codice più pulito e leggibile:** Si elimina la necessità di chiamare `delete` esplicitamente, semplificando il codice e riducendo la probabilità di errori.
*   **Maggiore sicurezza:** RAII riduce il rischio di  *double deletion* o di chiamare `delete` su puntatori non validi.

In sintesi, la soluzione basata su `unique_ptr` e RAII garantisce una gestione corretta della memoria sia in assenza che in presenza di eccezioni, rendendo il codice più robusto e meno soggetto a errori.
