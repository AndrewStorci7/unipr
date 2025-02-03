# Domande a risposta aperta della prova del 07 Febbraio 2024

### Indice

- [Fornire un esempio di violazione della ODR (One Definition Rule) che sia causato dalla assenza delle guardie contro l'inclusione ripetuta degli header file](#domanda-1)
- [Spiegare brevemente la differenza tra `static_cast`, `const_cast` e `dynamic_cast`, fornendo per ognuno un semplice esempio di utilizzo.](#domanda-2)

## Domanda 1

> **Fornire un esempio di violazione della ODR (One Definition Rule) che sia causato dalla assenza delle guardie contro l'inclusione ripetuta degli header file**

### Soluzione

**file: `header1.h`**
```cpp
#include <iostream>

struct S {
    /* ... */
};
```

**file: `header2.h`**
```cpp
#include "header1.h"
#include "header1.h"

struct D {
    /* ... */
};
```

**file: `main.cpp`**
```cpp
#include "header2.h"

int main() {
    S s;
    D d;
}
```

#### Come risolvere l'errore e seguire a pieno le regole della ODR (One Definition Rule).

**file: `header1.h`**
```cpp
#ifndef HEADER_1_H
#define HEADER_1_H

#include <iostream>

struct S {
    /* ... */
};

#endif // HEADER_1_H
```

**file: `header2.h`**
```cpp
#ifndef HEADER_2_H
#define HEADER_2_H

#include "header1.h"
#include "header1.h"

struct D {
    /* ... */
};

#endif // HEADER_2_H
```

**file: `main.cpp`**
```cpp
#include "header2.h"

int main() {
    S s;
    D d;
}
```

## Domanda 2

> **Spiegare brevemente la differenza tra `static_cast`, `const_cast` e `dynamic_cast`, fornendo per ognuno un semplice esempio di utilizzo.**

### Soluzione

- `static_cast`: lo **static cast** serve per effettuare un casting esplicito tra tipi che non hanno un cast implicito, serve inoltre per poter fare il casting esplcitio tra una classe derivata e una classe base però senza effettuare controlli, come nel caso del `dynamic_cast`.
- `dynamic_cast`: come anticipato sopra, il **dynamic cast** permette di fare il cast implicito tra una classe derivata e una classe base, però effettua il controllo. Nel caso in cui il tipo statico non sia in eredità con il tipo dinamico allora il rirultato del cast è `nullptr` (essendo che il dynamic cast può anche ritornare un riferimento, in quel caso lancia un eccezione di tipo `std::bad_cast`).
- `const_cast`: il **const cast**, invece, va ad eliminare nello scope in cui viene utilizzato il validificatore `const`, rendendolo così modificabile.

- **Esempio di `static_cast`**:
    -   ```cpp
        struct B {};
        struct C : public B {};

        B* b = static_cast<C*>();
        ```
- **Esempio di `dynamic_cast`**:
    -   ```cpp
        struct B {};
        struct C : public B {};
        struct D;

        B* b = dynamic_cast<C*>();  // ok
        B* b2 = dynamic_cast<D*>(); // nullptr
        try {
            B& b2 = dynamic_cast<D&>(); // Lancia eccezione std::bad_cast
        } catch (...) {}
        ```
- **Esempio di `const_cast`**:
    -   ```cpp
        void foo(const int& i) {
            int& z = const_cast<int&>(i);

            z = 56;
        }
        ```
    