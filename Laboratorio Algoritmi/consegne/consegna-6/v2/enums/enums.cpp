//
// Created by sandr_ft5c0vu on 24/06/2026.
//

#include "enums.h"

enum BLOCK_TYPES: int {
	FUNCTION,   /// Funzione
	CLASS,      /// Classe
	STRUCT,     /// Struttura
	BLK_IF,		/// Blocco if
	BLK_ELSE,	/// Blocco else
	BLK_WHILE,	/// Blocco while
	BLK_DO,		/// Blocco do
	BLK_FOR,	/// Blocco for
	BLK_SWITCH,	/// Blocco switch
};

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
	TYPE,       // tipo della variabile: int, float, double, ...
	KEYWORD,    // if, else, for, while, return, class, ...
	OBRACE,     // {
	CBRACE,     // }
	OPAREN,     // (
	CPAREN,     // )

	UNKNOWN,    // da cpaire come gestire
	EMPTY = -1,
};

enum SCORING_RULES: int {
	EMATCH_SCOPE    = +10,  // Match esatto dei blocchi
	EMATCH_VAR      = +4,   // Match esatto di due variabili
	RENAMING        = +1,   // Rinomina di una variabile

	GAP_PENALTY     = -2,   // Penalita' per elimina/inserimento di una nuova riga (token)
	MISMATCH_LIGHT  = -1,   // Mismatch lieve
	MISMATCH_SEVERE = -5,   // Mismatch pesante

	NO_SCORE        = 0,
};