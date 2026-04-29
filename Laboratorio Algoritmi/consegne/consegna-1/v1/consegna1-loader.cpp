#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cstdlib>
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

void print_array(int *A, int dim)
{
    for (int j = 0; j < dim; j++)
    {
        printf("%d ", A[j]);
    }
    printf("\n");
}

const int RUN = 32;

void binary_insertion_sort(int *arr, int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        int key = arr[i];
        ++ct_read;
        int lo = left;
        int hi = i - 1;

        while (lo <= hi)
        {
            int mid = (lo + hi) / 2;
            ++ct_read;
            if (arr[mid] > key)
                hi = mid - 1;
            else
                lo = mid + 1;
        }

        for (int j = i - 1; j >= lo; j--)
        {
            arr[j + 1] = arr[j];
            ++ct_read;
        }

        arr[lo] = key;
    }
}

void merge(int *arr, int l, int m, int r)
{
    int len1 = m - l + 1;
    int len2 = r - m;

    int *left = new int[len1];
    int *right = new int[len2];

    for (int i = 0; i < len1; i++)
    {
        left[i] = arr[l + i];
        ++ct_read;
    }

    for (int i = 0; i < len2; i++)
    {
        right[i] = arr[m + 1 + i];
        ++ct_read;
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < len1 && j < len2)
    {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < len1)
        arr[k++] = left[i++];

    while (j < len2)
        arr[k++] = right[j++];

    delete[] left;
    delete[] right;
}

void tim_sort(int *arr, int p, int r)
{
    int n = r - p;

    for (int i = 0; i < n; i += RUN)
        binary_insertion_sort(arr, i, min(i + RUN - 1, n - 1));

    for (int size = RUN; size < n; size = 2 * size)
    {
        for (int left = 0; left < n; left += 2 * size)
        {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, n - 1);

            if (mid < right)
                merge(arr, left, mid, right);
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
        tim_sort(A, 0, 333);

        if (details)
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
