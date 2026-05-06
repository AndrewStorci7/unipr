#include <iostream>

/// @brief Struttura del nodo
struct node;
typedef struct node node_t;

/// @brief Struttura del grafo
struct graph;
typedef struct graph graph_t;

struct node {
    int data;
    node_t* next = nullptr;

    bool hasNext() {
        return this->next != nullptr;
    }
};



int main(int argc, char* argv[]) {

    

    return 0;
}