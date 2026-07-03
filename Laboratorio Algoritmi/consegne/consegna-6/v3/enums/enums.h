//
// Created by sandr_ft5c0vu on 24/06/2026.
//

#ifndef LABORATORIO_ALGORITMI_ENUMS_H
#define LABORATORIO_ALGORITMI_ENUMS_H

#include <string>

enum BLOCK_TYPES: int {
	GLOBAL,		/// Globale
	FUNCTION,   /// Funzione
	CLASS,      /// Classe
	STRUCT,     /// Struttura
	BLK_IF,		/// Blocco if
	BLK_ELSE,	/// Blocco else
	BLK_WHILE,	/// Blocco while
	BLK_DO,		/// Blocco do
	BLK_FOR,	/// Blocco for
	BLK_SWITCH,	/// Blocco switch
	NOT_VALID
};
typedef BLOCK_TYPES BlockType;


enum TOKEN_TYPE: int {
	/// Valori testuali/generici
	DIRECTIVES, // #include <libreria>, #define <qualcosa>
	IDENTIFIER, // nome della variabile o funzione
	NUMBER,     // valore numerico
	STRING,     // valore testuale
	POINTER,    // puntatore
	OPERATOR,   // +, -, *, /, ==, =, ...
	SEMICOLON,  // ;

	/// Parole chiave del linguaggio
	NUMERICAL_TYPE, // tipo della variabile: numerico
	LITERAL_TYPE,	// tipo della variabiel letterelae
	BOOLEAN_TYPE,	// tipo della variabile: boolana
	VOID_TYPE,		// tipo della varaibile: void
	CONDITIONAL_K,  // switch, case, if, else, ...
	LOOP_K,			// for, while, do
	RETURN,		// return
	BREAK,		// break
	CONTINUE,	// continue
	OBRACE,     // {
	CBRACE,     // }
	OPAREN,     // (
	CPAREN,     // )

	BLOCK,		// blocco: serve solo per il nodo (if, else, struct, class, ...)
	UNKNOWN,    // da cpaire come gestire
	EMPTY = -1,
};
typedef TOKEN_TYPE TokenType;


enum SCORING_RULES: int {
	EMATCH_SCOPE    = +10,  // Match esatto dei blocchi
	EMATCH_VAR      = +4,   // Match esatto di due variabili
	RENAMING        = +1,   // Rinomina di una variabile

	GAP_PENALTY     = -2,   // Penalita' per elimina/inserimento di una nuova riga (token)
	MISMATCH_LIGHT  = -1,   // Mismatch lieve
	MISMATCH_SEVERE = -5,   // Mismatch pesante

	NO_SCORE        = 0,
};
typedef SCORING_RULES ScoringRules;


enum DIFF_TYPE: char {
	REMOVED		= '-',
	ADDED		= '+',
	MODIFIED	= '*',
	NOTHING		= ' ',
};
typedef DIFF_TYPE DiffType;


/// Funzione di supporto per convertire il tipo di blocco in testo
inline std::string getBlockTypeName(BlockType type) {
	switch (type) {
		case GLOBAL:     return "GLOBAL";
		case FUNCTION:   return "FUNCTION";
		case CLASS:      return "CLASS";
		case STRUCT:     return "STRUCT";
		case BLK_IF:     return "IF";
		case BLK_ELSE:   return "ELSE";
		case BLK_WHILE:  return "WHILE";
		case BLK_DO:     return "DO";
		case BLK_FOR:    return "FOR";
		case BLK_SWITCH: return "SWITCH";
		default:         return "UNKNOWN";
	}
}

inline std::string getTokenTypeName(TokenType type) {
	switch (type) {
		case DIRECTIVES:     return "DIRECTIVES";
		case IDENTIFIER:     return "IDENTIFIER";
		case NUMBER:         return "NUMBER";
		case STRING:         return "STRING";
		case POINTER:        return "POINTER";
		case OPERATOR:       return "OPERATOR";
		case SEMICOLON:      return "SEMICOLON";
		case NUMERICAL_TYPE: return "NUMERICAL_TYPE";
		case LITERAL_TYPE:   return "LITERAL_TYPE";
		case BOOLEAN_TYPE:   return "BOOLEAN_TYPE";
		case VOID_TYPE:      return "VOID_TYPE";
		case CONDITIONAL_K:  return "CONDITIONAL_K";
		case LOOP_K:         return "LOOP_K";
		case RETURN:         return "RETURN";
		case BREAK:          return "BREAK";
		case CONTINUE:       return "CONTINUE";
		case OBRACE:         return "OBRACE";
		case CBRACE:         return "CBRACE";
		case OPAREN:         return "OPAREN";
		case CPAREN:         return "CPAREN";
		case BLOCK:			 return "BLOCK";
		case EMPTY:          return "EMPTY";
		default:             return "UNKNOWN";
	}
}


#endif //LABORATORIO_ALGORITMI_ENUMS_H
