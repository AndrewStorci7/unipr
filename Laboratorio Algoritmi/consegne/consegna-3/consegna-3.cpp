#include <iostream>

/// @brief Struttura del nodo
class node;
typedef struct node node_t;

/// @brief Struttura del grafo
class graph;
typedef struct graph graph_t;

class node {
private:
    int data;
    node_t* next = nullptr;

public:

    node(): data(), next(nullptr) {}
    node(int data): data(data), next(nullptr) {}
    node(int data, node_t* next): data(data), next(next) {}

    bool hasNext() {
        return this->next != nullptr;
    }
};

class graph {
private:
    node_t* head = nullptr;
    int size = 0;

public:

    graph(): head(nullptr), size(0) {}

    /// TODO: l'idea e' quella di passargli un array di nodi
    /// TODO: dove ad ogni nodo e' associato il suo next (l'arco)
    graph(int* V, int n): head(nullptr), size(0) {
        /// TODO: per l'aggiunta creare una funzione ausiliare
        this->add(V, n);
    }

    void add(int *V, int n) {
        for (int i = 0; i < n; ++i) {

        }
    }

    bool isEmpty() {
        return this->size == 0;
    }
};

int main(int argc, char* argv[]) {

    

    return 0;
}