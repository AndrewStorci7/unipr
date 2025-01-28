# Esercizio convesrioen implicita

### Prova del 10 Settembre 2024

> Le conversioni implicite del C++ sono distinte nelle seguenti categorie: **corrispondenze esatte (E)**, **promozioni (P)**, **conversioni standard (S)**, **conversioni definite dall’utente (U)**. Assumendo che la variabile `i` abbia tipo `int`, per ognuno degli accoppiamenti argomento/parametro definiti di seguito, indicare (se esiste) la categoria della corrisponente conversione implicita.

| Indice | Argomento | Tipo parametro formale | Soluzione |
|--------|-----------|------------------------|-----------|
| (1)    | `i`       | `double`               | **S**     |
| (2)    | `i`       | `const int&`           | **E**     |
| (3)    | `0.2F`    | `double`               | **P**     |
| (4)    | "stringa" | `std::string`          | **U**     |

## Esercizio fatto da NotebookLM

Le conversioni implicite del C++ sono distinte nelle seguenti categorie: **corrispondenze esatte (E)**, **promozioni (P)**, **conversioni standard (S)**, **conversioni definite dall'utente (U)**. Assumendo che le variabili e i valori letterali seguenti abbiano i tipi indicati, per ognuno degli accoppiamenti argomento/parametro definiti nella tabella, indicare (se esiste) la categoria della corrispondente conversione implicita.

*   `i` è una variabile di tipo `int`
*   `f` è una variabile di tipo `float`
*   `d` è una variabile di tipo `double`
*   `c` è una variabile di tipo `char`
*   `s` è una variabile di tipo `std::string`
*   `10` è una costante letterale di tipo `int`
*   `10.0` è una costante letterale di tipo `double`
*   `'A'` è una costante letterale di tipo `char`
*   `"ciao"` è una costante letterale di tipo `const char*`
*   `nullptr` è un valore letterale di tipo `std::nullptr_t`

| Indice | Argomento | Tipo parametro formale | Soluzione |
|--------|-----------|------------------------|-----------|
| (1)    | `i`       | `float`                | **S**     |
| (2)    | `f`       | `double`               | **P**     |
| (3)    | `d`       | `int`                  | **S**     |
| (4)    | `c`       | `int`                  | **P**     |
| (5)    | `i`       | `const int&`           | **E**     |
| (6)    | `10`      | `double`               | **S**     |
| (7)    | `10.0`    | `int`                  | **S**     |
| (8)    | `'A'`     | `int`                  | **P**     |
| (9)    | `"ciao"`  | `std::string`          | **U**     |
| (10)   | `s`       | `const std::string&`   | **E**     |
| (11)   | `nullptr` | `int*`                 | **S**     |
| (12)   | `nullptr` | `void*`                | **S**     |
| (13)   | `i`       | `long long`            | **S**     |
| (14)   | `f`       | `const float&`         | **E**     |

**Note:**

*   Una conversione da un tipo `T` a `const T&` è una corrispondenza esatta **(E)**.
*   Le conversioni da tipi interi a tipi floating point (e viceversa) sono conversioni standard **(S)**.
*   Le conversioni da tipi floating point di minore precisione a maggiore precisione (`float` a `double`) sono promozioni **(P)**.
*   Le conversioni da `const char*` a `std::string` sono conversioni definite dall'utente **(U)**.
*   Le conversioni da `nullptr_t` a un tipo puntatore sono conversioni standard **(S)**.

