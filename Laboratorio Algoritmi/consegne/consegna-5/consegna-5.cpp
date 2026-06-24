#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/// apre il file CSV e carica le distanze in una matrice 2D dinamica, poi stampa un esempio di accesso alla matrice

// obiettivo: implementare kruskal e identificare gli ultimi archi aggiunti
// descrivere le coppie di città che corrispondono agli ultimi archi aggiunti e il significato geografico di queste coppie

std::string* capoluoghi = nullptr;

struct heap;
typedef struct heap heap_t;

struct edge;
typedef struct edge edge_t;

struct union_find;
typedef struct union_find union_t;

struct list;
typedef struct list list_t;

/// Kruskal
/// @param g        Grafo
/// @param n        Numerodi nodi
list_t* kruskal(float** g, int n);

struct node {
    edge_t* data = nullptr;
    node* next = nullptr;
};

struct list {
    size_t size = 0;
    node* head = nullptr;

    void push(edge_t* e) {
        auto newNode = new node{e, head};
        head = newNode;
        ++size;
    }

    edge_t* pop() {
        if (size == 0)
            return nullptr;

        auto ret = head->data;

        head = head->next;
        --size;

        return ret;
    }
};

struct union_find {
    size_t size = 0;
    int* V = nullptr;

    union_find(int n) {
        size = n;
        V = new int[n];
        for (int i = 0; i < n; ++i)
            V[i] = i;
    }

    ~union_find() {
        delete[] V;
    }

    void add(int i) {
        V[i] = i;
    }

    int find(int i) {
        if (V[i] == i)
            return i;

        return find(V[i]);
    }

    void unione(int u, int v) {
        V[u] = V[v];
    }

    void doGraph(const std::string& nomeFile) const {
        std::ofstream out(nomeFile);

        if (!out.is_open()) {
            std::cerr << "Errore nell'apertura del file per l'export!" << std::endl;
            return;
        }

        out << "digraph UnionFind {" << std::endl;
        out << "    rankdir=BT;" << std::endl;
        out << "    node [shape=circle];" << std::endl;

        for (int i = 0; i < size; ++i) {
            if (V[i] == i) {
                // Se e' un candidato
                out << "    " << i << " [shape=doublecircle];" << std::endl;
            } else {
                out << "    " << i << " [shape=circle];" << std::endl;
                out << "    " << i << " -> " << V[i] << ";" << std::endl;
            }
        }

        out << "}" << std::endl;
        out.close();
        std::cout << "File " << nomeFile << " generato correttamente." << std::endl;
    }
};

struct edge {
    // tento di riprodurre la coppia di una matrice di adiacenza
    int column = -1;
    int raw = -1;
    float weight = 0.0f;

    edge(): column(-1), raw(-1), weight(0.0f) {}
    edge(int c, int r, float w): column(c), raw(r), weight(w) {}

    void print() {
        std::cout << "(da: " << raw << " a: " << column << ", w: " << weight << ") -> ";
    }
};

struct heap {
private:
    size_t maxSize = 0;
    size_t size = 0;
    edge_t** V = nullptr;       // Memorizza le coppie dei nodi (archi)

    void swapNodes(int i, int j) {
        edge_t* nodeI = V[i];
        edge_t* nodeJ = V[j];

        V[i] = nodeJ;
        V[j] = nodeI;
    }

public:
    heap(int n) {
        maxSize = n;
        V = new edge_t*[n];
        for (int i = 0; i < n; ++i) {
            V[i] = new edge_t();
        }
    }

    ~heap() {
        delete[] V;
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

    void push(int col, int raw, float weight) {
        if (size >= maxSize)
            return;

        int i = size;
        V[i] = new edge_t(col, raw, weight);
        ++size;

        while (i != 0 && V[i]->weight < V[getParent(i)]->weight) {
            swapNodes(i, getParent(i));
            i = getParent(i);
        }
    }

    edge_t* pop() {
        if (size <= 0)
            return nullptr;

        auto minNode = V[0];

        auto lastNode = V[size - 1];
        V[0] = lastNode;

        --size;

        int i = 0;
        while (!isLeaf(i)) {
            int swapIndex = i;
            int left = getLeftChild(i);
            int right = getRightChild(i);

            if (left < size && V[left]->weight < V[swapIndex]->weight)
                swapIndex = left;

            if (right < size && V[right]->weight < V[swapIndex]->weight)
                swapIndex = right;

            if (swapIndex == i)
                break;

            swapNodes(i, swapIndex);
            i = swapIndex;
        }

        return minNode;
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
            out << "    " << i << " [label=\"" << V[i]->column << ":" << V[i]->raw << " -> " << V[i]->weight << "\"];" << std::endl;

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

void doGraphMST(list_t* MST, int N, int numClustersToHighlight, const std::string& nomeFile) {
    std::ofstream out(nomeFile);

    if (!out.is_open()) {
        std::cerr << "Errore nell'apertura del file per l'export MST!" << std::endl;
        return;
    }

    out << "graph SpanningTree {" << std::endl;
    out << "    node [shape=circle, style=filled];" << std::endl;
    out << "    layout=sfdp;" << std::endl;
    out << "    overlap=false;" << std::endl;

    int numRedEdges = numClustersToHighlight - 1;

    // identifico i cluster con la union-find
    union_t uf(N + 1);

    auto current = MST->head;
    int i = 0;

    while (current != nullptr) {
        if (i >= numRedEdges) {
            int root_u = uf.find(current->data->raw);
            int root_v = uf.find(current->data->column);
            if (root_u != root_v) {
                uf.unione(root_u, root_v);
            }
        }
        current = current->next;
        ++i;
    }

    /// palette dei colori per colorare i vari cluster
    std::string palette[] = {
            "lightblue", "lightgreen", "lightpink", "khaki",
            "plum", "peachpuff", "palegreen", "lightsalmon",
            "darkorchid", "chocolate", "darkgreen", "dodgerblue3",
            "gold", "gray45", "darkslategray2", "cadetblue", "aquamarine"
    };
    int numColors = 17;

    // array per mappare l'ID della radice del cluster al suo colore
    int* colorIndex = new int[N + 1];
    for(int j = 0; j <= N; ++j)
        colorIndex[j] = -1;

    int colorCounter = 0;

    for (int node = 1; node <= N; ++node) {
        int root = uf.find(node);

        // assegno il colore del cluster
        if (colorIndex[root] == -1) {
            colorIndex[root] = colorCounter % numColors;
            colorCounter++;
        }

        out << "    " << node << " [label=\"" << capoluoghi[node] << "\" fillcolor=\"" << palette[colorIndex[root]] << "\"];" << std::endl;
    }

    delete[] colorIndex;

    current = MST->head;
    i = 0;

    while (current != nullptr) {
        out << "    " << current->data->raw << " -- " << current->data->column;

        if (i < numRedEdges)
            out << " [label=\"" << current->data->weight << "\", color=\"red\", style=\"dashed\", penwidth=2.0];" << std::endl;
        else
            out << " [label=\"" << current->data->weight << "\", color=\"black\", penwidth=1.0];" << std::endl;

        current = current->next;
        ++i;
    }

    out << "}" << std::endl;
    out.close();
    std::cout << "File " << nomeFile << " generato correttamente con cluster colorati!" << std::endl;
}

int main() {

    const char* filename = "distanze_linea_aria_capoluoghi_con_id.csv";

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Errore apertura file\n";
        return 1;
    }

    const int N = 107; // numero capoluoghi

    // allocazione matrice 2D dinamica
    float** dist = new float*[N + 1];
    capoluoghi = new std::string[N + 1];

    for (int i = 0; i <= N; ++i) {
        dist[i] = new float[N + 1];
        for (int j = 0; j <= N; ++j)
            dist[i][j] = 0.0f;
    }

    std::string line;
    std::getline(file, line); // salta intestazione

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;

        int origine_id = 0;
        int destinazione_id = 0;
        float km = 0.0f;

        std::getline(ss, field, ',');
        origine_id = std::stoi(field);

        std::getline(ss, field, ',');
        destinazione_id = std::stoi(field);

        // salta origine_capoluogo
        std::getline(ss, field, ',');
        capoluoghi[origine_id] = field;

        // salta destinazione_capoluogo
        std::getline(ss, field, ',');

        // distanza km
        std::getline(ss, field, ',');
        km = std::stof(field);

        dist[origine_id][destinazione_id] = km;
        dist[destinazione_id][origine_id] = km;
    }

    capoluoghi[22] = "Carbonia"; // siccome viene saltato

//    // esempio accesso
//    std::cout << "Distanza 1 -> 2: " << dist[0][0] << " km\n";

    auto mst = kruskal(dist, N);
//    for (int i = 1; i <= N; ++i)
//        std::cout << "ID: " << i << ", nome: " << capoluoghi[i] << std::endl;

    /// Chimando Kruskal otteniamo l'MST che collega tuti i capolugohi dell'italia
    /// e rimuovendo gli ultimi 4 nodi otteniamo i 3 cluster principali dell'italia
    /// che sono quasi esattamente la penisola e le due isole.
    /// Questo ci fa capire che gli ultimi nodi sono esattamente i capoluoghi piu' distanti
    doGraphMST(mst, N, 3, "cluster-3.dot");

    /// TEST con 10 cluster e si deduce che i cluster man mano che vengono creati
    /// formano le regioni partendo dal sud
    doGraphMST(mst, N, 20, "cluster-20.dot");

    // deallocazione
    for (int i = 0; i <= N; ++i)
        delete[] dist[i];
    delete[] dist;

    return 0;
}

list_t* kruskal(float** g, int n) {

    /// Min-heap per l'inserimento dei pesi in ordine decrescente
    auto Q = new heap_t(n * n);
    /// Cluster gestiti con la union-find
    auto P = new union_t(n);

    /// Minimum Spanning Tree finale
    auto MST = new list_t;
    for (int i = 0; i < n; ++i) {
        P->add(i);
    }

    /// da cnon dimneticare, la prima posizione e' nulla in qunato non
    /// c'e' nessuna citta' con id 0

    /// Crazione del min heap
    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= n; ++c) {
            if (r == c)
                continue;
            Q->push(r, c, g[r][c]);
        }
    }

    int count = 0;
    while (!Q->isEmpty()) {
        auto e = Q->pop();
        auto findRaw = P->find(e->raw);
        auto findCol = P->find(e->column);

        if (findRaw != findCol) {
            MST->push(new edge_t(e->raw, e->column, e->weight));
            P->unione(findRaw, findCol);
            ++count;
        }
    }

//    Q->doGraph("min-heap-capoluoghi.dot");
//    P->doGraph("union-find.dot");

    return MST;
}