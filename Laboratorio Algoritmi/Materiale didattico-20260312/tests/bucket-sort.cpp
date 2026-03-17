#include <iostream>
#include <vector>

#define NAME "test"
using namespace std;

int cnt_read = 0;
int cnt_write = 0;

void bucket_sort(int *, int);
void insertion_sort(vector<int> &);
void print(int *, int);

struct node
{
    /* data */
};

int main(int argc, char *argv[])
{

    // if (argc <= 1) {
    //     cerr << "Usage: ./" << NAME << "" << endl;
    //     return 1;
    // }

    int size = 30;
    // int *A = new int[size]{1, 0, 1, 2, 1, -2, 2, 1, 2, 1, 0, 0, 0, -1, 0, -1, -2, -2, 0, 1, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0};
    int *A = new int[size]{939, 939, 937, 942, 938, 945, 941, 944, 940, 946, 943, 945, 942, 939, 946, 938, 937, 945, 941, 938, 938, 939, 943, 943, 935, 946, 941, 947, 942, 941};

    print(A, size);
    bucket_sort(A, size);
    print(A, size);

    cout << endl;
    cout << "conteggio totale letture: " << cnt_read << endl;

    exit(0);
}

void insertion_sort(vector<int> &A)
{

    // list<int>::iterator it = A.begin();

    int n = A.size();
    for (int i = 1; i < n; i++)
    {
        // cnt_read++;
        int key = A[i];
        int j = i - 1;
        // cnt_read++;
        while (j >= 0 && A[j] > key)
        {
            // cnt_read++;
            // cnt_read++;
            A[j + 1] = A[j];
            --j;
        }
        // cnt_read++;
        A[j + 1] = key;
    }
}

void bucket_sort(int *A, int n)
{

    // i buckets
    vector<vector<int>> buckets(n);
    int min = 0;

    for (int i = 0; i < n; ++i)
    {
        ++cnt_read;
        min = A[i] > min ? A[i] : min;
    }

    for (int i = 0; i < n; ++i)
    {
        int elem = A[i];
        ++cnt_read;
        // int index = int((elem - min) / n);
        int normalizedIndex = int((elem - min) / n);
        // int normalizedIndex = index < 0 ? -1 * index : index;
        cout << normalizedIndex << endl;
        buckets[normalizedIndex].push_back(elem);
    }

    for (int i = 0; i < n; ++i)
    {
        insertion_sort(buckets[i]);
    }

    int index = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int elem : buckets[i])
        {
            A[index] = elem;
            ++index;
        }
    }
}

void print(int *A, int n)
{
    cout << "[";
    for (int i = 0; i < n; ++i)
    {
        cout << A[i] << ((i < (n - 1)) ? ", " : "");
    }
    cout << "]" << endl;
}