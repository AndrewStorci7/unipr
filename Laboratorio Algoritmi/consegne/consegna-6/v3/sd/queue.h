//
// Created by sandr_ft5c0vu on 24/06/2026.
//

#ifndef LABORATORIO_ALGORITMI_QUEUE_H
#define LABORATORIO_ALGORITMI_QUEUE_H

#include "../enums/enums.h"
#include <string>

/// Struttura delle istruzioni
/// (che verranno tradotte in token)
struct Token {
	TokenType key;
	std::string val;
	// int line; // non so se usarlo

	Token();
	Token(TokenType key, std::string val);

	std::string tostring(std::string c = "") const;
};
typedef Token token_t;

struct node {
	Token * data = nullptr;
	node* next = nullptr;

	node(Token* data, node* next = nullptr):
	data(data), next(next) {};

	std::string tostring() const;
};

struct queue {
	int size = 0;
	node* head = nullptr;
	node* tail = nullptr;

	void push(Token* data);

	Token* pop();

	// Token** c_array() const;

	bool empty() const;

	std::string tostring(std::string c = "") const;
};
typedef queue queue_t;


#endif //LABORATORIO_ALGORITMI_QUEUE_H
