#include <iostream>
#include <fstream>
#include <random>

#define DEBUG_MODE true
#define INFTY (float)INT_MAX

int cnt_it = 0; // contatore delle iterazioni di shortestPath

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

struct heap {
private:
    size_t maxSize = 0;
    size_t size = 0;
    int* V = nullptr;

public:
    heap(int n) {
        maxSize = n;
        V = new int[n];
        for (int i = 0; i < n; ++i)
            V[i] = -1;
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

    void push(int val) {
        if (size >= maxSize) {
            perror("Heap pieno");
            return;
        }

        int i = size;
        V[i] = val;
        ++size;

        while (i != 0) {
            ++cnt_it;
            int tmp = V[getParent(i)];
            /// Propieta' dell'HEAP rispettata
            if (tmp >= V[i])
                return;

            V[getParent(i)] = V[i];
            V[i] = tmp;

            i = getParent(i);
        }

    }

    int pop() {
        if (size <= 0) {
            perror("Heap vuoto");
            return -1;
        }

        int max = V[0];
        V[0] = V[size - 1];
        V[size - 1] = max;

        --size;

        int i = 0;
        while (!isLeaf(i)) {
            ++cnt_it;
            int swapIndex = -1;

            if (V[i] < V[getLeftChild(i)]) {
                /// il nodo e' piu' piccolo

                swapIndex = getLeftChild(i);

                if (getRightChild(i) >= 0 && V[getLeftChild(i)] < V[getRightChild(i)])
                    swapIndex = getRightChild(i);
            } else {
                /// il nodo e' piu' grande

                if (getRightChild(i) < 0)
                    break;

                if (V[i] < V[getRightChild(i)])
                    swapIndex = getRightChild(i);
                else
                    break;
            }

            int tmp = V[i];
            V[i] = V[swapIndex];
            V[swapIndex] = tmp;

            i = swapIndex;
        }

        return max;
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

    size_t getSize() {
        return nVertexes;
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

    { /// Test Heap

        auto heap = new heap_t(10);

        for (int i = 0; i < 10; ++i)
            heap->push(i * 2);

        heap->doGraph("heap.dot");
    }

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
        std::cout << "Numero nodi: " << g->getSize() << ", Iterazioni: " << cnt_it << std::endl;

//        exit(0);
    }

    { /// Grafo random

        int n_nodi = 20;

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

        g->doGraph("grafo.dot");

    }
}

// int* shortestPath(graph_t* g, int p, int q) {
void shortestPath(graph_t* g, int p, int q) {

    cnt_it = 0;

    /*      V_visitato[i]=0;  // flag = non visitato
      V_prev[i]=-1;  // non c'e' precedente
      V_dist[i]=INFTY;  // infinito
    */

    auto V_visitato = new bool[g->getSize()]; // nodo visitato?
    auto V_prev = new int[g->getSize()];     // nodo precedente dalla visita
    auto V_dist = new float[g->getSize()];   // distanza da sorgente

    for (int i = 0; i < g->getSize(); ++i) {
        V_visitato[i] = false;
        V_prev[i] = -1;
        V_dist[i] = INFTY;
    }

    // distanza nodo di partenza = 0
    V_dist[p] = 0.0;
    auto E = g->getEdges();

    int size = (int)g->getSize(); /// contatore degli elementi in coda (V_visitato)

    for (int i = 0; i < size; ++i) {
        ++cnt_it;

        float minDist = INFTY;
        int u = -1;

        for (int j = 0; j < size; ++j) {
            ++cnt_it;
            if (!V_visitato[j] && V_dist[j] < minDist) {
                minDist = V_dist[j];
                u = j;
            }
        }

        if (u == -1 || V_dist[u] == INFTY)
            break;

        V_visitato[u] = true;

        // nodo trovato
//        if (u == q)
//            break;

        auto temp = E[u];
        while (temp != nullptr) {
            ++cnt_it;
            int v = temp->val;
            float w = temp->w;

            if (!V_visitato[v] && V_dist[u] + w < V_dist[v]) {
                V_dist[v] = V_dist[u] + w;
                V_prev[v] = u;
            }

            temp = temp->next;
        }
    }

    std::cout << "Distanza minima da " << p << " a " << q << ": " << V_dist[q] << "\n";
    std::cout << "Percorso: ";

    int currentNode = q;

    while (currentNode != -1) {
        std::cout << currentNode;
        if (currentNode == p)
            std::cout << std::endl;
        else
            std::cout << " <- ";

        currentNode = V_prev[currentNode];
    }

    delete[] V_dist;
    delete[] V_visitato;
    delete[] V_prev;
}
