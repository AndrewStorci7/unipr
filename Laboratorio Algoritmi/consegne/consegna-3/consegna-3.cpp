#include <iostream>
#include <fstream>
#include <random>
#include <cassert>

#define DEBUG_MODE false

/**
 * @author: Andrea Storci
 * @date:   2026/05/13
 */

int cnt_it = 0; // contatore delle iterazioni di DFS

struct queue;
typedef struct queue queue_t;

struct queue_node;
typedef struct queue_node qnode_t;

/// @brief Struttura del vertice
struct vertex;
typedef struct vertex vertex_t;

/// @brief Struttura del grafo
class graph;
typedef class graph graph_t;

/// @brief DFS modificato per vedere se un array di interi e' presente con lo stesso
/// ordine nel grafo
/// @param g        Grafo
/// @param n        Dimensione dell'array di interi `datas`
/// @param datas    Array di interi
bool dfs(graph_t* g, int* datas, int n, bool debug = DEBUG_MODE);
/// @param u        Nodo di partenza
/// @param visited  Array per tenere traccia delle visite
/// @param edges    Archi del grafo
/// @param datas    Array di interi
/// @param n        Dimensione dell'array di interi `datas`
/// @param count    Varabile contatore per tenere traccia i dati di `datas` trovati
bool dfsAux(int u, vertex_t* edges[], int* datas, int n, int count, bool debug = DEBUG_MODE);

struct vertex {
    int val = 0;
    vertex_t* next = nullptr;
};

class graph {
    int nVertexes = 0;
    int nEdges = 0;
    vertex_t** E = nullptr; // array degli archi
    size_t* inDegs = nullptr;
    size_t* outDegs = nullptr;

public:

    graph(const int V) {
        nVertexes = V;
        E = new vertex_t*[V];
        for (int i = 0; i < V; ++i)
            E[i] = nullptr;

        inDegs = new size_t[V];
        outDegs = new size_t[V];
        for (int i = 0; i < V; ++i) {
            inDegs[i] = 0;
            outDegs[i] = 0;
        }
    }

    ~graph() {
        if (E == nullptr)
            return;

        for (int i = 0; i < nVertexes; ++i)
            delete E[i];

        delete E;
        delete inDegs;
        delete outDegs;
    }

    size_t getSize() {
        return nVertexes;
    }

    vertex_t** getEdges() {
        return E;
    }

    void addEdge(const int src, const int dest) {

        const auto newVertex = new vertex_t{dest, E[src]};
        E[src] = newVertex;

        ++inDegs[dest];
        ++outDegs[src];

        nEdges += 1;
    }

    void doGraph(const std::string& nomeFile) const {
        std::ofstream out(nomeFile);

        if (!out.is_open()) {
            std::cerr << "Errore nell'apertura del file!" << std::endl;
            return;
        }

        out << "digraph G {" << std::endl;
        out << "    node [shape=circle];" << std::endl; // Forma di default per i nodi


        for (int i = 0; i < nVertexes; ++i) {
            auto temp = E[i];

            bool nodeEmpty = inDegs[i] == 0 && outDegs[i] == 0;

            out << "    " << i << " ["
                << (nodeEmpty ? "style=\"filled\" fillColor=\"#45FF67\" " : "")
                << "label=\"" << i << "\"];" << std::endl;
//                << " (in:"
//                << inDegs[i] << ", out:" << outDegs[i] << ")\"];" << std::endl;

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
        auto g = new graph(10);
        g->addEdge(0, 1);
        g->addEdge(0, 5);
        g->addEdge(1, 2);
        g->addEdge(2, 1);
        g->addEdge(2, 8);
        g->addEdge(3, 7);
        g->addEdge(3, 9);
        g->addEdge(4, 2);
        g->addEdge(5, 3);
        g->addEdge(6, 1);
        g->addEdge(7, 0);
        g->addEdge(8, 9);

        g->doGraph("grafo-connesso.dot");

        int dati[] = { 0, 5, 3, 9 };
        bool checkDFS = dfs(g, dati, 4);
        assert(checkDFS == true);
        std::cout << cnt_it << std::endl;

        int dati2[] = { 0, 1, 2, 8 };
        bool checkDFS2 = dfs(g, dati2, 4);
        assert(checkDFS2 == true);
        std::cout << cnt_it << std::endl;

        int dati3[] = { 0, 5, 3, 7 };
        bool checkDFS3 = dfs(g, dati3, 4);
        assert(checkDFS3 == true);
        std::cout << cnt_it << std::endl;

        /// ATTENZIONE: qui no funziona siccome 0 risulta gia' visitato
        /// capire se gestirlo
        int dati4[] = { 0, 5, 3, 7, 0 };
        bool checkDFS4 = dfs(g, dati4, 5);
        assert(checkDFS4 == true);
        std::cout << cnt_it << std::endl;

        int dati5[] = { 3, 9 };
        bool checkDFS5 = dfs(g, dati5, 2);
        assert(checkDFS5 == true);
        std::cout << cnt_it << std::endl;

        int dati6[] = { 5, 3, 7, 0 };
        bool checkDFS6 = dfs(g, dati6, 4);
        assert(checkDFS6 == true);
        std::cout << cnt_it << std::endl;

        int dati7[] = { 0, 5, 3, 7, 0, 1, 2, 1 };
        bool checkDFS7 = dfs(g, dati7, 8);
        assert(checkDFS7 == true);
        std::cout << cnt_it << std::endl;

        int dati8[] = { 0, 5, 3, 7, 0, 1, 2, 0 };
        bool checkDFS8 = dfs(g, dati8, 8);
        assert(checkDFS8 == false);

//        exit(0);
    }

    { /// Grafo random
        int MAX_VAL = 10;
        graph_t *g = new graph_t(MAX_VAL);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, MAX_VAL);

        for (int i = 0; i < MAX_VAL; ++i) {
            int r1 = distrib(gen);
            int r2 = distrib(gen);
            g->addEdge(r1, r2);
        }

        g->doGraph("grafo.dot");

        int dati[] = { 5, 3, 2, 7 };
        bool check = dfs(g, dati, 4);

        std::cout << "l'array: ";
        for (int i = 0; i < 3; ++i)
            std::cout << dati[i] << ", ";
        std::cout << dati[3] << " => "
            << (check ? "E' presente" : "Non e' presente")
            << std::endl;
    }

    exit(0);
}

bool dfs(graph_t* g, int* datas, int n, bool debug) {
    cnt_it = 0;
    if (g->getSize() == 0)
        return false;

    if (datas == nullptr)
        throw std::invalid_argument("datas non può essere null");

    bool check = dfsAux(datas[0], g->getEdges(), datas, n, 0, debug);
    if (check)
        return true;

    return false;
}

bool dfsAux(const int u, vertex_t* edges[], int* datas, int n, int count, bool debug) {
    ++cnt_it;
    if (count >= n || u != datas[count])
        return false;

    if (debug) {
        std::cout << "Visitando il nodo: " << u << " (corrisponde a datas[" << count << "])" << std::endl;
    }

    ++count;

    if (count == n)
        return true;

    vertex_t* curr = edges[u];
    while (curr != nullptr) {
        int v = curr->val;

        if (v == datas[count])
            return dfsAux(v, edges, datas, n, count, debug);

        curr = curr->next;
    }

    if (count != n)
        return false;

    return true;
}