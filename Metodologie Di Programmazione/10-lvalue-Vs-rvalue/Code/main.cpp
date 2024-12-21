/**
 * Individuare lvalue e rvalue
 * per ogni espressione
 **/

#include <iostream>

int main() {

    /// Per ogni espressione, identifica se è un lvalue o un rvalue:
    int a = 5;  // a è lvalue; 5 è rvalue
    a;          // a è lvalue
    10;         // 10 è rvalue
    a + 2;      // a + 2 è xvalue
    a = 20;     // a è lvalue; 20 è rvalue

    /// Scrivi codice in cui assegni un valore a una variabile:
    int x;
    // DOMANDA: E' possibile assegnare a x un rvalue ?
    // RISPOSTA: Si
    // DOMANDA: E' possibile assegnare a x un lvalue ?
    // RISPOSTA: No



    return 0;
}
