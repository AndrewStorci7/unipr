#include <iostream>
#include <fstream>

using namespace std;

int find_max(int* A, int n) {
//    int dim_range = n / 3;
//    int range_start = dim_range, range_end = dim_range * 2;

    int dim_range = n;
    int range_start = 0;
    int range_end= n;

    int max = A[range_start];
    int index_max = 0;
    // ++ct_read;
    for (int i = range_start; i < range_end + 1; ++i) {
        int current = A[i];
        if (current > max) {
            max = current;
            index_max = i;
        }
        // ++ct_read;
    }
    std::cout << "Minimo trovato in posizione: " << index_max << " => " << max << std::endl;

    return max;
}

int find_min(int* A, int n) {
//    int dim_range = n / 3;
//    int range_start = dim_range, range_end = dim_range * 2;

    int range_start = 0;
    int range_end = n;

    int min = A[range_start];
    int index_min = 0;
    // ++ct_read;
    for (int i = range_start; i < range_end + 1; ++i) {
        int current = A[i];
        if (current < min) {
            min = current;
            index_min = i;
        }
        // ++ct_read;
    }

    std::cout << "Minimo trovato in posizione: " << index_min << " => " << min << std::endl;

    return min;
}

void print_array(int *A, int dim) {
    for (int j = 0; j < dim; j++) {
        printf("%d ", A[j]);
    }
    printf("\n");
}

int main (int argc, char* argv[]) {

    int i, test, ntests = 100;
    int *A;
    int *B; /// buffer per visualizzazione algoritmo
    int max_dim = 1000;

//    if (parse_cmd(argc, argv))
//        return 1;


    /// allocazione array
    A = new int[max_dim];

    int n = max_dim;

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

        // if (details) {
        //     printf("caricato array di dimensione %d\n", n);
        //     print_array(A, n);
        // }

        int ct_swap = 0;
        int ct_cmp = 0;
        int ct_read = 0;

        /// algoritmo di sorting
//        bucket_sort(A, n, 20);
//
//        if (details) {
//            printf("Output:\n");
//            print_array(A, n);
//        }

        find_max(A, n);
        find_min(A, n);

        /// statistiche
        read_avg += ct_read;
        if (read_min < 0 || read_min > ct_read)
            read_min = ct_read;
        if (read_max < 0 || read_max < ct_read)
            read_max = ct_read;
        printf("Test %d %d\n", test, ct_read);
    }
}