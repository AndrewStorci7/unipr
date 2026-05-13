#include <iostream>
#include <fstream>
#include <random>

/// @brief Struttura degli archi
//struct edges;
//typedef struct edges edges_t;

/// @brief Struttura del vertice
struct vertex;
typedef struct vertex vertex_t;

/// @brief Struttura del grafo
class graph;
typedef struct graph graph_t;

bool dfs(graph_t* g, int* datas);
void dfsAux(int u, bool visited[], vertex_t* edges[], int* datas);

struct vertex {
    int val;
    vertex_t* next;
};

class graph {
    size_t nVertex = 0;
    // int* V = nullptr; // array dei vertici
    vertex_t** E = nullptr; // array degli archi

public:

    graph(const int V) {
        nVertex = V;
        E = new vertex_t*[V];
        for (int i = 0; i < V; ++i)
            E[i] = nullptr;
    }

    // graph(int* V, int n) {
    //     nVertex = n;
    //     this->V = V;
    // }

    size_t getSize() {
        return nVertex;
    }

    vertex_t** getEdges() {
        return E;
    }

    // int* getVertex() {
    //     return V;
    // }

    void addVertex(const int src, const int dest) const {
        const auto newVertex = new vertex_t{dest, E[src]};
        E[src] = newVertex;
    }

    void doGraph(const std::string& nomeFile) const {
        std::ofstream out(nomeFile);

        if (!out.is_open()) {
            std::cerr << "Errore nell'apertura del file!" << std::endl;
            return;
        }

        out << "digraph G {" << std::endl;
        out << "    node [shape=circle];" << std::endl;

        for (int i = 0; i < nVertex; ++i) {
            auto temp = E[i];

            if (temp == nullptr)
                out << "    " << i << ";" << std::endl;

            while (temp != nullptr) {
                out << "    " << i << " -> " << temp->val << ";" << std::endl;
                temp = temp->next;
            }
        }

        out << "}" << std::endl;
        out.close();

        std::cout << "File " << nomeFile << " generato con successo." << std::endl;
    }
};

bool dfs(graph_t* g, int* datas) {
    if (g->getSize() == 0)
        return false;

    bool visited[g->getSize()];
    for (int i = 0; i < g->getSize(); ++i)
        visited[i] = false;

    if (datas == nullptr)
        throw std::invalid_argument("datas non può essere null");

    // for (int i = 0; i < g->getSize(); ++i) {
        // std::cout << "---- Inizio visita nodo " << i << " ---" << std::endl;
        dfsAux(datas[0], visited, g->getEdges(), datas);
        // std::cout << "---- Fine visita nodo ---" << std::endl;
    // }

    // dfsAux(0, visited, g->getEdges(), datas);

    return false;
}

void dfsAux(const int u, bool visited[], vertex_t* edges[], int* datas) {
    visited[u] = true;
    // std::cout << "Visito il nodo: " << u << std::endl;

    vertex_t* curr = edges[u];
    while (curr != nullptr) {
        int v = curr->val;
        if (!visited[v]) {
            // std::cout << "\tInizio visita ricorsiva del nodo " << v << std::endl;
            dfsAux(v, visited, edges, datas);
            // std::cout << "\tFine visita ricorsiva del nodo " << v << std::endl;
        }
        curr = curr->next;
    }
}

int main(int argc, char* argv[]) {

    { /// Grafo connesso
        graph_t* g = new graph(10);
        g->addVertex(0, 1);
        g->addVertex(0, 5);
        g->addVertex(1, 2);
        g->addVertex(2, 1);
        g->addVertex(2, 8);
        g->addVertex(3, 7);
        g->addVertex(3, 9);
        g->addVertex(4, 2);
        g->addVertex(5, 3);
        g->addVertex(6, 1);
        g->addVertex(7, 0);
        g->addVertex(8, 9);

        g->doGraph("grafo-connesso.dot");

        dfs(g, nullptr);
        exit(0);
    }

    { /// Grafo random
        graph_t *g = new graph_t(10);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 10);

        for (int i = 0; i < 10; ++i) {
            int r1 = distrib(gen);
            int r2 = distrib(gen);
            g->addVertex(r1, r2);
        }

        g->doGraph("grafo.dot");

        dfs(g, nullptr);
    }

    exit(0);
}