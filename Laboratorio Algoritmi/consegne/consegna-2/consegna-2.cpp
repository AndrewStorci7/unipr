#include <iostream>
#include <fstream>
#include <cstring>

extern class Albero;
typedef class Albero tree_t;

extern struct node;
typedef struct node node_t;

/// @brief funzione che determina se un l'albero passato comke parametro e' completo o meno
/// @return true se e' l'albero e' compelto, false altrimenti
bool isComplete(tree_t*);

/// @brief Ausiliaare per la funzione `isComplete`. Funzione ricorsiva
/// @return true se e' l'albero e' compelto, false altrimenti
bool isCompleteAux(tree_t*, node_t*, int);

struct node {
    int data;
    node* right = nullptr;
    node* left = nullptr;

    node() : data(), right(nullptr), left(nullptr) {};
    node(int data) : data(data), right(nullptr), left(nullptr) {};
    node(int data, node* l, node* r) : data(data), right(r), left(l) {};

    bool isLeaf() {
        return this->right == nullptr && this->left == nullptr;
    }
};

class Albero {
private:
    node_t* root;
    int size;

    void write_dot_recursive(node_t* node, std::ofstream& out) {
        if (node == nullptr) return;

        out << "    \"" << node << "\" [label=\"" << node->data << "\"];\n";

        if (node->left != nullptr) {
            out << "    \"" << node << "\" -> \"" << node->left << "\";\n";
            write_dot_recursive(node->left, out);
        }

        if (node->right != nullptr) {
            out << "    \"" << node << "\" -> \"" << node->right << "\";\n";
            write_dot_recursive(node->right, out);
        }
    }

public:

    Albero() {
        this->root = nullptr;
        int size = 0;
    }

    Albero(node_t* root) {
        this->root = root;
        this->size = 1;
    }

    void add(int data) {
        node_t* new_node = new node_t(data, nullptr, nullptr);

        if (this->root == nullptr) {
            this->root = new_node;
            ++this->size;
            return;
        }

        node_t* parent = nullptr;
        node_t* current = this->root;

        while (current != nullptr) {
            parent = current;
            if (data > current->data)
                current = current->right;
            else
                current = current->left;
        }

        if (data > parent->data)
            parent->right = new_node;
        else
            parent->left = new_node;

        ++this->size;
    }

    void do_graph(const std::string& filename = "albero.dot") {
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
            write_dot_recursive(this->root, out);

        out << "}\n";
        out.close();

        std::cout << "File '" << filename << "' generato con successo!" << std::endl;
    }

    node_t* getRoot() {
        return this->root;
    }
};

int main(int argc, char* argv[]) {

    node_t* root = new node_t(5);
    tree_t* tree = new tree_t(root);

    for (int i = 0; i < 10; ++i) {
        tree->add(rand() % 100);
    }

    if (argc > 1 && std::strcmp(argv[1], "-g") == 0)
        tree->do_graph();

    return 0;
}

/// @brief funzione che determina se un l'albero passato comke parametro e' completo o meno
/// @return true se e' l'albero e' compelto, false altrimenti
bool isComplete(tree_t* t) {
    return isCompleteAux(t, t->getRoot(), 0);
}

/// @brief Ausiliaare per la funzione `isComplete`. Funzione ricorsiva
/// @return true se e' l'albero e' compelto, false altrimenti
bool isCompleteAux(tree_t* t, node_t* node, int level) {

    /// TODO: capire come controllare che tutte le foglie si trovano sullo stesso livello.
    /// TODO: ho pensato di salvare in ogni nodo il valore del livello, ma sarebbe da gestire bene per ogni operazione
    if (!node->isLeaf() && (node->right == nullptr || node->left == nullptr))
        return false;

    if (node->isLeaf()) {

    }

    return
}