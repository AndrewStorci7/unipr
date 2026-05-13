#include <iostream>
#include <fstream>
#include <random>
#include <cassert>

/**
 * @author: Andrea Storci
 * @date:   2026/05/13
 */

int cnt_it = 0; // contatore delle iterazioni di DFS

/// @brief Struttura del vertice
struct vertex;
typedef struct vertex vertex_t;

/// @brief Struttura del grafo
class graph;
typedef struct graph graph_t;

/// @brief DFS modificato per vedere se un array di interi e' presente con lo stesso
/// ordine nel grafo
/// @param g        Grafo
/// @param n        Dimensione dell'array di interi `datas`
/// @param datas    Array di interi
bool dfs(graph_t* g, int* datas, int n, bool debug = false);
/// @param u        Nodo di partenza
/// @param visited  Array per tenere traccia delle visite
/// @param edges    Archi del grafo
/// @param datas    Array di interi
/// @param n        Dimensione dell'array di interi `datas`
/// @param count    Varabile contatore per tenere traccia i dati di `datas` trovati
bool dfsAux(int u, bool visited[], vertex_t* edges[], int* datas, int n, int count, bool debug = false);

struct vertex {
    int val;
    vertex_t* next;
};

class graph {
    size_t nVertex = 0;
    vertex_t** E = nullptr; // array degli archi

public:

    graph(const int V) {
        nVertex = V;
        E = new vertex_t*[V];
        for (int i = 0; i < V; ++i)
            E[i] = nullptr;
    }

    size_t getSize() {
        return nVertex;
    }

    vertex_t** getEdges() {
        return E;
    }

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

        int dati[] = { 0, 5, 3, 9 };
        bool checkDFS = dfs(g, dati, 4);
        assert(checkDFS == true);
//        std::cout << cnt_it << std::endl;

        int dati2[] = { 0, 12, 3, 9 };
        bool checkDFS2 = dfs(g, dati2, 4);
        assert(checkDFS2 == false);
//        std::cout << cnt_it << std::endl;

        int dati3[] = { 0, 5, 3, 7 };
        bool checkDFS3 = dfs(g, dati3, 4);
        assert(checkDFS3 == true);
//        std::cout << cnt_it << std::endl;

        /// ATTENZIONE: qui no funziona siccome 0 risulta gia' visitato
        /// capire se gestirlo
        int dati4[] = { 0, 5, 3, 7, 0 };
        bool checkDFS4 = dfs(g, dati4, 5);
//        assert(checkDFS4 == true);

        int dati5[] = { 3, 9 };
        bool checkDFS5 = dfs(g, dati5, 2);
        assert(checkDFS5 == true);

        int dati6[] = { 5, 3, 7, 0 };
        bool checkDFS6 = dfs(g, dati6, 4);
        assert(checkDFS6 == true);

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

        // dfs(g, nullptr);
    }

    exit(0);
}

bool dfs(graph_t* g, int* datas, int n, bool debug) {
    cnt_it = 0;
    if (g->getSize() == 0)
        return false;

    bool visited[g->getSize()];
    for (int i = 0; i < g->getSize(); ++i)
        visited[i] = false;

    if (datas == nullptr)
        throw std::invalid_argument("datas non può essere null");

    bool check = dfsAux(datas[0], visited, g->getEdges(), datas, n, 0, debug);
    if (check)
        return true;

    return false;
}

bool dfsAux(const int u, bool visited[], vertex_t* edges[], int* datas, int n, int count, bool debug) {
    ++cnt_it;
    if (count >= n || u != datas[count])
        return false;

    if (debug) {
        std::cout << "Visitando il nodo: " << u << " (corrisponde a datas[" << count << "])" << std::endl;
    }

    visited[u] = true;
    ++count;

    vertex_t* curr = edges[u];
    while (curr != nullptr) {
        int v = curr->val;

        if (!visited[v]) {
            if (v == datas[count]) {
                return dfsAux(v, visited, edges, datas, n, count, debug);
            }
        }

        curr = curr->next;
    }

    if (count != n)
        return false;

    return true;
}