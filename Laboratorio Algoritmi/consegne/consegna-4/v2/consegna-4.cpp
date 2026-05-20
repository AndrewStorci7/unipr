#include <iostream>
#include <fstream>
#include <random>
#include <cassert>

#define DEBUG_MODE true
#define INFTY (float)INT_MAX

int cnt_it = 0; // contatore delle iterazioni di shortestPath e bellmanFord

struct heap;
typedef struct heap heap_t;

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

/// @brief Algoritmo Shortest Path modificato
/// @param g        Grafo
/// @param p        Nodo di partenza
/// @param q        Nodo di arrivo
// int* shortestPath(graph_t* g, int p, int q);
void shortestPath(graph_t* g, int p, int q);

/// @brief ALgoritmo di Bellman-Ford
/// @param g        Grafo
/// @param p        Nodo di partenza
void bellmanFord(graph_t* g, int p);

struct heap {
private:
    size_t maxSize = 0;
    size_t size = 0;
    int* V = nullptr;       // Memorizza l'id dei nodi
    int* pos = nullptr;     // Memorizza in che indice si trova un certo nodo. pos[nodo] = indice in V
    float* dist = nullptr;  // Puntatore all'array V_dist di shortestPath

    void swapNodes(int i, int j) {
        int nodeI = V[i];
        int nodeJ = V[j];

        V[i] = nodeJ;
        V[j] = nodeI;

        pos[nodeI] = j;
        pos[nodeJ] = i;
    }

public:
    heap(int n, float* d) {
        maxSize = n;
        dist = d;
        V = new int[n];
        pos = new int[n];
        for (int i = 0; i < n; ++i) {
            V[i] = -1;
            pos[i] = -1;
        }
    }

    ~heap() {
        delete[] V;
        delete[] pos;
    }

    int getParent(int n) const {
        if (n == 0)
            return -1;
        return (n - 1) / 2;
    }

    int getLeftChild(int n) const {
        if (2 * n + 1 >= maxSize)
            return -1;
        return 2 * n + 1;
    }

    int getRightChild(int n) const {
        if (2 * n + 2 >= maxSize)
            return -1;
        return 2 * n + 2;
    }

    bool isLeaf(int n) const {
        return getLeftChild(n) == -1;
    }

    bool isEmpty() const {
        return size == 0;
    }

    bool contains(int nodo) const {
        return pos[nodo] != -1;
    }

    void push(int nodo) {
        if (size >= maxSize) return;

        int i = size;
        V[i] = nodo;
        pos[nodo] = i;
        ++size;

        while (i != 0 && dist[V[i]] < dist[V[getParent(i)]]) {
            ++cnt_it;
            swapNodes(i, getParent(i));
            i = getParent(i);
        }
    }

    int pop() {
        if (size <= 0) return -1;

        int maxNode = V[0];

        int lastNode = V[size - 1];
        V[0] = lastNode;
        pos[lastNode] = 0;

        pos[maxNode] = -1;
        --size;

        int i = 0;
        while (!isLeaf(i)) {
            ++cnt_it;
            int swapIndex = i;
            int left = getLeftChild(i);
            int right = getRightChild(i);

            if (left < size && dist[V[left]] < dist[V[swapIndex]])
                swapIndex = left;

            if (right < size && dist[V[right]] < dist[V[swapIndex]])
                swapIndex = right;

            if (swapIndex == i)
                break;

            swapNodes(i, swapIndex);
            i = swapIndex;
        }

        return maxNode;
    }

    void decreaseKey(int nodo, float nuova_distanza) {
        dist[nodo] = nuova_distanza;
        int i = pos[nodo];

        while (i != 0 && dist[V[i]] < dist[V[getParent(i)]]) {
            ++cnt_it;
            swapNodes(i, getParent(i));
            i = getParent(i);
        }
    }

    void doGraph(const std::string& nomeFile) const {
        std::ofstream out(nomeFile);

        if (!out.is_open()) {
            std::cerr << "Errore nell'apertura del file per l'export!" << std::endl;
            return;
        }

        out << "digraph Heap {" << std::endl;
        out << "    node [shape=circle];" << std::endl;

        for (int i = 0; i < size; ++i) {
            out << "    " << i << " [label=\"" << V[i] << "\"];" << std::endl;

            int left = getLeftChild(i);
            if (left != -1 && left < (int)size)
                out << "    " << i << " -> " << left << ";" << std::endl;

            int right = getRightChild(i);
            if (right != -1 && right < (int)size)
                out << "    " << i << " -> " << right << ";" << std::endl;
        }

        out << "}" << std::endl;
        out.close();
        std::cout << "File " << nomeFile << " generato correttamente." << std::endl;
    }

};

struct vertex {
    int val = 0;
    vertex_t* next = nullptr;
    float w = 0.0;
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
        inDegs = new size_t[V];
        outDegs = new size_t[V];

        for (int i = 0; i < V; ++i) {
            E[i] = nullptr;
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

    size_t getSize() const {
        return nVertexes;
    }

    size_t getEdgesTotal() const {
        return nEdges;
    }

    vertex_t** getEdges() {
        return E;
    }

    void addEdge(const int src, const int dest, const float w) {

//        V_visitato[src] = 0; // flag = non visitato
//        V_prev[src] = -1;    // non c'e' precedente
//        V_dist[src] = INFTY; // infinito

        const auto newVertex = new vertex_t{dest, E[src], w};
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

            while (temp != nullptr) {
                out << "    " << i << " -> " << temp->val
                    << " [label=\"" << (temp != nullptr ? temp->w : 0.0) << "\"];" << std::endl;

                temp = temp->next;
            }
        }

        out << "}" << std::endl;
        out.close();

        std::cout << "File " << nomeFile << " generato con successo." << std::endl;
    }
};

int main (int argc, char* argv[]) {

    { /// Grafo pesato
        auto g = new graph(10);
        g->addEdge(0, 1, 12);
        g->addEdge(0, 5, 11);
        g->addEdge(0, 2, 2);
        g->addEdge(1, 2, 10);
        g->addEdge(2, 1, 1);
        g->addEdge(2, 8, 0.5);
        g->addEdge(2, 3, 1);
        g->addEdge(3, 7, 4);
        g->addEdge(3, 9, 4.6);
        g->addEdge(4, 2, 3);
        g->addEdge(5, 3, 3.5);
        g->addEdge(6, 1, 14);
        g->addEdge(7, 0, 45);
        g->addEdge(7, 8, 2);
        g->addEdge(8, 9, 1);

        g->doGraph("grafo-connesso.dot");

        shortestPath(g, 0, 9);
        std::cout << "Numero nodi: " << g->getSize()
            << ", Iterazioni: " << cnt_it
            << "; complessita': O("
            << ((int)(g->getSize() + g->getEdgesTotal()) * log2(g->getSize()))
            << ")" << std::endl;
        assert(cnt_it < ((g->getSize() + g->getEdgesTotal()) * log(g->getSize())));

//        exit(0);
    }

    { /// Grafo random

        int n_nodi = 40;

        graph_t* g = new graph_t(n_nodi);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distribNode(1, n_nodi);
        std::uniform_real_distribution<float> distribWeight(1.0, 40.0);

        for (int i = 0; i < n_nodi; ++i) {
            int r1 = distribNode(gen);
            int r2 = distribNode(gen);
            float w = distribWeight(gen);
            g->addEdge(r1, r2, w);
        }

        shortestPath(g, 1, 9);
        std::cout << "Numero nodi: " << g->getSize()
                  << ", Iterazioni: " << cnt_it
                  << "; complessita': O("
                  << ((int)(g->getSize() + g->getEdgesTotal()) * log2(g->getSize()))
                  << ")" << std::endl;
        assert(cnt_it < ((g->getSize() + g->getEdgesTotal()) * log(g->getSize())));

        g->doGraph("grafo-random.dot");
    }

    { /// Grafo con un solo peso negativo
        graph_t* g = new graph_t(10);
        g->addEdge(0, 1, -1);
        g->addEdge(0, 2, 2);
        g->addEdge(1, 3, 3);
        g->addEdge(2, 3, 0.5);
        g->addEdge(3, 4, 6);
        g->addEdge(3, 5, -3);
        g->addEdge(4, 6, 2.5);
        g->addEdge(5, 6, 1.5);
        g->addEdge(6, 7, 2.5);
        g->addEdge(6, 8, 2.5);
        g->addEdge(7, 9, 2.5);
        g->addEdge(8, 9, 2.5);

        g->doGraph("grafo-pesi-negativi.dot");

        bellmanFord(g, 0);
    }

    { /// Grafo con cicli negativi
        graph_t* g = new graph_t(12);
        g->addEdge(0, 1, -1);
        g->addEdge(0, 2, 2);
        g->addEdge(1, 3, 3);
        g->addEdge(2, 3, 0.5);
        g->addEdge(3, 4, 6);
        g->addEdge(3, 5, 7);
        g->addEdge(4, 6, 2.5);
        g->addEdge(5, 6, 1.5);
        g->addEdge(5, 10, -12);
        g->addEdge(10, 11, -2);
        g->addEdge(11, 5, -4);
        g->addEdge(6, 7, 2.5);
        g->addEdge(6, 8, 2.5);
        g->addEdge(7, 9, 2.5);
        g->addEdge(8, 9, 2.5);

        g->doGraph("grafo-ciclo-negativo.dot");

//        bellmanFord(g, 0);
    }
}

// int* shortestPath(graph_t* g, int p, int q) {
void shortestPath(graph_t* g, int p, int q) {
    if (g->getSize() == 0) {
        perror("Il grafo e' vuoto");
        return;
    }

    cnt_it = 0;
    int V = (int) g->getSize();

    auto V_prev = new int[V];
    auto V_dist = new float[V];

    for (int i = 0; i < V; ++i) {
        V_prev[i] = -1;
        V_dist[i] = INFTY;
    }

    heap h(V, V_dist);

    V_dist[p] = 0.0;

    for (int i = 0; i < V; ++i)
        h.push(i);

    auto E = g->getEdges();

    while (!h.isEmpty()) {
        ++cnt_it;

        int u = h.pop();

        if (V_dist[u] == INFTY)
            break;

        // nodo trovato
//        if (u == q)
//            break;

        auto temp = E[u];
        while (temp != nullptr) {
            ++cnt_it;
            int v = temp->val;
            float w = temp->w;

            if (h.contains(v) && V_dist[u] + w < V_dist[v]) {
                V_prev[v] = u;
                h.decreaseKey(v, V_dist[u] + w);
            }

            temp = temp->next;
        }
    }

//    std::cout << "Distanza minima da " << p << " a " << q << ": " << V_dist[q] << "\n";
//    std::cout << "Percorso: ";
//
//    int currentNode = q;
//
//    while (currentNode != -1) {
//        std::cout << currentNode;
//        if (currentNode == p)
//            std::cout << std::endl;
//        else
//            std::cout << " <- ";
//
//        currentNode = V_prev[currentNode];
//    }

    delete[] V_dist;
    delete[] V_prev;
}

void bellmanFord(graph_t* g, int p) {
    if (g->getSize() == 0) {
        perror("Il grafo e' vuoto");
        return;
    }

    cnt_it = 0;
    int V = (int) g->getSize();

    auto V_prev = new int[V];
    auto V_dist = new float[V];

    for (int i = 0; i < V; ++i) {
        V_prev[i] = -1;
        V_dist[i] = INFTY;
    }

    V_dist[p] = 0.0;

    auto E = g->getEdges();

    for (int i = 0; i < V; ++i) {
        for (int u = 0; u < V; ++u) {
            auto temp = E[u];

            while (temp != nullptr) {
                ++cnt_it;
                int v = temp->val;
                float w = temp->w;

                if (V_dist[u] != INFTY && V_dist[u] + w < V_dist[v]) {
                    V_dist[v] = V_dist[u] + w;
                    V_prev[v] = u;
                }

                temp = temp->next;
            }
        }
    }

    // Contorllo di cicli negativi
    bool negativeCicle = false;

    for (int i = 0; i < V; ++i) {
        auto temp = E[i];

        while (temp != nullptr) {
            int v = temp->val;
            float w = temp->w;

            if (V_dist[i] != INFTY && V_dist[i] + w < V_dist[v]) {
                negativeCicle = true;
                break;
            }

            temp = temp->next;
        }

        if (negativeCicle)
            break;
    }

    std::cout << "Iterazioni Bellman-Ford: " << cnt_it << ", V * E: " << g->getSize() * g->getEdgesTotal() << std::endl;

    if (negativeCicle)
        perror("Ciclo negativo identificato!");
}
