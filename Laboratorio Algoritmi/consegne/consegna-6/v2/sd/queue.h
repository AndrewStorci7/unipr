//
// Created by sandr_ft5c0vu on 24/06/2026.
//

#ifndef LABORATORIO_ALGORITMI_QUEUE_H
#define LABORATORIO_ALGORITMI_QUEUE_H

/// Struttura delle istruzioni
/// (che verranno tradotte in token)
struct Token {
	TokenType key;
	char val[64] = "\0";
	// int line; // non so se usarlo

	// void print() {
	// 	// cout << "[" << tokenToString(key) << ": " << val << "]" << endl;
	// }
};
typedef Token token_t;

struct node {
	Token * data = nullptr;
	node* next = nullptr;

	node(Token* data, node* next = nullptr):
	data(data), next(next) {};
};

struct queue {
	int size = 0;
	node* head = nullptr;
	node* tail = nullptr;

	// Queue(): head(nullptr), tail(nullptr) {};
	// Queue(node* head, node* tail): head(head), tail(tail) {};

	void push(Token* data) {
		auto new_node = new node{data, nullptr};

		if (this->head == nullptr) {
			this->head = this->tail = new_node;
		} else {
			this->tail->next = new_node;
			this->tail = new_node;
		}

		++size;
	}

	Token* pop() {
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

	Token** c_array() {
		auto ogSize = size;
		auto ret = new Token*[ogSize + 1];
		for (int i = 0; i < ogSize; ++i)
			ret[i + 1] = this->pop();

		ret[0] = nullptr; // lo faccio per gestire meglio

		return ret;
	}

	// void print() {
	// 	auto current = head;
	// 	while (current != nullptr) {
	// 		current->data->print();
	// 		current = current->next;
	// 	}
	// }
};
typedef queue queue_t;


#endif //LABORATORIO_ALGORITMI_QUEUE_H
