#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <cstdlib>
using namespace std;

struct Node
{
    int value;
    int count;
    Node *left;
    Node *right;

    Node(int v)
    {
        value = v;
        count = 1;
        left = nullptr;
        right = nullptr;
    }
};

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

void print_array(int *A, int dim)
{
    for (int j = 0; j < dim; j++)
    {
        printf("%d ", A[j]);
    }
    printf("\n");
}

void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
    /// aggiorno contatore globale di swap
    ct_swap++;
}

// Funzioni helper per muoversi nella sequenza di Leonardo
// b e c rappresentano LP[n] e LP[n-1]
inline void up(int &b, int &c)
{
    int temp = b;
    b = b + c + 1;
    c = temp;
}

inline void down(int &b, int &c)
{
    int temp = c;
    c = b - c - 1;
    b = temp;
}

// La procedura SIFT: assicura che un albero rispetti la proprietà di heap
void sift(int &A, int r1, int b1, int c1)
{
    while (b1 >= 3)
    {
        int r2 = r1 - b1 + c1; // figlio sinistro
        int e1 = A + r1;
        int e2 = A + r2;
        ++ct_read;
        ++ct_read;
        ++ct_read;
        if (e2 < A + (r1 - 1))
        { // confronta con il figlio destro
            r2 = r1 - 1;
            down(b1, c1);
        }

        if (e1 >= e2)
        {
            b1 = 1; // Proprietà di heap soddisfatta
        }
        else
        {
            swap(e1, e2);
            r1 = r2;
            down(b1, c1);
        }
    }
}

// La procedura TRINKLE: gestisce la proprietà di heap tra le radici della foresta
void trinkle(int &A, int r, int p, int b, int c)
{
    int r1 = r;
    int b1 = b;
    int c1 = c;
    int p1 = p;

    while (p1 > 0)
    {
        while ((p1 & 1) == 0)
        {
            p1 >>= 1;
            up(b1, c1);
        }

        int r3 = r1 - b1;
        int e3 = A + r3;
        int e1 = A + r1;
        ++ct_read;
        ++ct_read;
        if (p1 == 1 || e3 <= e1)
        {
            p1 = 0; // stop
        }
        else
        {
            p1--;
            if (b1 == 1)
            {
                ++ct_read;
                // swap(e1, A + (e3 > e1 ? r3 : r1)); // Semplificazione logica
                swap(e1, e3);
                r1 = r3;
            }
            else if (b1 >= 3)
            {
                int r2 = r1 - b1 + c1;
                int e2 = A + r2;
                ++ct_read;
                ++ct_read;
                if (e2 < A + (r1 - 1))
                {
                    r2 = r1 - 1;
                    down(b1, c1);
                    p1 <<= 1;
                }

                if (e3 >= e2)
                {
                    swap(e1, e3);
                    r1 = r3;
                }
                else
                {
                    swap(e1, e2);
                    r1 = r2;
                    down(b1, c1);
                    p1 = 0;
                }
            }
        }
    }
    sift(A, r1, b1, c1);
}

// La procedura SEMITRINKLE
void semitrinkle(int &A, int r, int p, int b, int c)
{
    int r1 = r - c;
    ++ct_read;
    ++ct_read;
    int e1 = A + r1;
    int e2 = A + r;

    if (e1 > e2)
    {
        swap(e2, e1);
        trinkle(A, r1, p, b, c);
    }
}

// Funzione principale Smoothsort
void smoothsort(int &A, int N)
{
    if (N <= 1)
        return;

    int q = 1;
    int r = 0;
    int p = 1;
    int b = 1;
    int c = 1;

    // Fase 1: Costruzione della foresta
    while (q < N)
    {
        if ((p & 7) == 3)
        {
            sift(A, r, b, c);
            p = (p + 1) >> 2;
            up(b, c);
            up(b, c);
        }
        else if ((p & 3) == 1)
        {
            if (q + c < N)
            {
                sift(A, r, b, c);
            }
            else
            {
                trinkle(A, r, p, b, c);
            }
            down(b, c);
            p <<= 1;
            while (b > 1)
            {
                down(b, c);
                p <<= 1;
            }
            p++;
        }
        q++;
        r++;
    }
    trinkle(A, r, p, b, c);

    // Fase 2: Decomposizione e ordinamento finale
    while (q > 1)
    {
        q--;
        if (b == 1)
        {
            r--;
            p--;
            while ((p & 1) == 0)
            {
                p >>= 1;
                up(b, c);
            }
        }
        else if (b >= 3)
        {
            p--;
            r = r - b + c;
            if (p > 0)
                semitrinkle(A, r, p, b, c);

            down(b, c);
            p = (p << 1) + 1;
            r = r + c;
            semitrinkle(A, r, p, b, c);

            down(b, c);
            p = (p << 1) + 1;
        }
    }
}

int parse_cmd(int argc, char **argv)
{

    /// parsing argomento
    max_dim = 1000;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][1] == 'd')
            ndiv = atoi(argv[i] + 3);
        if (argv[i][1] == 't')
            ntests = atoi(argv[i] + 3);
        if (argv[i][1] == 'v')
            details = 1;
        if (argv[i][1] == 'g')
        {
            graph = 1;
            ndiv = 1;
            ntests = 1;
        }
    }

    return 0;
}

int main(int argc, char **argv)
{
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
    for (test = 0; test < ntests; test++)
    {

        /// inizializzazione array: numeri random con range dimensione array
        for (i = 0; i < n; i++)
        {
            char comma;
            input_data >> A[i];
            input_data >> comma;
        }

        if (details)
        {
            printf("caricato array di dimensione %d\n", n);
            print_array(A, n);
        }

        ct_swap = 0;
        ct_cmp = 0;
        ct_read = 0;

        /// algoritmo di sorting
        // quick_sort(A, 0, n - 1);

        // 330 /33 = 11
        // for (int i = 330; i < 331; i += 330)
        // {

        //     // bucket_sort(A, start, end);
        //     // treeSort(A, start, end);
        //     smoothsort(A, i);
        // }

        smoothsort(*A, n);

        // bucket_sort(A, 0, n);
        // treeSort(A, 0, n);
        // smoothsort(A, n);

        if (details || test == 0)
        {
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
    }

    printf("N test: %d, Min: %d, Med: %.1f, Max: %d\n",
           ntests,
           read_min, (0.0 + read_avg) / ntests, read_max);

    delete[] A;

    system("pause");
    return 0;
}
