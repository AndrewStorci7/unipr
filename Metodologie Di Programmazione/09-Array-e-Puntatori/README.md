# Array e puntatori

> :pushpin: In questo appunto vedremo il legame e la differenza tra array e puntatori

## Introduzione al Type Decay

> Prima di iniziare è corretto spiegare cos'è il ***type decay***

In C++, il **type decay** è un meccanismo che converte implicitamente un tipo in un altro tipo, semplificando la sintassi ma a volte portando a perdite di informazioni. Questo processo si verifica in diverse circostanze, tra cui quando si usano espressioni in cui il tipo originale (`T1`) non è accettato, ma può essere convertito in un tipo accettabile (`T2`).

Un esempio di type decay si verifica quando si passa un array come argomento a una funzione. Per evitare costose copie dell'intero array, il compilatore applica il type decay convertendo il tipo dell'array nel puntatore al suo primo elemento.

## Array e puntatori

Il legame tra array e puntatori è molto forte in C++. L'indicizzazione di un array (`a[b]`) è semplicemente una forma abbreviata di aritmetica dei puntatori, equivalente a `*(a + b)`. 

#### Esempio:

```c++
int a = {1, 2, 3, 4, 5};
int b = 2;

// a[b] è equivalente a *(a + b)
cout << a[b] << endl; // Stampa 3
cout << *(a + b) << endl; // Stampa 3
```

In questo esempio, `a` decade in un puntatore al suo primo elemento. Sommando `b` al puntatore, ci si sposta di `b` posizioni nell'array, ottenendo l'indirizzo del terzo elemento. Infine, dereferenziando l'indirizzo, si ottiene il valore del terzo elemento, ovvero 3.

> #### :bulb: Nota Bene:
> - Questa equivalenza tra array e puntatori funziona solo con gli array, non con altri contenitori come `std::vector<T>`.
> - Sebbene sia possibile scrivere `b[a]` sfruttando la commutatività della somma, è consigliabile utilizzare la notazione standard `a[b]` per chiarezza.

## Aritmetica dei puntatori

L'aritmetica dei puntatori prevede operazioni di somma e sottrazione tra un puntatore e un intero, o tra due puntatori. 

### **Somma di puntatore e intero:**

- Se `ptr` è un puntatore di tipo `T*` e `n` è un intero, `ptr + n` si traduce in un puntatore che punta all'elemento `n` posizioni avanti rispetto a `ptr`. L'indirizzo risultante è calcolato come `ptr + sizeof(T) * n`.

### **Differenza tra due puntatori:**

- Se `ptr1` e `ptr2` sono puntatori dello stesso tipo `T*` che puntano a elementi dello stesso array, `ptr1 - ptr2` restituisce la differenza tra gli indirizzi dei due puntatori divisa per `sizeof(T)`, ovvero il numero di elementi che li separa.

#### **Esempio:**

```c++
int arr = {10, 20, 30, 40, 50};
int *p1 = &arr;
int *p2 = &arr;

// p2 - p1 = 2 (due elementi separano p1 e p2)
cout << p2 - p1 << endl; // Stampa 2
```

L'aritmetica dei puntatori è utile per iterare sugli array. Ad esempio, il seguente codice itera su tutti gli elementi compresi tra `first` (incluso) e `last` (escluso):

```c++
for (int *p = first; p != last; ++p) {
  // elaborazione dell'elemento puntato da p
}
```

Questo idioma di programmazione è stato esteso in C++ al caso degli iteratori su sequenze generiche e sui contenitori della libreria standard.

### Passaggio di array e puntatori come parametri

Quando si passa un array come parametro a una funzione, in realtà si passa un puntatore al primo elemento dell'array. La funzione riceve quindi una copia del puntatore, non una copia dell'intero array.  Di conseguenza, le modifiche apportate agli elementi dell'array all'interno della funzione si rifletteranno sull'array originale.

#### **Esempio:**

```c++
void modifica_array(int *arr, int n) {
  for (int i = 0; i < n; ++i) {
    arr[i] *= 2;
  }
}

int main() {
  int a = {1, 2, 3, 4, 5};
  modifica_array(a, 5);

  // L'array 'a' ora contiene {2, 4, 6, 8, 10}
  for (int i = 0; i < 5; ++i) {
    cout << a[i] << " ";
  }
  cout << endl;
  return 0;
}
```

In questo esempio, la funzione `modifica_array` riceve un puntatore all'array `a`. Le modifiche apportate agli elementi dell'array all'interno della funzione si rifletteranno sull'array originale `a` nel `main`.

È importante ricordare che quando si passa un array a una funzione, si perde l'informazione sulla sua dimensione. Per questo motivo, è buona norma passare anche la dimensione dell'array come parametro separato.

In sintesi, la comprensione del type decay e dell'aritmetica dei puntatori è fondamentale per lavorare con gli array in C++. 
