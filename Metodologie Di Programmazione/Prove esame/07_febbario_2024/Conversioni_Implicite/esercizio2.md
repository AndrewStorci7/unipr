# Esercizio 2 prova del 07 Febbraio 2024

### Conversioni implicite

> **Scrivere la dichiarazione di una funzione avente 4 parametri e una chiamata della funzione stessa che comporti le seguenti conversioni implicite sui 4 argomenti (nell’ordine): conversione di qualificazione const, promozione, conversione standard, conversione definita dall’utente.**

#### Soluzione

```c++
// Dichiarazione
void foo(const int&, int, double, std::string);

// Chiamata alla funzione foo()
int a = 10;

foo(a, 'a', a, "ciao");
```
