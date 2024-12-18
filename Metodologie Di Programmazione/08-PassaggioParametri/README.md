# Passaggio per valore VS passaggio per riferimento

> In C++ ci sono due modi per passare i parametri alle funzioni: **passaggio per valore** e **passaggio per riferimento**.

## Passaggio per valore

Nel passaggio per valore, vengono create **copie locali dei valori** delle variabili passate alla funzione. Queste copie vengono utilizzate all'interno della funzione, mentre i valori originali delle variabili rimangono invariati. 

- **Vantaggi**: Protegge i valori originali da modifiche accidentali all'interno della funzione.
- **Svantaggi**: Meno efficiente in termini di memoria, specialmente per dati di grandi dimensioni.

#### Esempio:

```c++
#include <iostream>
using namespace std;

// Funzione per scambiare due interi 
void swap(int a, int b) {
    int temp; 
    temp = a;
    a = b; 
    b = temp;
}

int main() {
    int x, y; 
    cout << "Inserisci il numero x: ";
    cin >> x;
    cout << "Inserisci il numero y: "; 
    cin >> y;
    
    swap(x, y); 
    
    cout << "Dopo lo scambio:" << endl;
    cout << "x: " << x << endl; 
    cout << "y: " << y << endl; 
    return 0;
}
```

In questo esempio, la funzione `swap` non modifica i valori originali di `x` e `y` nel `main` perché le modifiche vengono apportate solo alle copie locali dei parametri.

## Passaggio per riferimento

Nel passaggio per riferimento, viene passato un **riferimento alla variabile originale**, consentendo alla funzione di operare direttamente sui dati originali. Per definire un parametro come passaggio per riferimento, si usa l'operatore `&` prima del nome del parametro.

*   **Vantaggi**: Consente di modificare i valori originali, più efficiente in termini di memoria.
*   **Svantaggi**: Bisogna fare attenzione a non modificare accidentalmente i valori originali se non desiderato.

#### Esempio:

```c++
#include <iostream> 
using namespace std;

// Funzione per scambiare due interi usando il passaggio per riferimento 
void swap(int &a, int &b) { 
    int temp = a; 
    a = b; 
    b = temp; 
}

int main() {
    int x, y;
    cout << "Inserisci il numero x: ";
    cin >> x; 
    cout << "Inserisci il numero y: ";
    cin >> y; 
    
    swap(x, y);
    
    cout << "Dopo lo scambio:" << endl; 
    cout << "x vale: " << x << endl;
    cout << "y vale: " << y << endl;
    return 0;
}
```

In questo esempio, la funzione `swap` modifica i valori originali di `x` e `y` nel `main` perché  opera direttamente sulle variabili originali attraverso i riferimenti.

### Riepilogo:

- **Passaggio per valore**: crea una copia del valore, proteggendo l'originale.
- **Passaggio per riferimento**: consente di modificare il valore originale, offrendo maggiore efficienza.

La scelta tra passaggio per valore e passaggio per riferimento dipende dalle esigenze specifiche del programma.
