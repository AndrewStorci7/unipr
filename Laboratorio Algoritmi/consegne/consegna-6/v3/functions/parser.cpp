//
// Created by sandr_ft5c0vu on 25/06/2026.
//

#include "parser.h"
#include <fstream>

// variabile che utilizzo per controllare che l'elemento precedente
// era un token di tipo "TYPE" (ovvero, "tipo della variabiale")
bool is_type_var = false;
bool isFor = false;

// const std::string keywords[] = { "class", "struct", "return" };
// const size_t size_keywords = sizeof(keywords) / sizeof(keywords[0]);

const std::string blocks[] = { "if", "else", "switch", "case", "default", "do", "for", "while" };
const size_t size_blocks = sizeof(blocks) / sizeof(blocks[0]);

// controllo che il token letto sia uno tra le
// parole chiave dei loops
bool oneOfLoops(const std::string& val) {
	const std::string loops[] = { "do", "for", "while" };
	const size_t size_loops = sizeof(loops) / sizeof(loops[0]);

	for (int i = 0; i <= size_loops; ++i)
		if (val == loops[i])
			return true;

	return false;
}

// controllo che il token letto sia uno tra le
// parole chiave dei conditioanls
bool oneOfConditionals(const std::string& val) {
	const std::string conditionals[] = { "if", "else", "switch", "case", "default" };
	const size_t size_conds = sizeof(conditionals) / sizeof(conditionals[0]);

	for (int i = 0; i <= size_conds; ++i)
		if (val == conditionals[i])
			return true;

	return false;
}

// controllo che il token letto sia uno tra le
// parole chiave dei numbers
bool oneOfNumbers(const std::string& val) {
	const std::string numbers[] = { "int", "float", "double", "long", "long int", "long long", "long double", "long float" };
	const size_t size_numbers = sizeof(numbers) / sizeof(numbers[0]);

	for (int i = 0; i <= size_numbers; ++i)
		if (val == numbers[i])
			return true;

	return false;
}

// controllo che il token letto sia uno tra le
// parole chiave dei literal
bool oneOfLiterals(const std::string& val) {
	const std::string literals[] = { "std::string", "string", "char" };
	const size_t size_literals = sizeof(literals) / sizeof(literals[0]);

	for (int i = 0; i <= size_literals; ++i)
		if (val == literals[i])
			return true;

	return false;
}

// ritoran true se e' un tipo di variabiel
bool isTypeVar(const std::string& val) {
	return oneOfLiterals(val) || oneOfNumbers(val) || val == "bool" || val == "void";
}

// const std::string bools[] = { "bool" }; const size_t size_bools = sizeof(bools) / sizeof(bools[0]);
// const std::string voids[] = { "void" }; const size_t size_voids = sizeof(voids) / sizeof(voids[0]);

/// Aggiunge un nuovo token alla lista
/// @param tokens Lista dei token
/// @param ttype Tipo del token
/// @param str Valore
void addNewToken(queue_t* tokens, TokenType ttype, std::string& str) {
	auto new_token = new token_t(ttype, str);
	tokens->push(new_token);
	str.clear();
}

/// Funzione di parsing
///
/// @param file_name
/// @param tree
/// @return
queue_t* parser(const std::string& file_name) {
    std::ifstream stream;
    stream.open(file_name);

    if (!stream.is_open()) {
	    perror("File non trovato!");
    	return nullptr;
    }

    auto tokens_source = new queue_t;

    char c;
    std::string temp;

    /// Parsing del fiel source
    while (stream.get(c)) {
        /// controllo per le direttive
        if (c == '#') {
            if (!temp.empty())
                parserAux(tokens_source, temp);

            temp += c;
            while (stream.get(c) && c != '\n')
                temp += c;

        	// addNewToken(tokens_source, DIRECTIVES, temp);
        	parserAux(tokens_source, temp);
        	continue;
        }

        /// controollo per le stringhe
        if (c == '"') {
            if (!temp.empty())
                parserAux(tokens_source, temp);

            temp += c;
            while (stream.get(c) && c != '"')
                temp += c;
            temp += '"';

            parserAux(tokens_source, temp);
            continue;
        }

        /// quando finisce un'istruzione
        if (c == ' ' || c == '\t' || c == '\n') {
            if (!temp.empty()) {
                parserAux(tokens_source, temp);
                temp.clear();
            }
            continue;
        }

    	/// cotnrollo particolare per evitare gesire i ';'
    	/// nel for
    	// if (isFor && c == ';') {
    	// 	if (!temp.empty())
    	// 		parserAux(tokens_source, temp);
    	// }

        /// controllo per caratteri specioali
        if (c == '{' || c == '}' || c == '(' || c == ')' || c == ';' ||
            c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=') {

            if (!temp.empty())
                parserAux(tokens_source, temp);

            if (is_type_var && c == '*') {
                temp = c;
                parserAux(tokens_source, temp);
            } else {
                TokenType t_type;

                if (c == '{') t_type = OBRACE;
                else if (c == '}') t_type = CBRACE;
                else if (c == '(') t_type = OPAREN;
                else if (c == ')') t_type = CPAREN;
                else if (c == ';') t_type = SEMICOLON;
                else t_type = OPERATOR;

            	std::string s(1, c);
                auto new_token = new Token(t_type, s);
                tokens_source->push(new_token);
            }

        	isFor = false;
        } else {
            temp += c;
        }
    }

    if (!temp.empty())
        parserAux(tokens_source, temp);

    stream.close();
    return tokens_source;
}

/// Serve per assgeneare il tipo del token in base alla stringa letta
TokenType parserAux(queue_t* tokens, std::string& str) {
	if (str.empty())
		return EMPTY;

	TokenType type;

	// if (str == "for") {
	// 	isFor = true;
	// }

	// Valori con un solo carattere
	if (is_type_var && str[0] == '*') {
		type = POINTER;
	} else if (oneOfNumbers(str)) { // else if (oneOf(size_loops, loops, str) || oneOf(size_conds, conditionals, str)) {
		is_type_var = true;
		type = NUMERICAL_TYPE;
	} else if (oneOfLiterals(str)) { // else if (oneOf(size_loops, loops, str) || oneOf(size_conds, conditionals, str)) {
		is_type_var = true;
		type = LITERAL_TYPE;
	} else if (str == "bool") { // else if (oneOf(size_loops, loops, str) || oneOf(size_conds, conditionals, str)) {
		is_type_var = true;
		type = BOOLEAN_TYPE;
	} else if (str == "void") { // else if (oneOf(size_loops, loops, str) || oneOf(size_conds, conditionals, str)) {
		is_type_var = true;
		type = VOID_TYPE;
	} else if (oneOfLoops(str)) { // else if (oneOf(size_numbers, numbers, str) || oneOf(size_chars, chars, str) || oneOf(size_bools, bools, str) || oneOf(size_voids, voids, str)) {
		is_type_var = false;
		type = LOOP_K;
	} else if (oneOfConditionals(str)) { // else if (oneOf(size_numbers, numbers, str) || oneOf(size_chars, chars, str) || oneOf(size_bools, bools, str) || oneOf(size_voids, voids, str)) {
		is_type_var = false;
		type = CONDITIONAL_K;
	} else if (str == "return" || str == "return;") {
		type = RETURN;
	} else if (str == "break" || str == "break;") {
		type = BREAK;
	} else if (str == "continue" || str == "continue;") {
		type = CONTINUE;
	} else if (str[0] >= '0' && str[0] <= '9') {
		is_type_var = false;
		type = NUMBER;
	} else if (str[0] == '"') {
		is_type_var = false;
		type = STRING;
	} else if (str[0] == '#') {
		type = DIRECTIVES;
	} else {
		is_type_var = false;
		type = IDENTIFIER;
	}

	auto new_token = new Token(type, str);
	tokens->push(new_token);

	// cancello la stringa
	str.clear();

	return type;
}

NWTree* findBlocks(queue_t* tokens) {

	if (tokens->empty())
		return nullptr;

	// creazioen dell'alber0o vuoto
	auto* tree = new NWTree;
	auto* root = new NWTreeNode;
	tree->addRoot(root);

	auto* currentNode = tree->getRoot(); // nodo corrente
	auto* currentToken = tokens->pop();  // token corrente

	// BlockType blockType = GLOBAL;
	// TokenType ttype = UNKNOWN;
	bool isFor = false;

	/// la utilizzo per creare l'oggetto ArgumentBlock
	auto temp = new queue_t;

	while (currentToken != nullptr) {
		// controllo solo per il for perche'
		// contiene i caratteri ';'
		isFor = currentToken->val == "for";

        if (currentToken->key == OBRACE) { // '{'
            temp->push(currentToken);

        	auto newBlockToken = new Token(BLOCK, "");
            auto* newBlockNode = new NWTreeNode(newBlockToken, currentNode);
            currentNode->addChild(newBlockNode);

        	// qua aggiungo l'intestazione del blocco
            while (!temp->empty()) {
            	auto newBlockChild = new NWTreeNode(temp->pop(), newBlockNode);
                newBlockNode->addChild(newBlockChild);
            }

            currentNode = newBlockNode;

            // ttype = GLOBAL;
            isFor = false;

        } else if (currentToken->key == CBRACE) { // '}'
        	auto newNode = new NWTreeNode(currentToken, currentNode);
            currentNode->addChild(newNode);

            if (currentNode->father != nullptr) {
                currentNode = currentNode->father;
            }

        } else if (!isFor && currentToken->key == SEMICOLON || currentToken->key == DIRECTIVES) { // Incontro ';'
            temp->push(currentToken);

        	while (!temp->empty()) {
        		auto newBlockChild = new NWTreeNode(temp->pop(), currentNode);
        		currentNode->addChild(newBlockChild);
        	}

            // while (!temp->empty()) {
            //     currentNode->tokens->push(temp->pop());
            // }

            // ttype = GLOBAL;
            isFor = false;

        } else {
            temp->push(currentToken);
        }

		currentToken = tokens->pop();
	}

	delete temp;

	return tree;

}