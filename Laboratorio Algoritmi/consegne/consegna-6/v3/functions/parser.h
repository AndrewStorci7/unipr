//
// Created by sandr_ft5c0vu on 25/06/2026.
//

#ifndef V3_PARSER_H
#define V3_PARSER_H

#include "../sd/queue.h"
#include <string>

#include "../sd/nw_tree.h"

/// Funzione di parsing
/// @param file_name
/// @return
queue_t* parser(const std::string& file_name);
/// Serve per assgeneare il tipo del token in base alla stringa letta
TokenType parserAux(queue_t* tokens, std::string& str);


///
/// @param tokens Coda di tokens
/// @return Albero utilizzato nell'algoritmo di Needleman-Wunsch
NWTree* findBlocks(queue_t* tokens);

/// Funzione ausiliare per `findBlocks()`
/// @param father Nodo padre al quale aggiugnere i figli
/// @param tokens Coda di tokens
/// @return il nodo figlio appena creato
// NWTreeNode* findBlocksAux(NWTreeNode* father, queue_t* tokens);

#endif //V3_PARSER_H
