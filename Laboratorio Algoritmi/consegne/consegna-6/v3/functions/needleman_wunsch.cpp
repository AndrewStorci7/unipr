//
// Created by sandr_ft5c0vu on 01/07/2026.
//

#include "needleman_wunsch.h"

#include <iostream>

#include "parser.h"
#include "../sd/stack.h"

/**
 * Funzione di backtracing
 * @param blockA
 * @param blockB
 * @param matrix
 */
void backtrackMatrix(NWTreeNode* blockA, NWTreeNode* blockB, int** matrix);

/**
 * Stampa la matrice (solo per debugging)
 * @param matrix
 * @param size1
 * @param size2
 */
void printMatrix(int** matrix, int size1, int size2);

/**
 * Funzione ausiliare per l'algoritmo principale di Needleman-Wunsch
 * @param blockA
 * @param blockB
 * @param generateDiff
 * @return
 */
int needlemanWunschAux(NWTreeNode* blockA, NWTreeNode* blockB, bool generateDiff = false);

/**
 * Stampa la differenza di codice in modo che sia piu' visibile
 * @param diffStack stack con le stringhe e le operazioni (-, + o *)
 */
void printDiff(stack* diffStack);

void pushNodeToDiff(NWTreeNode* node, int op);

/**
 * Stack per la gestione delle stringhe in backtracing
 */
stack* diff = new stack;

int similarity(NWTreeNode* n1, NWTreeNode* n2) {

    if (n1 == nullptr || n2 == nullptr)
        return NO_SCORE;

	if (n1->token == nullptr || n2->token == nullptr)
		return NO_SCORE;

	/// Gestisoc il caso in cui il tipo dei token sia cambiato
	Token* t1 = n1->token;
	Token* t2 = n2->token;
	TokenType t_temp1 = t1->key, t_temp2 = t2->key;

	if (t_temp1 == t_temp2 && t_temp1 == BLOCK)
		return needlemanWunschAux(n1, n2, false);

    /// Gestisco il caso inj cui il tipo dei token sia uguale
    if (t_temp1 == t_temp2) {
    	// se e' un nome di variabile e il valore
    	// e' diverso allora e' stato
    	// rinominata la variabile (o funzione)
    	if (t_temp1 == IDENTIFIER && t1->val != t2->val)
    		return RENAMING;

    	if (t1->val != t2->val)
    		return MISMATCH_LIGHT;

    	return EMATCH_VAR;
    }

	// token di tipo "VAR"
	if ((t_temp1 == NUMERICAL_TYPE && t_temp2 == LITERAL_TYPE) ||
		(t_temp2 == NUMERICAL_TYPE && t_temp1 == LITERAL_TYPE) ||
		(t_temp1 == BOOLEAN_TYPE && t_temp2 == LITERAL_TYPE) ||
		(t_temp2 == BOOLEAN_TYPE && t_temp1 == LITERAL_TYPE) ||
		(t_temp1 == VOID_TYPE && (t_temp2 == LITERAL_TYPE || t_temp2 == NUMERICAL_TYPE || t_temp2 == BOOLEAN_TYPE)) ||
		(t_temp2 == VOID_TYPE && (t_temp1 == LITERAL_TYPE || t_temp1 == NUMERICAL_TYPE || t_temp1 == BOOLEAN_TYPE)))
		return MISMATCH_SEVERE;
	if (t_temp1 == NUMERICAL_TYPE && t_temp2 != BOOLEAN_TYPE)
		return MISMATCH_LIGHT;

	// token di tipo "BLOCCO"
	if ((t_temp1 == CONDITIONAL_K && t_temp2 != LOOP_K) ||
		(t_temp2 == CONDITIONAL_K && t_temp1 != LOOP_K))
		return MISMATCH_SEVERE;

	return MISMATCH_SEVERE;
}


void needlemanWunsch(const std::string& source, const std::string& target) {

	auto tokens1 = parser(source);
	auto blocks1 = findBlocks(tokens1);

	// blocks1->doGraph("source.dot");

	auto tokens2 = parser(target);
	auto blocks2 = findBlocks(tokens2);

	// blocks2->doGraph("target.dot");

	if (blocks1 == nullptr || blocks2 == nullptr) {
		perror("neddlemanWunsch(): Nessun dato!");
		delete tokens1;
		delete tokens2;
		delete blocks1;
		delete blocks2;
		return;
	}

	auto currentSourceNode = blocks1->getRoot();
	auto currentTargetNode = blocks2->getRoot();

	needlemanWunschAux(currentSourceNode, currentTargetNode, true);

	// bool isNewLine = false;
	//
	// // fase dio backtracing
	// while (!diff->isEmpty()) {
	// 	auto node = diff->pop();
	//
	// 	if (isNewLine) {
	// 		std::cout << node->op << ":";
	// 		isNewLine = false;
	// 	}
	// 	std::cout << " " << node->token_target->val;
	//
	// 	if (node->token_target->key == CBRACE ||
	// 		node->token_target->key == OBRACE ||
	// 		node->token_target->key == SEMICOLON ||
	// 		node->token_target->key == DIRECTIVES
	// 	) {
	// 		std::cout << std::endl;
	// 		isNewLine = true;
	// 	}
	// }

	printDiff(diff);

}


int needlemanWunschAux(NWTreeNode* blockA, NWTreeNode* blockB, bool generateDiff) {
	auto lenA = blockA->size;
	auto lenB = blockB->size;

	auto matrix = new int*[lenA + 1];
	for (int i = 0; i <= lenA; ++i)
		matrix[i] = new int[lenB + 1];

	// imposto il gap
	for (int i = 0; i <= lenA; ++i)
		matrix[i][0] = i * GAP_PENALTY;
	for (int j = 0; j <= lenB; ++j)
		matrix[0][j] = j * GAP_PENALTY;

	// costruisco la matrice di Needleman-Wunsch
	for (int i = 1; i <= lenA; ++i) {
		for (int j = 1; j <= lenB; ++j) {

			NWTreeNode* childA = blockA->childs[i - 1];
			NWTreeNode* childB = blockB->childs[j - 1];

			auto match = matrix[i - 1][j - 1] + similarity(childA, childB);
			auto del   = matrix[i - 1][j] + GAP_PENALTY;
			auto ins   = matrix[i][j - 1] + GAP_PENALTY;

			auto maxScore = (match > del) ? ((match > ins) ? match : ins) : (del > ins ? del : ins);

			matrix[i][j] = maxScore;
		}
	}

	int finalBlockScore = matrix[lenA][lenB];

	if (generateDiff)
		backtrackMatrix(blockA, blockB, matrix);

	for (int i = 0; i <= lenA; ++i)
		delete[] matrix[i];
	delete[] matrix;

	return finalBlockScore;
}


void backtrackMatrix(NWTreeNode* blockA, NWTreeNode* blockB, int** matrix) {
    int i = blockA->size;
    int j = blockB->size;

    // ATTENZIONE: Il backtracking genera le operazioni al contrario (dall'ultima alla prima).
    // Per un output perfetto dovresti salvarle in uno Stack (LIFO) o un array e stamparle alla fine,
    // ma per ora stampiamole direttamente per testare la logica.

    while (i > 0 || j > 0) {
        if (j == 0) {
            // diff->push(blockA->childs[i - 1]->token, blockB->childs[j]->token, REMOVED);
        	pushNodeToDiff(blockA->childs[i - 1], REMOVED);
        	--i;
        } else if (i == 0) {
            // diff->push(blockB->childs[j - 1]->token, nullptr, ADDED);
        	pushNodeToDiff(blockB->childs[j - 1], ADDED);
        	--j;
        } else {
            NWTreeNode* childA = blockA->childs[i - 1];
            NWTreeNode* childB = blockB->childs[j - 1];

            int scoreMatch = matrix[i - 1][j - 1] + similarity(childA, childB);
            int scoreDel   = matrix[i - 1][j] + GAP_PENALTY;
            // int scoreIns   = matrix[i][j - 1] + GAP_PENALTY; // (Puoi ricalcolarlo o andare per esclusione)

            // Abbiamo preso la diagonale?
            if (matrix[i][j] == scoreMatch) {
                if (childA->token->key == BLOCK && childB->token->key == BLOCK) {
                    needlemanWunschAux(childA, childB, true);
                } else {
                    // Sono Token semplici
                	if (childA->token->val != childB->token->val) {
                		diff->push(childA->token, childB->token, MODIFIED);
                	} else {
                		diff->push(childA->token, nullptr, NOTHING);
                	}
                }
                --i;
            	--j;
            }
            // Abbiamo preso la strada verso l'alto? (Cancellazione)
            else if (matrix[i][j] == scoreDel) {
                // diff->push(childA->token, childB->token, REMOVED);
            	pushNodeToDiff(childA, REMOVED);
            	--i;
            }
            // Altrimenti, per esclusione, siamo andati a sinistra (Aggiunta)
            else {
                // diff->push(childB->token, nullptr, ADDED);
            	pushNodeToDiff(childB, ADDED);
            	--j;
            }
        }
    }
}


void pushNodeToDiff(NWTreeNode* node, int op) {
	if (node->token->key == BLOCK) {
		// Dobbiamo scorrere i figli al contrario perché lo Stack (LIFO) li invertirà
		for (int k = node->size - 1; k >= 0; --k) {
			pushNodeToDiff(node->childs[k], op);
		}
	} else {
		if (op == REMOVED) {
			auto newToken = new Token(EMPTY, "");
			diff->push(newToken, node->token, REMOVED); // (target, source, op)
		} else {
			diff->push(node->token, nullptr, ADDED);
		}
	}
}


void printDiff(stack* diffStack) {
    std::string currentLineLeft;
    std::string currentLineRight;
    char currentLineOp = NOTHING;

    while (!diffStack->isEmpty()) {
        auto node = diffStack->pop();

        // Token* activeToken = node->token_target;
    	Token* activeToken = (node->op == REMOVED) ? node->token_source : node->token_target;

        if (node->op == MODIFIED) {
            currentLineOp = '*';
        } else if (node->op == ADDED) {
            if (currentLineOp == ' ') currentLineOp = '+';
            else if (currentLineOp == '-') currentLineOp = '*';
        } else if (node->op == REMOVED) {
            if (currentLineOp == ' ') currentLineOp = '-';
            else if (currentLineOp == '+') currentLineOp = '*';
        }

    	switch (node->op) {
        	default:
        	case NOTHING:
    			currentLineLeft += node->token_target->val + " ";
    			currentLineRight += node->token_target->val + " ";
    			break;
        	case ADDED:
    			currentLineLeft += node->token_target->val + " ";
    			break;
        	case REMOVED:
        	case MODIFIED:
    			currentLineLeft += node->token_target->val + " ";
    			currentLineRight += node->token_source->val + " ";
    			break;
    	}

        if (activeToken != nullptr &&
           (activeToken->key == CBRACE ||
            activeToken->key == OBRACE ||
            activeToken->key == SEMICOLON ||
            activeToken->key == DIRECTIVES)) {

            std::cout << currentLineOp << ": " << currentLineLeft;

            if (currentLineOp == '*' || currentLineOp == '-') {
            	// calcolo automatico degli spazi
                int spaces = 50 - (int) currentLineLeft.length();
                for (int k = 0; k < (spaces > 0 ? spaces : 1); ++k)
                	std::cout << " ";

                std::cout << "-> " << currentLineRight;
            }

            std::cout << "\n";

            currentLineLeft = "";
            currentLineRight = "";
            currentLineOp = ' ';
        }
    }

    if (!currentLineLeft.empty() || !currentLineRight.empty()) {
        std::cout << currentLineOp << ": " << currentLineLeft;

        if (currentLineOp == '*' || currentLineOp == '-') {
        	// calcolo degli spazi
            int spaces = 50 - (int) currentLineLeft.length();
            for(int k = 0; k < (spaces > 0 ? spaces : 1); ++k)
            	std::cout << " ";
            std::cout << "-> " << currentLineRight;
        }
        std::cout << "\n";
    }
}


void printMatrix(int** matrix, int size1, int size2) {
	for (int i = 0; i <= size1; ++i) {
		for (int j = 0; j <= size2; ++j) {
			std::cout << matrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}