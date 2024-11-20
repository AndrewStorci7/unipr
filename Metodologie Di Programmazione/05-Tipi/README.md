# Tipi, qualificatori e costanti letterali

## Introduzione

I **tipi** in programmazione rappresentano le categorie che descrivono la natura e le proprietà dei dati utilizzati nei programmi. Un tipo di dato definisce quali valori una variabile può contenere, quali operazioni si possono effettuare su di essa e come il compilatore (o l'interprete) gestisce il dato stesso in termini di memoria e comportamento.

## Tipi integrali

I **tipi integrali** rappresentano tutti i numeri interi e offrono una serie di caratteristiche e proprietà fondamentali. Sono ampiamente utilizzati per numerosi scopi, come il conteggio, l'indicizzazione, l'archiviazione di valori discreti e operazioni aritmetiche.

- **Tipi booleani**: `bool`
- **Tipi carattere**: 
    - **narrow**: `char`, `signed char`, `unsigned char`
    - **wide**: `wchar_t`, `char16_t`, `char32_t`
- **Tipi interi standard con segno**: `signed char`, `short`, `int`, `long`, `long long`
- **Tipi interi standard senza segno**: `unsigned char`, `unsigned short`, `unsigned int`, ...

## Tipi integrali piccoli

I **tipi booleani** sono detti <u>tipi integrali piccoli</u> perché la loro dimensione (`sizeof`) **potrebbe** essere inferiore a quello di un intero `int`

### Promozioni

Le variabili con **tipo integrale piccolo** sono soggette ad un fenomeno particolare chiamato **promozione**. \
La **promozione** è una particolare conversione implicita, ovvero, sono il meccanismo con cui un tipo di dato viene <u>automaticamente convertito</u> in un altro tipo con **maggiore capacità** o **maggiore precisione** durante l'esecuzione di un'operazione. Questo processo consente di ridurre il rischio di perdita di dati o di modificare i valori per garantire un corretto comportamento nelle espressioni.

## Tipi built-in NON integrali

I **tipi built-in non integrali** rappresentano i tipi di dati che non sono direttamente associati a numeri interi e includono tipi per numeri a virgola mobile, caratteri e tipi booleani. Questi tipi sono fondamentali per gestire una varietà di valori e operazioni che vanno al di là degli interi puri, come la rappresentazione di numeri frazionari, il trattamento di caratteri e la logica booleana.

- **Tipi floating point**: `float`, `double`, `long double`
- **Tipo void** (insieme vuoto di valori):
    - Come tipo di ritorno indica che non ritorna **nessun valore**.
    - Usato in un <u>cast esplicito</u> significa che il valore deve essere **scartato**.
- **Tipo `std::nullptr_t`** (dal c++11): tipo puntatore convertibile implicitamente in qualunque altro tipo puntatore; <u>ha un solo valore possibile</u>, la costante letterale `nullptr`, che indica il puntatore nullo (non dereferenziabile)

## Tipi composti

I tipi composti sono tipi creati a partire dai tipi più semplici (integrali, built-in non integrali, ...) per generarne uno personalizzato.

#### Array

Un array è un insieme di dati dello stesso tipo salvati contiguamente in memoria.

```cpp
int array[5] = {1, 2, 3, 4, 5};
```

#### Struct

Le struct sono strutture dati atte a raggruppare tipi di dati diversi (anche simili o uguali) per generarne uno.

```cpp
struct Point {
    int x;
    int y;
};

Point p = {1, 2};
```

#### Classi

**Le classi sono una generalizzazione delle strutture**, introdotte per il supporto alla programmazione orientata agli oggetti. Le classi permettono di definire dati (membri) e funzioni (metodi) insieme. La differenza principale rispetto a una `struct` è che i membri delle classi, per default, sono **privati**, mentre in una `struct` sono **pubblici**.

```cpp
class Rectangle {
private:
    int width, height;

public:
    Rectangle(int w, int h) : width(w), height(h) {}
    int area() { return width * height; }
};
```

#### Enumerazioni

Le **enumerazioni** sono contenitori di costanti, denominati da un identificativo.

```cpp
enum Color { RED, GREEN, BLUE };
Color myColor = RED;
```

#### Puntatori

I **puntatori** sono variabili che memorizzano l'indirizzo di memoria di un'altra variabile. I puntatori servono per gestire la memoria in modo **diretto**.

```cpp
int x = 5;
int* p = &x;  // Puntatore che memorizza l'indirizzo di 'x'
```

#### Riferimenti (references)

I **riferimenti** (`&`) sono alias per altre variabili. A differenza dei puntatori, non possono essere riassegnati e devono essere inizializzati al momento della dichiarazione.

```cpp
int a = 10;
int& ref = a;  // 'ref' è un riferimento ad 'a'
ref = 20;      // Modifica il valore di 'a' a 20
```