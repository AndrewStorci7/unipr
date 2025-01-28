# Funzioni Virtual

Le <font color="#22cc87">funzioni **`virtual`**</font> in C++ sono un meccanismo che permette il **collegamento dinamico** (o *dynamic binding*) delle chiamate a funzione, ovvero la risoluzione della funzione corretta da eseguire avviene a tempo di esecuzione, e non a tempo di compilazione. Questo è fondamentale per implementare il **polimorfismo**, uno dei pilastri della programmazione orientata agli oggetti.

Ecco una spiegazione più dettagliata:

*   **Cos'è una funzione virtuale?** Una funzione membro di una classe dichiarata con la parola chiave `virtual`. Questa dichiarazione dice al compilatore che la scelta della funzione specifica da eseguire deve essere fatta a runtime in base al **tipo effettivo dell'oggetto**, e non al tipo del riferimento o del puntatore usato per chiamarla.

*   **A cosa servono?**
    *   **Polimorfismo:** Le funzioni virtual permettono di trattare oggetti di classi derivate come oggetti della classe base, pur mantenendo il comportamento specifico di ogni classe derivata. Questo è cruciale per scrivere codice flessibile e riutilizzabile.
    *   **Interfacce astratte:** Le funzioni virtual sono essenziali nelle classi astratte, che definiscono un'interfaccia per le classi derivate. Una classe che dichiara o eredita una funzione virtuale è definita classe polimorfa. In una classe astratta, le funzioni virtual possono essere dichiarate come **pure virtual** (`= 0`), il che obbliga le classi derivate a fornire una propria implementazione.
    *   **Override:** Una funzione virtuale può essere ridefinita (o *overridden*) nelle classi derivate. Se una funzione con la stessa firma (nome e parametri) di una funzione virtuale della classe base viene dichiarata in una classe derivata, essa **sovrascrive** la funzione virtuale della classe base.
    *   **Distruttori virtuali:** I distruttori di una classe base devono essere dichiarati come virtuali per garantire che il distruttore appropriato della classe derivata venga chiamato quando un oggetto viene eliminato tramite un puntatore alla classe base.

*   **Perché è importante conoscerle?**
    *   **Flessibilità:** Le funzioni virtual rendono il codice più adattabile ai cambiamenti, permettendo di estendere il comportamento di un programma senza modificare il codice esistente.
    *   **Riutilizzabilità:** Permettono di scrivere codice generico che opera su una varietà di oggetti tramite un'interfaccia comune, senza conoscere il tipo concreto degli oggetti stessi.
    *   **Progettazione orientata agli oggetti:** Sono un concetto fondamentale per lo sviluppo di applicazioni orientate agli oggetti, consentendo l'implementazione di comportamenti specifici per le classi derivate in modo polimorfico.
    *   **Efficienza:** Il meccanismo di chiamata delle funzioni virtuali (tramite *virtual function table* o *vtbl*) è efficiente e la piccola spesa di memoria e di tempo di esecuzione è ampiamente giustificata dalla flessibilità e riusabilità che offrono. Il *vtbl* è una tabella di puntatori a funzioni virtuali, specifica per ogni classe polimorfa.

*   **Esempio:** Si consideri una classe `Shape` con una funzione virtuale `draw()`. Le classi `Circle` e `Rectangle` possono ereditare da `Shape` e fornire una propria implementazione di `draw()`. Una funzione che opera su un `Shape*` può chiamare `draw()` e l'output sarà diverso a seconda che il puntatore punti a un `Circle` o a un `Rectangle`.

*   **Importante:** Se una funzione membro non è dichiarata virtual nella classe base, le classi derivate non possono ridefinirla in modo polimorfico e la risoluzione della funzione avviene staticamente a tempo di compilazione.

In sintesi, le funzioni virtual in C++ sono uno strumento potente e essenziale per implementare il polimorfismo e la programmazione orientata agli oggetti, garantendo flessibilità, riutilizzabilità e facilità di manutenzione del codice. Conoscere il loro funzionamento è fondamentale per lo sviluppo di applicazioni complesse e ben strutturate.
