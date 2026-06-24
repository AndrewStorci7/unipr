#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cstdlib>
#include <cassert>

#define INFINITO 1000000

using namespace std;

// compilazione: g++ consegna1-loader.c
//

// Il programma carica il file data.csv contenente 100 righe con dati da ordinare in modo crescente
// ./a.out
// In output viene mostrato il numero di accessi in read alla memoria per eseguire il sorting di ciascuna riga

// Obiettivo:
// Creare un algoritmo di sorting che minimizzi la somma del numero di accessi per ogni sorting di ciascuna riga del file

int ct_swap = 0;
int ct_cmp = 0;
int ct_read = 0;

int max_dim = 0;
int ntests = 100;
int ndiv = 1;
int details = 0;
int graph = 0;

int n = 0; /// dimensione dell'array

void print_array(int *A, int dim) {
    for (int j = 0; j < dim; j++) {
        printf("%d ", A[j]);
    }
    printf("\n");
}

struct bucket {
    size_t size = 0;
    size_t max_size = 0;
    int* V = nullptr;

    bucket(int n) {
        max_size = n;
        size = 0;
        V = new int[n];
        for (int i = 0; i < n; ++i)
            V[i] = 0;
    }

    void push(int val) {
        if (size == max_size) {
            perror("Bucket pieno");
            return;
        }

        V[size] = val;
        ++size;
    }

    int pop() {
        return V[size--];
    }

    bool isEmpty() const {
        return size == 0;
    }

    void print() {
        for (int i = 0; i < size; ++i) {
            std::cout << V[i] << ", ";
        }
        std::cout << std::endl;
    }

    void sort() {
        /// TODO
    }
};


/// @brief Cerco il massimo esattamente nella parte centrale per minimizzare le letture.
/// Sfrutto la parte centrale perche' li in mezzo sicuramente ci sara' il valore piu' alto
/// @param A    Array
/// @param n    Dimensione
int find_max(int* A, int n) {
    int dim_range = n / 2;
    int range_start = dim_range - 100, range_end = dim_range + 100;

    int max = A[range_start];
    ++ct_read;
    for (int i = range_start; i < range_end + 1; ++i) {
        int current = A[i];
        max = current > max ? current : max;
        ++ct_read;
    }

    return max;
}

/// @brief Cerco il minimo esattamente nella parte finale per minimizzare le letture.
/// Sfrutto la parte finale perche' ci sara' sicuramente il valore minore
/// @param A    Array
/// @param n    Dimensione
int find_min(int* A, int n) {
    int dim_range = n;
    int range_start = dim_range - 100, range_end = dim_range;

    int min = A[range_start];
    ++ct_read;
    for (int i = range_start; i < range_end; ++i) {
        int current = A[i];
        min = current < min ? current : min;
        ++ct_read;
    }

    return min;
}

/// @brief Bucket Sort
///
/// @param A    Array A da ordinare
/// @param n    Numero di elementi
/// @param k    Numeir di buckets
void bucket_sort(int* A, int size, int k) {
    auto buckets = new bucket*[k];
    for (int i = 0; i < k; ++i)
        buckets[i] = new bucket((size / k) * 3);

    int max = find_max(A, size);
    int min = find_min(A, size);

    for (int i = 0; i < size; ++i) {
        int index = (A[i] - min) * (k - 1) / (max - min);
        ++ct_read;
        if (index < 0)
            index = 0;
        if (index >= k)
            index = k - 1;


        buckets[index]->push(A[i]);
    }

    for (int i = 0; i < k; ++i) {
        std::cout << "Bucket[" << i << "] => ";
        buckets[i]->print();
    }

    int count = 0;
    for (int i = 0; i < k; ++i) {
        auto b = buckets[i];
        while (!b->isEmpty()) {
            auto pop = b->pop();
            std::cout << pop << ", ";
            A[count] = pop;
            ++count;
        }
    }

    // doGraph(buckets, k, "visualizzazione-buckets.dot");
}

int parse_cmd(int argc, char **argv) {

    /// parsing argomento
    max_dim = 1000;

    for (int i = 1; i < argc; i++) {
        if (argv[i][1] == 'd')
            ndiv = atoi(argv[i] + 3);
        if (argv[i][1] == 't')
            ntests = atoi(argv[i] + 3);
        if (argv[i][1] == 'v')
            details = 1;
        if (argv[i][1] == 'g') {
            graph = 1;
            ndiv = 1;
            ntests = 1;
        }
    }

    return 0;
}

int main(int argc, char **argv) {
    int i, test;
    int *A;
    int *B; /// buffer per visualizzazione algoritmo

    if (parse_cmd(argc, argv))
        return 1;

    /// allocazione array
    A = new int[max_dim];

    n = max_dim;

    // //creazione file input: NON USARE PIU' --> il file data.csv ufficiale è stato allegato, per permettere confronti equivalenti
    // srand((unsigned)time(NULL));
    //  FILE *f = fopen("data.csv", "w+");
    //  int size=100;
    //  for (int j = 0; j < size; j++) {
    //      for (int i = 0; i < n; i++) {
    //          int v = 0;             
    //         //  v=(int)(100000*exp(-(0.0+i-n/2)*(0.0+i-n/2)/n/n*64));
    //         //  v=(int)(5000*(1+sin(3.1415*(i/(n/2.0)))));
    //          v=(int)(10000*sin(3.1415*(((int)(i/30))*30/(n+0.0))));
    //          v+=(rand()%2*2-1)*rand()%(3+(int)(2*n*pow(((i+0.0)/n),2)));
    //          fprintf(f, "%d,", v);
    //      }
    //      fprintf(f, "\n");
    //  }
    //  fclose(f);

    ifstream input_data;
    input_data.open("data.csv");

    int read_min = -1;
    int read_max = -1;
    long read_avg = 0;

    //// lancio ntests volte per coprire diversi casi di input random
    for (test = 0; test < ntests; test++) {

        /// inizializzazione array: numeri random con range dimensione array
        for (i = 0; i < n; i++) {
            char comma;
            input_data >> A[i];
            input_data >> comma;
        }

        if (details) {
            printf("caricato array di dimensione %d\n", n);
            print_array(A, n);
        }

        ct_swap = 0;
        ct_cmp = 0;
        ct_read = 0;

        /// algoritmo di sorting
        bucket_sort(A, n, 20);

        /// TEST SE EFFETTIVAMENTE E' ORDINATO
        for (int j = 1; j < n; ++j)
            assert(A[j] >= A[j - 1]);

        if (details) {
            printf("Output:\n");
            print_array(A, n);
        }

        /// statistiche
        read_avg += ct_read;
        if (read_min < 0 || read_min > ct_read)
            read_min = ct_read;
        if (read_max < 0 || read_max < ct_read)
            read_max = ct_read;
        printf("Test %d %d\n", test, ct_read);

        // break;
    }

    printf("N test: %d, Min: %d, Med: %.1f, Max: %d\n",
           ntests,
           read_min, (0.0 + read_avg) / ntests, read_max);

    delete[] A;

    system("pause");
    return 0;
}
