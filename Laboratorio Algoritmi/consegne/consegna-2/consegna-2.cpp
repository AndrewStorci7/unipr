#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include <random>

#define PATH_TO_STORE_DOTFILE "albero.dot"
#define MAX_IT 100

/**
 * @author: Andrea Storci
 * @date:   2026/05/06
 */

int cnt_it = 0; // variabile utilizzata per verificare che la funzione isBalanced sia O(n)
//int cnt_read = 0;

//enum PARSE_CODES {
//    NOTHING = 0,
//    T_RND = 1,
//    GRAPH = 2,
//    T_COMPLETE = 4,
//    T_BALANCED = 10,
//    R_A_G = T_RND + GRAPH,
//    C_A_G = T_COMPLETE + GRAPH,
//    B_A_G = T_BALANCED + GRAPH,
//};

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
int isBalancedAux(btree_t* tree, node_t* node);

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
int lowestCommonAncestor(btree_t* tree, int data1, int data2);
node_t* lowestCommonAncestorAux(node_t* node, int data1, int data2);

struct node {
    int data;
    node_t* right = nullptr;
    node_t* left = nullptr;
    int level = 0; // livello del nodo rispetto ad un albero

    node() : data(), level(0), right(nullptr), left(nullptr) {};
    node(int data, int level) : data(data), level(level), right(nullptr), left(nullptr) {};
    node(int data, node_t* l, node_t* r) : data(data), right(r), left(l) {};

    bool isLeaf() {
        return this->right == nullptr && this->left == nullptr;
    }

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
        auto new_node = new queue_node(data);

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
    node_t* addRight(node_t* node, int data) {
        if (node->hasRight())
            throw std::invalid_argument("il nodo ha gia' un figlio destro");

        auto new_node = new node_t(data, node->level + 1);

        node->right = new_node;
        ++this->size;

        return new_node;
    }

    /// @brief Funzione ricosriva di aggiunta di un nuovo dato a destra
    /// @param data Nuovo dato da aggiugnere all'albero
    node_t* addLeft(node_t* node, int data) {
        if (node->hasLeft())
            throw std::invalid_argument("il nodo ha gia' un figlio sinistro");

        auto new_node = new node_t(data, node->level + 1);

        node->left = new_node;
        ++this->size;

        return new_node;
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

    { /// Albero completo e bilanciato
        auto root = new node_t(14, 0);
        auto tree = new btree_t(root);
        auto r1 = tree->addRight(root, 45);
        auto l1 = tree->addLeft(root, 12);

        // aggiunta L e R al primo nodo destro
        auto r2 = tree->addRight(r1, 45);
        auto l2 = tree->addLeft(r1, 12);

        // aggiunta L e R al primo nodo sinistro
        auto r3 = tree->addRight(l1, 67);
        auto l3 = tree->addLeft(l1, 98);

        // aggiunta L e R al primo nodo destro
        auto r4 = tree->addRight(r2, 6);
        auto l4 = tree->addLeft(r2, 44);

        // aggiunta L e R al primo nodo sinistro
        auto r5 = tree->addRight(l2, 13);
        auto l5 = tree->addLeft(l2, 52);

        // aggiunta L e R al primo nodo destro
        tree->addRight(r3, 38);
        tree->addLeft(r3, 33);

        // aggiunta L e R al primo nodo sinistro
        tree->addRight(l3, 23);
        tree->addLeft(l3, 32);

        /// TEST calcolo LCA
        auto lca = lowestCommonAncestor(tree, 23, 33);
        assert(lca == 12);
        auto lca2 = lowestCommonAncestor(tree, 32, 100);
        assert(lca2 == 32);

        /// TEST calcolo isCompelte
        auto complete = isComplete(tree);
        assert(complete == true);

        /// TEST calcolo isBalanced
        auto balanced = isBalanced(tree);
        assert(balanced == true);
//        std::cout << "Count: " << cnt_it << "; " << tree->getSize() << std::endl;
        assert(cnt_it <= tree->getSize());

        /// TEST calcolo profondita'
        auto depth32 = calcDepth(tree, 32);
        assert(depth32 == 3);
        auto depth67 = calcDepth(tree, 67);
        assert(depth67 == 2);
        auto depthNIL = calcDepth(tree, 0);
        assert(depthNIL == -1);

        /// TEST calcolo altezza
        auto heightL3 = calcHeight(tree, l3);
        assert(heightL3 == 1);
        auto heightR1 = calcHeight(tree, r1);
        assert(heightR1 == 2);
        auto heightNIL = calcHeight(tree, nullptr);
        assert(heightNIL == -1);

        tree->do_graph("albero-bilanciato-completo.dot");

        flipTree(tree);
        tree->do_graph("albero-bilanciato-completo-flipped.dot");
    }

    { /// Albero bilanciato
        auto root = new node_t(14, 0);
        auto tree = new btree_t(root);
        auto r1 = tree->addRight(root, 45);
        auto l1 = tree->addLeft(root, 12);

        // aggiunta L e R al primo nodo destro
        auto r2 = tree->addRight(r1, 45);
        auto l2 = tree->addLeft(r1, 12);

        // aggiunta L e R al primo nodo sinistro
        auto r3 = tree->addRight(l1, 67);
        auto l3 = tree->addLeft(l1, 98);

        // aggiunta L e R al primo nodo destro
        auto r4 = tree->addRight(r2, 6);
        auto l4 = tree->addLeft(r2, 44);

        // aggiunta L e R al primo nodo destro
        tree->addRight(r3, 38);
        tree->addLeft(r3, 33);

        // aggiunta L e R al primo nodo sinistro
        tree->addRight(l3, 23);
        tree->addLeft(l3, 32);

        auto lca = lowestCommonAncestor(tree, 23, 33);
        assert(lca == 12);

        auto lca2 = lowestCommonAncestor(tree, 32, 100);
        assert(lca2 == 32);

        auto complete = isComplete(tree);
        assert(complete == false);

        auto balanced = isBalanced(tree);
        assert(balanced == true);
//        std::cout << "Count: " << cnt_it << "; " << tree->getSize() << std::endl;
        assert(cnt_it <= tree->getSize());

        tree->do_graph("albero-bilanciato.dot");

        flipTree(tree);
        tree->do_graph("albero-bilanciato-flipped.dot");
    }

    { /// Albero random
        const int MAX_VALUES = 30;
        // int pc = parseArguments(argc, argv);

        auto* root = new node_t(80, 0);
        auto* tree = new btree_t(root);

        insert_random_rec(tree, tree->getRoot(), MAX_VALUES);

        tree->do_graph("albero-random.dot");

        auto complete = isComplete(tree);
        // assert(complete == false);

        auto balanced = isBalanced(tree);
        assert(cnt_it <= tree->getSize());
        // assert(balanced == false);

    }

    exit(0);
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
//    cnt_read = 0;

    if (tree->getSize() <= 0)
        return true;

    return isBalancedAux(tree, tree->getRoot()) != -1;
}

int isBalancedAux(btree_t* tree, node_t* node) {
    ++cnt_it;
    if (node == nullptr)
        return 0;

    int hLeft = 0, hRight = 0;

    if (node->hasLeft())
        hLeft = calcHeight(tree, node->left);
    if (node->hasRight())
        hRight = calcHeight(tree, node->right);

    if (hLeft == -1 || hRight == -1)
        return -1;

    if (std::abs(hLeft - hRight) > 1)
        return -1;

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

    int leftDepth = calcDepthAux(node->left, data);
    if (leftDepth != -1)
        return leftDepth;

    return calcDepthAux(node->right, data);
}

int lowestCommonAncestor(btree_t* tree, int data1, int data2) {
    if (tree->getSize() <= 1)
        return -1;

    node_t* ancestorFound = lowestCommonAncestorAux(tree->getRoot(), data1, data2);

    if (ancestorFound != nullptr)
        return ancestorFound->data;

    return -1;
}

node_t* lowestCommonAncestorAux(node_t* node, int data1, int data2) {
    if (node == nullptr)
        return nullptr;

    if (node->data == data1 || node->data == data2)
        return node;

    node_t* left = lowestCommonAncestorAux(node->left, data1, data2);
    node_t* right = lowestCommonAncestorAux(node->right, data1, data2);

    if (left != nullptr && right != nullptr)
        return node;

    return (left != nullptr) ? left : right;
}