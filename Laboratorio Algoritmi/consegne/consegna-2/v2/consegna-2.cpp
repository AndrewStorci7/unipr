#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include <random>

#define PATH_TO_STORE_DOTFILE "albero.dot"

/**
 * @author: Andrea Storci
 * @date:   2026/04/06
 *
 * @brief   Documentazione Consegna 2
 *
 *  Ho utilizzato la struttura degli alberi binari sfruttando le proprietà degli alberi binari di ricerca (BST).
 *  La motivazione è semplicemente per comodità, in quanto l'aggiunta di un nuovo nodo si può fare tranquilamente
 *  con un array e un semplice ciclo for.
 *  Inoltre un BST risulta molto più efficiente e veloce per il calcolo del Lowest Common Ancestor, siccome sfrutto
 *  la sua proprietà più forte che è quella di avere per tutti i sottoalberi i nodi a sinistra più piccoli del nodo padre
 *  e a destra quelli più grandi; questo mi permette di sapere con anticipo se il LCA si trova nel sottoalbero sinstro o
 *  in quello destro.
 *  Un altro vantaggio che mi porta il BST è quello della ricerca binaria, tantè che nel seguente codice
 *  viene sfruttato per controllare che un certo dato sia presente nell'albero in una complessità temporale ragionevole.
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

int cnt_complexity = 0; // variabile utilizzata per verificare che la funzione isBalanced sia O(n)

enum PARSE_CODES {
    NOTHING = 0,
    T_RND = 1,
    GRAPH = 2,
    T_CMPLTE = 4,
    R_A_G = T_RND + GRAPH,
    C_A_G = T_CMPLTE + GRAPH
};

class binary_t;
typedef class binary_t btree_t;

struct node;
typedef struct node node_t;

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
int isBalancedAux(node_t* node);

/// @brief funzione ricorsiva per il binary-search
/// @return ritorna il puntatore all'oggetto trovato con quel dato, nullptr altrimenti
node_t* binarySearch(btree_t* tree, int data);
node_t* binarySearchAux(node_t* node, int data);

/// @brief funzione ricorsiva per flippare un albero
/// @return niente, siccome flippo l'albero sul posto
void flipTree(btree_t* tree);
void flipTreeAux(node_t* node);

/// @brief dati due valori presenti nell'albero, restituisce il valore del nodo piu' basso che
/// contiene entrambi nel suo sottoalbero
/// @return il piu' piccolo nodo che gli contiene
node_t* lowestCommonAncestor(btree_t* tree, int data1, int data2);
node_t* lowestCommonAncestorAux(node_t* node, int data1, int data2);

struct node {
    int data;
    node_t* father = nullptr;
    node_t* right = nullptr;
    node_t* left = nullptr;
    int count = 0; // numero di occorrenze
    int height = 0; // altezza del nodo rispetto ad un albero
    int level = 0; // livello del nodo rispetto ad un albero

    node() : data(), father(nullptr), right(nullptr), left(nullptr), count(0) {};
    node(int data) : data(data), father(nullptr), right(nullptr), left(nullptr), count(1) {};
    node(int data, node_t* f, node_t* l, node_t* r) : data(data), father(f), right(r), left(l), count(1) {};

    bool isLeaf() {
        return this->right == nullptr && this->left == nullptr;
    }

    bool hasFather() {
        return this->father != nullptr;
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

class binary_t {
private:
    node_t* root;
    int size;

    void addAux(node_t* father, node_t* &current, int data, int level) {
        if (current == nullptr) {
            current = new node_t(data, father, nullptr, nullptr);
            current->level = level;
            return;
        }

        assert(current != nullptr);
        if (data < current->data)
            addAux(current, current->left, data, level + 1);
        else
            addAux(current, current->right, data, level + 1);
    }

    void writeDotRecursive(node_t* node, std::ofstream& out) {
        if (node == nullptr)
            return;

        // out << "    \"" << node << "\" [style=filled fillcolor=red label=\"" << node->data << " (lvl: " << node->level << ")" << "\"];\n";
        out << "    \"" << node << "\" [label=\"" << node->data << " (lvl: " << node->level << ")" << "\"];\n";

        if (node->left != nullptr) {
            // out << "    \"" << node << "\" [style=filled fillcolor=green label=\"" << node->data << " (lvl: " << node->level << ")" << "\"];\n";
            out << "    \"" << node << "\" -> \"" << node->left << "\";\n";
            writeDotRecursive(node->left, out);
        }

        if (node->right != nullptr) {
            // out << "    \"" << node << "\" [style=filled fillcolor=red label=\"" << node->data << " (lvl: " << node->level << ")" << "\"];\n";
            out << "    \"" << node << "\" -> \"" << node->right << "\";\n";
            writeDotRecursive(node->right, out);
        }

        if (node->father != nullptr) {
            out << "    \"" << node << "\" -> \"" << node->father << "\";\n";
        }
    }

    int calcHeightAux(node_t* node) {
        if (node == nullptr)
            return -1;

        int hLeft = calcHeightAux(node->left);
        int hRight = calcHeightAux(node->right);

        return 1 + std::max(hLeft, hRight);
    }

public:

    binary_t() {
        this->root = nullptr;
        this->size = 0;
    }

    binary_t(node_t* root) {
        this->root = root;
        this->size = 1;
    }

    node_t* getRoot() {
        return this->root;
    }

    int getSize() const {
        return this->size;
    }

    /// @brief Funzione ricosriva di aggiunta di un nuovo dato,
    /// Regole di aggiunta:
    ///     - filgio Sinistro: dato < del dato Padre
    ///     - figlio Destro: dato > del dato Padre
    ///     - i dati gia' presenti nell'albero vengono contati al'interno di ogni nodo
    /// @param data Nuovo dato da aggiugnere all'albero
    void add(int data) {
        auto new_node = new node_t(data, nullptr, nullptr, nullptr);

        if (this->root == nullptr) {
            this->root = new_node;
            ++this->size;
            return;
        }

        // controllo se e' gia' presente il dato,
        // che nel caso incremento il suo contatore interno
        node_t* check = binarySearch(this, data);
        if (check != nullptr) {
            ++check->count;
            return;
        }

        assert(this->root != nullptr);

        // aggiungo in maniera ricorsiva
        this->addAux(nullptr, this->root, data, 0);

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

    /// @brief Calcola l'altezza del sottoalbero di un ndod passato come parametro
    /// @param data Nodo dal quale calcolare l'altezza
    /// @return l'altezza del sotoalbero del nodo
    int calcHeight(int data) {
        if (this->size == 0)
            return -2;

        // controllo che il nodo passato come parametro esista nell'albero
        node_t* node = binarySearch(this, data);
        if (node == nullptr)
            return -1;

        return calcHeightAux(node);
    }

    /// @brief Calcola la profondita' di un nodo passato come parametro
    /// @param data Nodo dal quale calcolare la profondita'
    /// @return la profondita' di un certo nodo
    int calcDepth(int data) {
        if (this->size == 0)
            return 0;

        // controllo che il nodo passato come parametro esista nell'albero
        node_t* node = binarySearch(this, data);
        if (node == nullptr)
            return -1;

        return node->level;
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

        if (strcmp(argv[i], "-random") == 0 || strcmp(argv[i], "-complete") == 0) {
            if (typeAlreadySet)
                std::cerr << "Errore: Non puoi utilizzare '-random' e '-complete' insieme!" << std::endl;
            else {
                if (strcmp(argv[i], "-random") == 0)
                    code += T_RND;
                else
                    code += T_CMPLTE;

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

int main(int argc, char* argv[]) {

    int pc = parseArguments(argc, argv);

    // node_t* root = new node_t(5);
    auto tree = new btree_t();

    if (pc == T_RND || pc == R_A_G) { // albero random
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 100);
        int n = 30;
        for (int i = 0; i < n; ++i)
            tree->add(distrib(gen));
    } else if (pc == T_CMPLTE || pc == C_A_G) { // albero completo
        int values[] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15};
        for (int i = 0; i < 15; ++i)
            tree->add(values[i]);
    } else { // albero custom
        int MAX_VALUES = 30;
        int values[MAX_VALUES];
        int count = 0;

        std::cout << "Inserisci i numeri separati da una virgola (es. 1,2,3): ";
        while (count < MAX_VALUES) {
            if (!(std::cin >> values[count]))
                break;

            ++count;

            if (std::cin.peek() == ',' || std::cin.peek() == ' ')
                std::cin.ignore();

            if (std::cin.peek() == '\n')
                break;
        }

        for (int i = 0; i < MAX_VALUES; ++i)
            tree->add(values[i]);
    }

    if (pc == GRAPH || pc == C_A_G || pc == R_A_G)
        tree->do_graph();

    /// 1) calcolo altezza e profondita'
    if (pc == GRAPH || pc == C_A_G) {
        std::cout << "Altezza albero partendo dal nodo radice: " << tree->calcHeight(tree->getRoot()->data) << std::endl;
        assert(tree->calcHeight(tree->getRoot()->data) == 3);
        std::cout << "Altezza albero partendo dal nodo (12): " << tree->calcHeight(12) << std::endl;
        assert(tree->calcHeight(12) == 2);

        std::cout << "------" << std::endl;

        std::cout << "Profondita' albero partendo dal nodo radice: " << tree->calcDepth(tree->getRoot()->data) << std::endl;
        assert(tree->calcDepth(tree->getRoot()->data) == 0);
        std::cout << "Profondita' albero partendo dal nodo (12): " << tree->calcDepth(12) << std::endl;
        assert(tree->calcDepth(12) == 1);
    }

    /// 2) vedere se un albero e' compelto
    std::cout << "L'albero e' completo ? " << (isComplete(tree) ? "Si" : "No") << std::endl;
    assert((pc == T_CMPLTE || pc == C_A_G) ? isComplete(tree) : true);

    /// 3) vedere se un albero e' bilanciato
    std::cout << "L'albero e' bilanciato ? " << (isBalanced(tree) ? "Si" : "No") << std::endl;
    assert((pc == T_CMPLTE || pc == C_A_G) ? isBalanced(tree) : true);
    assert((pc == T_RND || pc == R_A_G) ? cnt_complexity < 31 : true);
    // assert((pc == T_CMPLTE || pc == C_A_G) ? cnt_complexity < 16 : true);

    /// 4) Lowest Common Ancestor TEST
    // auto lca = lowestCommonAncestor(tree, 23, 29);
    int val1 = 86, val2 = 71;
    auto lca = lowestCommonAncestor(tree, val1, val2);
    std::cout << "Lowest Common Ancestor di (" << val1 << ") e (" << val2 << "): " << (lca != nullptr ? lca->data : -1) << std::endl;

    flipTree(tree);
    if (pc == GRAPH || pc == C_A_G || pc == R_A_G)
        tree->do_graph("albero-flipped.dot");

    return 0;
}

bool isComplete(btree_t* t) {
    if (t->getSize() <= 1)
        return true;

    int height = t->calcHeight(t->getRoot()->data);

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
    if (tree->getSize() <= 0)
        return true;

    return isBalancedAux(tree->getRoot()) <= 1;
}

int isBalancedAux(node_t* node) {
    ++cnt_complexity;

    if (node->isLeaf())
        return node->level;

    int isBalancedLeft = 0;
    int isBalancedRight = 4;
    if (node->hasRight())
        isBalancedLeft = isBalancedAux(node->right);
    if (node->hasLeft())
        isBalancedRight = isBalancedAux(node->left);

    return abs(isBalancedLeft - isBalancedRight);
}

node_t* binarySearch(btree_t* tree, int data) {
    if (tree->getSize() == 0)
        return nullptr;

    return binarySearchAux(tree->getRoot(), data);
}

node_t* binarySearchAux(node_t* node, int data) {
    if (node->data == data)
        return node;

    if (node->isLeaf())
        return nullptr;

    if (node->hasRight() && data > node->data)
        return binarySearchAux(node->right, data);
    else if (node->hasLeft() && data < node->data)
        return binarySearchAux(node->left, data);
    else
        return nullptr;
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

node_t* lowestCommonAncestor(btree_t* tree, int data1, int data2) {
    if (tree->getSize() <= 1)
        return nullptr;

    // di default: siccome utilizzo gli alberi binari di ricerca
    // vado ad impostare sempre il primo elemento della chiamata ricorsiva
    // l'elemento più piccolo
    if (binarySearch(tree, data1) == nullptr ||
        binarySearch(tree, data2) == nullptr)
        return nullptr;

    auto firstNode = data1 > data2 ? data2 : data1;
    auto secondNode = data1 > data2 ? data1 : data2;

    return lowestCommonAncestorAux(tree->getRoot(), firstNode, secondNode);
}

/// TODO: da sistemare, non corretto
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