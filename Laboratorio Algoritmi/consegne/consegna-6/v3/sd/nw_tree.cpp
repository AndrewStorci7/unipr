//
// Created by sandr_ft5c0vu on 24/06/2026.
//

#include "../enums/enums.h"
#include "nw_tree.h"
#include <string>
#include <fstream>

std::string tostringAux(NWTreeNode* node, int depth);

/// NWTreeNode

NWTreeNode::NWTreeNode() {
	maxSize = 2;
	size = 0;
	father = nullptr;
	token = nullptr;
	childs = new NWTreeNode*[maxSize];
	// diffMatrix = new int*[0];

	for (int i = 0; i < maxSize; ++i)
		childs[i] = nullptr;

}

NWTreeNode::NWTreeNode(Token* t, NWTreeNode* father = nullptr) {
	maxSize = 2;
	size = 0;
	this->father = father;
	token = t;
	childs = new NWTreeNode*[maxSize];
	// diffMatrix = new int*[0];

	for (int i = 0; i < maxSize; ++i)
		childs[i] = nullptr;
}

NWTreeNode::~NWTreeNode() {
	for (int i = 0; i < size; ++i)
		delete[] childs[i];
	delete[] childs;
}

/// Funzione utilizzata per riallocare la memoria dinamica ogni
/// vola che si tenta di aggiugnere un nuovo figlio (ovveor un blocco)
/// con l'array pieno
void NWTreeNode::reallocChildren() {
	int newSize = 2 * maxSize;
	auto** newBlockChildren = new NWTreeNode*[newSize];

	for (int i = 0; i < size; ++i)
		newBlockChildren[i] = childs[i];

	delete[] childs;

	childs = newBlockChildren;
	maxSize = newSize;
}

void NWTreeNode::addFather(NWTreeNode* f) {
	this->father = f;
}

/// Funzione per aggiugnere un nuovo figlio
void NWTreeNode::addChild(NWTreeNode* child) {
	if (size >= maxSize)
		reallocChildren();

	if (child == nullptr)
		return;

	childs[size] = child;
	++size;
}

/// Metodo diretto per capire se  un nodo e' una folgia
bool NWTreeNode::isLeaf() const {
	return size == 0;
}

/// Helper ricorsivo per NWTreeNode
// void NWTreeNode::doGraphNode(std::ofstream& out) const {
// 	// Usiamo l'indirizzo di memoria del nodo come ID univoco per Graphviz
// 	uintptr_t nodeId = reinterpret_cast<uintptr_t>(this);
//
// 	// Risolviamo il nome (se vuoto, mettiamo una stringa di default)
// 	// std::string nodeName = (name[0] != '\0') ? name : "<anonimo>";
//
// 	std::string typeName = token != nullptr ? getTokenTypeName(token->key) : "GLOBAL";
// 	std::string valName = token != nullptr ? "'" + token->val + "'" : "";
// 	if (typeName == "STRING")
// 		valName = "String value";
//
// 	// Dichiarazione del nodo corrente con etichetta
// 	out << "    node_" << nodeId
// 		<< " [label=\"Type: " << typeName
// 		<< "\\nVal: " << valName;
//
// 	// Se c'è un contesto, possiamo aggiungerlo all'etichetta
// 	// if (context != nullptr && !context->val.empty()) {
// 	// 	out << "\\nCtx: " << context->val;
// 	// }
// 	out << "\"];\n";
//
// 	// Visitiamo i figli per creare gli archi (edges) e stampare i nodi ricorsivamente
// 	for (int i = 0; i < size; ++i) {
// 		if (childs[i] != nullptr) {
// 			uintptr_t childId = reinterpret_cast<uintptr_t>(childs[i]);
//
// 			// Crea il collegamento tra padre e figlio
// 			out << "    node_" << nodeId << " -> node_" << childId << ";\n";
//
// 			// Chiamata ricorsiva sul figlio
// 			childs[i]->doGraphNode(out);
// 		}
// 	}
// }

std::string NWTreeNode::tostring() const {
	std::string ret;

	ret = "Blocco {\n";

	// 2. Controllo sui token e chiamata senza argomenti
	if (this->token != nullptr) {
		ret += this->token->tostring("\t");
	}

	ret += "}\n";

	return ret;
}

/// END NWTreeNode

/// NWTree

NWTree::NWTree() {
	size = 0;
	root = nullptr;
}

int NWTree::getSize() const {
	return size;
}

void NWTree::addRoot(NWTreeNode* root) {
	if (root == nullptr)
		root = new NWTreeNode();

	this->root = root;
	++size;
}

NWTreeNode* NWTree::getRoot() const {
	return this->root;
}

/// Implementazione del metodo principale in NWTree
// void NWTree::doGraph(const std::string& filename) const {
// 	std::ofstream out(filename);
// 	if (!out.is_open()) {
// 		// Gestione base dell'errore se il file non può essere aperto
// 		return;
// 	}
//
// 	// Intestazione del file .dot
// 	out << "digraph NWTree {\n";
// 	out << "    node [shape=box, style=rounded, fontname=\"Helvetica\"];\n";
// 	out << "    edge [dir=none];\n"; // Rimuovi 'dir=none' se vuoi le frecce direzionali
//
// 	// Avvia la visita dall'albero se la radice esiste
// 	if (root != nullptr) {
// 		root->doGraphNode(out);
// 	}
//
// 	out << "}\n";
// 	out.close();
// }

std::string NWTree::tostring() const {
	// Controllo di sicurezza se l'albero è vuoto
	if (this->root == nullptr) {
		return "Tree { vuoto }\n";
	}

	std::string ret = "Tree {\n";

	// Facciamo partire la ricorsione dalla radice con profondità 1 (per l'indentazione)
	ret += tostringAux(this->root, 1);

	ret += "}\n";

	return ret;
}

std::string tostringAux(NWTreeNode* node, int depth) {
	if (node == nullptr) return "";

	std::string ret;

	// 1. Creiamo l'indentazione manuale (niente STL, un semplice loop)
	std::string indent = "";
	for (int i = 0; i < depth * 4; ++i) {
		indent += " ";
	}

	// 2. Aggiungiamo le informazioni del nodo corrente usando il tostring()
	// che hai già preparato per NWTreeNode
	ret += indent + node->tostring() + "\n";

	// 3. Chiamata ricorsiva per esplorare in profondità (DFS) tutti i figli
	// Usiamo node->size per sapere quanti figli effettivi ha
	for (int i = 0; i < node->size; ++i) {
		if (node->childs[i] != nullptr) {
			// Aumentiamo la profondità per i figli
			ret += tostringAux(node->childs[i], depth + 1);
		}
	}

	return ret;
}

/// END NWTree
