#include "graph.h"

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

bool dfs(graph_t* g, int* datas, int n, bool debug) {
    // cnt_it = 0;
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
    // ++cnt_it;
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