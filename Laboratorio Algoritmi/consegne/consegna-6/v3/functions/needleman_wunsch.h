//
// Created by sandr_ft5c0vu on 01/07/2026.
//

#ifndef V3_NEEDLEMAN_WUNSCH_H
#define V3_NEEDLEMAN_WUNSCH_H

#include "../sd/nw_tree.h"
#include "../sd/queue.h"


/// struttura creata per migliroare la gestione
/// del risutalto della differenza del codice
/// ottenuta dall'algoritmo di Neddleman-Wunsch
// struct DiffResult {
// 	int score;
// 	std::string diff;
//
// 	DiffResult(): score(0), diff("") {};
// };

/// Funzione che ritoran lo scoring tra 2 token
/// @param t1 token del `source`
/// @param t2 token del `target`
/// @return Punteggio di similarita'
int similarity(NWTreeNode* t1, NWTreeNode* t2);

/// Algortimo di Needleman-Wunsch
/// @param source nome del file codice `source`
/// @param target nome del file codice `target`
void needlemanWunsch(const std::string& source, const std::string& target);
// int needlemanWunschAux(NWTreeNode* source, NWTreeNode* target);



#endif //V3_NEEDLEMAN_WUNSCH_H
