//
// Created by sandr_ft5c0vu on 02/07/2026.
//

#include "stack.h"

void stack::push(Token* target, Token* source, char op) {

	if (target == nullptr) {
		perror("Token vuoto");
		return;
	}

	auto newNode = new stack_node;
	newNode->token_source = source;
	newNode->token_target = target;
	newNode->op = op;
	newNode->next = top;
	top = newNode;

	++size;
}


stack_node* stack::pop() {

	if (size == 0) {
		return nullptr;
	}

	auto ret = top;
	top = top->next;

	--size;

	return ret;
}

bool stack::isEmpty() const {
	return size == 0 || top == nullptr;
}