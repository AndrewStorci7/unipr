//
// Created by sandr_ft5c0vu on 24/06/2026.
//

#ifndef LABORATORIO_ALGORITMI_NW_TREE_H
#define LABORATORIO_ALGORITMI_NW_TREE_H

#include <string>
#include "queue.h"

/// ! il prefisso NW sta per Needleman-Wunsch

/// Nodo dell'albero che equivale
/// ad un blocco del codice
struct NWTreeNode {
	int maxSize = 0;		// dimnesione massima
	int size = 0;			// dimensione effettiva

	NWTreeNode* father;		// puntatore al padre
	NWTreeNode** childs;	// array dei figli
	Token* token;			// contiene il token
							// se e' di tipo BLOCK sicuramente avra' dei figli

	// int** diffMatrix;		// Matrice di Needleman-Wunsch

	NWTreeNode();
	NWTreeNode(Token* token, NWTreeNode* father);
	~NWTreeNode();

	void addFather(NWTreeNode* f);

	void addChild(NWTreeNode* child);

	bool isLeaf() const;

	// void doGraphNode(std::ofstream& out) const;

	std::string tostring() const;

private:
	void reallocChildren();
};

/// Albero con tutte i blocchi
struct NWTree {
private:
	int size = 0;
	NWTreeNode* root = nullptr;

public:
	NWTree();

	int getSize() const;

	void addRoot(NWTreeNode* root);

	NWTreeNode* getRoot() const;

	// void doGraph(const std::string& filename) const;

	std::string tostring() const;
};


#endif //LABORATORIO_ALGORITMI_NW_TREE_H
