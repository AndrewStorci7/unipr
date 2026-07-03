//
// Created by sandr_ft5c0vu on 24/06/2026.
//

#include "../enums/enums.h"
#include "nw_tree.h"
#include "queue.h"
#include <string>

// class NWMatrix {
//
// };

struct ContextBlock {
	ContextType context; /// Puo' essere parametri o espressione regolare
	std::string val;
};

struct NWTreeNode {
	int children_size = 0;

	Queue** tokens = nullptr;				/// Lista dei tokens
	NWTreeNode** blockChildren = nullptr;	/// array dei figli
	char name[25] = "\0";
	BlockType blockType;

	// questo e' il contesto utilizzato tuttii blocchi tranne che per classi
	// e struct ed e' il contenuto delle parentesi, quindi da non confondere
	// con la matrice vera e propria
	ContextBlock* context;

	NWTreeNode() {
		children_size = 2;
		blockChildren = new NWTreeNode*[2];
		context = nullptr;
	}

	~NWTreeNode() {
		for (int i = 0; i < children_size; ++i)
			delete[] blockChildren[i];
		delete[] blockChildren;
	}
};

// class NWTree {
// };
