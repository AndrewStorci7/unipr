#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include <random>

#define PATH_TO_STORE_DOTFILE "albero.dot"
#define MAX_IT 100

/**
 * @author: Andrea Storci
 * @date:   2026/04/06
 *
 * @brief   Documentazione Consegna 2
 *
 * v2:
 *  Fino ad'ora e' stato utilizzato un albero binario
 *
 * @usage
 * Utilizzo: ./consegna-2 [option]
 *
 * Opzioni:
 *  -g: stampa il file .dot dell'albero
 *  -random/-complete:
 *      -random: crea un albero con valori causali
 *      -complete: crea un albero con dei valori di default (da 1 a 15) che formano un albero completo
 *
 * Attenzione: -random e -complete sono mutuamente esclusivi
 */

int cnt_it = 0; // variabile utilizzata per verificare che la funzione isBalanced sia O(n)
int cnt_read = 0;

enum PARSE_CODES {
    NOTHING = 0,
    T_RND = 1,
    GRAPH = 2,
    T_COMPLETE = 4,
    T_BALANCED = 10,
    R_A_G = T_RND + GRAPH,
    C_A_G = T_COMPLETE + GRAPH,
    B_A_G = T_BALANCED + GRAPH,
};

class binary_tree;
typedef class binary_tree btree_t;

struct node;
typedef struct node node_t;

struct queue;
typedef struct queue queue_t;

struct queue_node;
typedef struct queue_node qnode_t;

/// @brief funzione che determina se un l'albero passato comke parametro e' completo o meno
/// @return true se e' l'albero e' compelto, false altrimenti
bool isComplete(btree_t* tree);
bool isCompleteAux(node_t* node, int height);

/// @brief Calcola se l'albero passato come parametro e' bilanciato o meno
/// la funzione ricorsiva invece ritorna il valore della differenza tra il livello dei due figli trovati,
/// se la differenza è minore o uguale a 1 allora l'albero è bilanciato, altrimento no.
/// @param tree Albero binario
/// @return true se l'albero e' bilanciato, false altrimenti
bool isBalanced(btree_t* tree);
bool isBalancedAux(btree_t* tree, node_t* node);

/// @brief Algoritmo BFS per la ricerca di un nodo
/// @return true se il dato e'xpresente, false altrimenti
bool bfs(btree_t* tree, int data);

/// @brief funzione ricorsiva per flippare un albero
/// @return niente, siccome flippo l'albero sul posto
void flipTree(btree_t* tree);
void flipTreeAux(node_t* node);

/// @brief Calcola la profondita' di un nodo passato come parametro
/// @param data Nodo dal quale calcolare la profondita'
/// @return la profondita' di un certo nodo
int calcDepth(btree_t* tree, int data);
int calcDepthAux(node_t* node, int data);

/// @brief Calcola l'altezza del sottoalbero di un ndod passato come parametro
/// @param data Nodo dal quale calcolare l'altezza
/// @return l'altezza del sotoalbero del nodo
int calcHeight(btree_t* tree, node_t* data);
int calcHeightAux(node_t* node);

/// @brief dati due valori presenti nell'albero, restituisce il valore del nodo piu' basso che
/// contiene entrambi nel suo sottoalbero
/// @return il piu' piccolo nodo che gli contiene
node_t* lowestCommonAncestor(btree_t* tree, int data1, int data2);
node_t* lowestCommonAncestorAux(node_t* node, int data1, int data2);

struct node {
    int data;
    // node_t* father = nullptr;
    node_t* right = nullptr;
    node_t* left = nullptr;
//    int count = 0; // numero di occorrenze
    // int height = 0; // altezza del nodo rispetto ad un albero
    int level = 0; // livello del nodo rispetto ad un albero

//    node() : data(), father(nullptr), right(nullptr), left(nullptr), count(0) {};
//    node(int data) : data(data), father(nullptr), right(nullptr), left(nullptr), count(1) {};
//    node(int data, node_t* f, node_t* l, node_t* r) : data(data), father(f), right(r), left(l), count(1) {};
    node() : data(), level(0), right(nullptr), left(nullptr) {};
    node(int data, int level) : data(data), level(level), right(nullptr), left(nullptr) {};
    node(int data, node_t* l, node_t* r) : data(data), right(r), left(l) {};

    bool isLeaf() {
        return this->right == nullptr && this->left == nullptr;
    }

//    bool hasFather() {
//        return this->father != nullptr;
//    }

    bool hasRight() {
        return this->right != nullptr;
    }

    bool hasLeft() {
        return this->left != nullptr;
    }

    bool isComplete() {
        return this->hasRight() && this->hasLeft();
    }
};

struct queue_node {
    node_t* data;
    qnode_t* next = nullptr;

    queue_node(): data(), next(nullptr) {}
    queue_node(node_t* data): data(data), next(nullptr) {}

    bool hasNext() {
        return this->next != nullptr;
    }
};

struct queue {
    qnode_t* head = nullptr;
    qnode_t* tail = nullptr;
    size_t size = 0;

    queue(): head(nullptr) {}

    void push(node_t* data) {
        auto new_node = new qnode_t(data);

        if (this->head == nullptr) {
            this->head = this->tail = new_node;
        } else {
            this->tail->next = new_node;
            this->tail = new_node;
        }
        ++size;
    }

    node_t* pop() {
        if (this->head == nullptr)
            return nullptr;

        auto temp = this->head;
        node_t* ret = temp->data;

        this->head = this->head->next;

        if (this->head == nullptr) {
            this->tail = nullptr;
        }

        delete temp;
        --size;
        return ret;
    }

    void print() {
        auto current = head;

        while (current->hasNext()) {
            node_t* n = current->data;
            std::cout << n->data << ", ";
            current = current->next;
        }
        std::cout << current->data->data << std::endl;
    }

//    bool find(node_t* node) {
//        auto current = head;
//
//        while (current != nullptr) {
//            if (current->data == node)
//                return true;
//            current = current->next;
//        }
//
//        return false;
//    }

    bool isEmpty() {
        return this->size == 0;
    }
};

class binary_tree {
private:
    node_t* root;
    size_t size;

    void writeDotRecursive(node_t* node, std::ofstream& out) {
        if (node == nullptr)
            return;

        out << "    \"" << node << "\" [label=\"" << node->data << " (lvl: " << node->level << ")" << "\"];\n";

        if (node->left != nullptr) {
            out << "    \"" << node << "\" -> \"" << node->left << "\";\n";
            writeDotRecursive(node->left, out);
        }

        if (node->right != nullptr) {
            out << "    \"" << node << "\" -> \"" << node->right << "\";\n";
            writeDotRecursive(node->right, out);
        }
    }

public:

    binary_tree() {
        this->root = nullptr;
        this->size = 0;
    }

    binary_tree(node_t* root) {
        this->root = root;
        this->size = 1;
    }

    node_t* getRoot() {
        return this->root;
    }

    size_t getSize() const {
        return this->size;
    }

    /// @brief Funzione ricosriva di aggiunta di un nuovo dato a destra
    /// @param data Nuovo dato da aggiugnere all'albero
    void addRight(node_t* node, int data) {
        if (node->hasRight())
            throw std::invalid_argument("il nodo ha gia' un figlio destro");

        auto new_node = new node_t(data, node->level + 1);

        node->right = new_node;
        ++this->size;
    }

    /// @brief Funzione ricosriva di aggiunta di un nuovo dato a destra
    /// @param data Nuovo dato da aggiugnere all'albero
    void addLeft(node_t* node, int data) {
        if (node->hasLeft())
            throw std::invalid_argument("il nodo ha gia' un figlio sinistro");

        auto new_node = new node_t(data, node->level + 1);

        node->left = new_node;
        ++this->size;
    }

    /// @brief Crea il grafico visivo dell'albero e lo stampa in un file .dot
    /// @param filename
    void do_graph(const std::string& filename = PATH_TO_STORE_DOTFILE) {
        std::ofstream out(filename);

        if (!out.is_open()) {
            std::cerr << "Errore: Impossibile creare il file " << filename << std::endl;
            return;
        }

        out << "digraph Albero {\n";
        out << "    node [fontname=\"Helvetica\", shape=circle];\n";

        if (this->root == nullptr)
            out << "    vuoto [label=\"Albero vuoto\", shape=none];\n";
        else
            writeDotRecursive(this->root, out);

        out << "}\n";
        out.close();

        std::cout << "File '" << filename << "' generato con successo!" << std::endl;
    }
};

///
/// @param argc
/// @param argv
/// @return uno dei codici di PARSE_CODES
int parseArguments(int argc, char* argv[]) {
    if (argc < 1)
        return NOTHING;

    int code = NOTHING;
    bool typeAlreadySet = false;

    for (int i = 1; i < argc; ++i) {
        if (argv[i] == nullptr)
            continue;

        if (strcmp(argv[i], "-random") == 0 || strcmp(argv[i], "-complete") == 0 || strcmp(argv[i], "-balanced") == 0) {
            if (typeAlreadySet)
                std::cerr << "Errore: Non puoi utilizzare '-random' e '-complete' insieme!" << std::endl;
            else {
                if (strcmp(argv[i], "-random") == 0)
                    code += T_RND;
                else if (strcmp(argv[i], "-balanced") == 0)
                    code += T_BALANCED;
                else
                    code += T_COMPLETE;

                typeAlreadySet = true;
            }
        } else if (strcmp(argv[i], "-g") == 0) {
            code += GRAPH;
        } else if (strcmp(argv[i], "-h") == 0) {
            std::cout << "Utilizzo: ./consegna-2 [option]\n"
                         "\n"
                         "Opzioni:\n"
                         "\t-g: stampa il file .dot dell'albero\n"
                         "\t-random/-complete:\n"
                         "\t\t-random: crea un albero con valori causali\n"
                         "\t\t-complete: crea un albero con dei valori di default (da 1 a 15) che formano un albero completo\n"
                         "\n"
                         "Attenzione: -random e -complete sono mutuamente esclusivi" << std::endl;
            exit(0);
        }
        else
            std::cerr << "Argomento sconosciuto: " << argv[i] << std::endl;
    }

    return code;
}

int size = 0;

void insert_random_rec(btree_t* tree, node_t *n, const int max_it = MAX_IT) {

    if (size >= max_it)
        return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);

    float probabilita = 0.6; /// tra 0 e 1

    if (float(distrib(gen)) < probabilita * 100) { // se numero random e' minore della probabilita' -> aggiungo nodo R con valore a caso
        ++size;
        tree->addRight(n, distrib(gen));
    }
    if (float(distrib(gen)) < probabilita * 100) { // se numero random e' minore della probabilita' -> aggiungo nodo L con valore a caso
        ++size;
        tree->addLeft(n, distrib(gen));
    }

    if (n->hasLeft())
        insert_random_rec(tree, n->left, max_it);
    if (n->hasRight())
        insert_random_rec(tree, n->right, max_it);
}

int main(int argc, char* argv[]) {


    const int MAX_VALUES = 30;
    int pc = parseArguments(argc, argv);

    auto* root = new node_t(80, 0);
    auto* tree = new btree_t(root);

    insert_random_rec(tree, tree->getRoot(), MAX_VALUES);

    std::cout << "Dimensione albero: " << tree->getSize() << std::endl;

    std::cout << bfs(tree, 23) << std::endl;

    if (pc == GRAPH)
        tree->do_graph();

    /// 1) calcolo altezza e profondita'
    std::cout << "Altezza albero partendo dal nodo radice: " << calcHeight(tree, tree->getRoot()) << std::endl;
//    assert(tree->calcHeight(tree->getRoot()->data) == 3);
    std::cout << "Altezza albero partendo dal nodo (12): " << calcHeight(tree, new node) << std::endl;
//    assert(tree->calcHeight(12) == 2);

    std::cout << "------" << std::endl;

    std::cout << "Profondita' albero partendo dal nodo radice: " << calcDepth(tree, tree->getRoot()->data) << std::endl;
//    assert(tree->calcDepth(tree->getRoot()->data) == 0);
    std::cout << "Profondita' albero partendo dal nodo (12): " << calcDepth(tree, 12) << std::endl;
//    assert(tree->calcDepth(12) == 1);

    /// 2) vedere se un albero e' compelto
    std::cout << "L'albero e' completo ? " << (isComplete(tree) ? "Si" : "No") << std::endl;
//    assert((pc == T_COMPLETE || pc == C_A_G) ? isComplete(tree) : true);

    /// 3) vedere se un albero e' bilanciato
    std::cout << "L'albero e' bilanciato ? " << (isBalanced(tree) ? "Si" : "No") << std::endl;
//    std::cout << "Conteggio iterazioni: " << cnt_it << ", n=" << MAX_VALUES << std::endl;
//    assert((pc == T_COMPLETE || pc == C_A_G) ? isBalanced(tree) : true);
//    assert((pc == T_RND || pc == R_A_G) ? cnt_it < 31 : true);
    // assert((pc == T_COMPLETE || pc == C_A_G) ? cnt_it < 16 : true);

    /// 4) Lowest Common Ancestor TEST
    // auto lca = lowestCommonAncestor(tree, 23, 29);
    int val1 = 86, val2 = 71;
    auto lca = lowestCommonAncestor(tree, val1, val2);
    std::cout << "Lowest Common Ancestor di (" << val1 << ") e (" << val2 << "): "
        << (lca != nullptr ? lca->data : -1) << std::endl;

    flipTree(tree);
    if (pc == GRAPH)
        tree->do_graph("albero-flipped.dot");

    return 0;
}

bool isComplete(btree_t* t) {
    if (t->getSize() <= 1)
        return true;

    int height = calcHeight(t, t->getRoot());

    return isCompleteAux(t->getRoot(), height);
}

bool isCompleteAux(node_t* node, int h) {
    if (node->isLeaf())
        return node->level == h;

    if (!node->isComplete())
        return false;

    bool isCompleteLeft = isCompleteAux(node->left, h);
    bool isCompleteRight = isCompleteAux(node->right, h);

    return isCompleteLeft && isCompleteRight;
}

bool isBalanced(btree_t* tree) {
    cnt_it = 0;
    cnt_read = 0;

    if (tree->getSize() <= 0)
        return true;

    return isBalancedAux(tree, tree->getRoot());
}

bool isBalancedAux(btree_t* tree, node_t* node) {
    ++cnt_it;
    if (node == nullptr)
        return true;

    int hLeft = 0, hRight = 0;

    if (node->hasLeft())
        hLeft = calcHeight(tree, node->left);
    if (node->hasRight())
        hRight = calcHeight(tree, node->right);

    if (std::abs(hLeft - hRight) > 1)
        return false;

    return isBalancedAux(tree, node->left) && isBalancedAux(tree, node->right);
}

bool bfs(btree_t* tree, int data) {
    if (tree->getSize() == 0)
        return false;

    auto q = new queue_t();
    auto node = tree->getRoot();
    q->push(node);

    while (!q->isEmpty()) {
        auto v = q->pop();
        if (v->data == data)
            return true;
        if (v->hasLeft())
            q->push(v->left);
        if (v->hasRight())
            q->push(v->right);
        ++cnt_it;
    }

    delete q;

    return false;
}

void flipTree(btree_t* tree) {
    if (tree->getSize() <= 1)
        return;

    flipTreeAux(tree->getRoot());
}

void flipTreeAux(node_t* node) {
    if (node->isLeaf())
        return;

    node_t* tmp = node->left;
    node->left = node->right;
    node->right = tmp;

    if (node->hasLeft())
        flipTreeAux(node->left);
    if (node->hasRight())
        flipTreeAux(node->right);
}

int calcHeight(btree_t* tree, node_t* data) {
    if (tree->getSize() == 0)
        return -2;

    return calcHeightAux(data);
}

int calcHeightAux(node_t* node) {
    if (node == nullptr)
        return -1;

    int left = calcHeightAux(node->left);
    int right = calcHeightAux(node->right);

    return 1 + std::max(left, right);
}

int calcDepth(btree_t* tree, int data) {
    if (tree->getSize() == 0)
        return -1;

    return calcDepthAux(tree->getRoot(), data);
}

int calcDepthAux(node_t* node, int data) {
    if (node == nullptr)
        return -1;

    if (node->data == data)
        return node->level;

    if (node->hasLeft())
        return calcDepthAux(node->left, data);
    if (node->hasRight())
        return calcDepthAux(node->right, data);
}

node_t* lowestCommonAncestor(btree_t* tree, int data1, int data2) {
    if (tree->getSize() <= 1)
        return nullptr;

    // di default: siccome utilizzo gli alberi binari di ricerca
    // vado ad impostare sempre il primo elemento della chiamata ricorsiva
    // l'elemento più piccolo
//    if (binarySearch(tree, data1) == nullptr ||
//        binarySearch(tree, data2) == nullptr)
//        return nullptr;

    auto firstNode = data1 > data2 ? data2 : data1;
    auto secondNode = data1 > data2 ? data1 : data2;

    return lowestCommonAncestorAux(tree->getRoot(), firstNode, secondNode);
}

/// Idea: ogni volta controllo se data1 e data2 sono minori del nodo corrente
/// se sono tutti e due più piccoli significa che si trovano all'interno del sottoalbero
/// (lo do per socntato perché prima di entrare nella funzione ricorsiva controlo che i due dati
/// passati come parametro esistano all'interno dell'albero); se invece anche solo uno dei due dati
/// è più grande allora significa che non sono più nel sottoalbero che gli contiene
node_t* lowestCommonAncestorAux(node_t* node, int data1, int data2) {

    if (node->isLeaf() && (data1 != node->data || data2 != node->data))
        return nullptr;

    if (data1 < node->data && data2 > node->data)
        return node;

    if (data1 < node->data && data2 < node->data)
        return lowestCommonAncestorAux(node->left, data1, data2);
    else if (data1 > node->data && data2 > node->data)
        return lowestCommonAncestorAux(node->right, data1, data2);
}