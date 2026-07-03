//
// Created by sandr_ft5c0vu on 02/07/2026.
//

#ifndef V3_STACK_H
#define V3_STACK_H

#include "queue.h"


struct stack_node {
	char op = '\0'; // operazione: +, - o *
	Token* token_source = nullptr;
	Token* token_target = nullptr;
	stack_node* next = nullptr;

	stack_node(): token_source(nullptr), token_target(nullptr), next(nullptr) {}
	stack_node(Token* source, Token* target, char op, stack_node* next):
	token_source(source), token_target(target), op(op), next(next) {}
};

struct stack {
	int size = 0;
	stack_node* top = nullptr;

	stack_node* pop();

	void push(Token* target, Token* source, char op);

	bool isEmpty() const;
};


#endif //V3_STACK_H
