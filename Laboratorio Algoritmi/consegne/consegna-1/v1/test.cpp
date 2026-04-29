#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct node_t
{
    int index = 0;
    int lenght = 0;
    node_t *next = nullptr;
};

typedef struct pila
{
    int size = 0;
    node_t *next = nullptr;

    void push(int index, int lenght)
    {
        if (size == 0)
        {
            node_t *new_node = new node_t();
            new_node->index = index;
            new_node->lenght = lenght;
            this->next = new_node;
            ++size;
            return;
        }

        node_t *backup = next;
        while (backup->next != nullptr)
        {
            backup = backup->next;
        }

        node_t *new_node = new node_t();
        new_node->index = index;
        new_node->lenght = lenght;
        backup->next = new_node;
        ++size;
    }

    int get(int index)
    {

        node_t *next = this->next;

        while (next != nullptr)
        {
            if (next->index == index)
            {
                return next->lenght;
            }
            next = next->next;
        }

        return -1; // significa che non e' stato trovato
    }

} pila_t;

void print_pila(pila_t *stack)
{

    node_t *next = stack->next;

    while (next != nullptr)
    {
        std::cout << "Index: " << next->index << ", Length: " << next->lenght << std::endl;
        next = next->next;
    }
}

int binary_search(int *A, int val, int start, int end)
{
    while (start <= end && start >= 0)
    {
        int mid = ((end - start) / 2) + start;
        int val_mid = A[mid];
        // ++ct_read;

        if (val_mid == val)
        {
            return mid;
        }
        else
        {
            if (val > val_mid)
            {
                return binary_search(A, val, mid, end);
            }
            else
            {
                return binary_search(A, val, start, mid);
            }
        }
    }
}

int main()
{

    pila_t *stack = new pila_t();

    stack->push(0, 10);
    stack->push(1, 20);
    stack->push(2, 30);

    print_pila(stack);

    int A[] = {2, 6, 7, 10, 11, 14, 22, 45, 66, 67, 78, 123};

    printf("%d", binary_search(A, 67, 0, 12));

    return 0;
}