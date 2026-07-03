//
// Created by sandr_ft5c0vu on 24/06/2026.
//

#include "queue.h"
#include "../enums/enums.h"

Token::Token() {
	this->key = UNKNOWN;
	this->val = "";
}

Token::Token(TokenType type, std::string val) {
	this->key = type;
	this->val = val;
}

std::string Token::tostring(std::string c) const {
	std::string ret = c;

	ret += "[" + getTokenTypeName(this->key);
	ret += std::string(" => ") + this->val;
	ret += "]\n";

	return ret;
}

std::string node::tostring() const {
	std::string ret;

	ret += "[" + getTokenTypeName(this->data->key);
	ret += std::string(" => ") + this->data->val;
	ret += "]\n";

	return ret;
}

void queue::push(Token* data) {
	auto new_node = new node{data, nullptr};

	if (this->head == nullptr) {
		this->head = this->tail = new_node;
	} else {
		this->tail->next = new_node;
		this->tail = new_node;
	}

	++size;
}

Token* queue::pop() {
	if (this->head == nullptr)
		return nullptr;

	auto temp = this->head;
	auto ret = temp->data;

	this->head = this->head->next;

	if (this->head == nullptr) {
		this->tail = nullptr;
	}

	delete temp;
	--size;
	return ret;
}

// Token** queue::c_array() const {
// 	auto current = head;
// 	auto ogSize = size;
// 	auto ret = new Token*[ogSize + 1];
//
// 	for (int i = 0; i < ogSize; ++i) {
// 		if (current == nullptr)
// 			break;
// 		ret[i + 1] = current->data;
// 		current = current->next;
// 	}
//
// 	ret[0] = nullptr; // lo faccio per gestire meglio
//
// 	return ret;
// }

bool queue::empty() const {
	return size == 0;
}

std::string queue::tostring(std::string c) const {
	std::string ret;

	auto current = head;
	while (current != nullptr) {
		ret += c + current->tostring();
		current = current->next;
	}

	return ret;
}