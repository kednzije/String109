#include "ListPoly.h"

ListPoly::ListPoly() {
	head = nullptr;
}
ListPoly::~ListPoly() {
	Node* node = head;
	while(node != nullptr) {
		Node* next = node->m_next;
		delete node;
		node = next;
	}
}
ListPoly::ListPoly(ListPoly const &polynomial) {
	head = new Node(polynomial.head->coef, polynomial.head->power);
	Node* node = polynomial.head->m_next, *local_node = head;
	while(node != nullptr) {
		local_node->m_next = new Node(node->coef, node->power);
		local_node->m_next->m_pre = local_node;
		local_node = local_node->m_next;
		node = node->m_next;
	}
}
ListPoly& ListPoly::operator= (const ListPoly& p) {
	head = new Node(p.head->coef, p.head->power);
	Node* node = p.head->m_next, *local_node = head;
	while(node != nullptr) {
		local_node->m_next = new Node(node->coef, node->power);
		local_node->m_next->m_pre = local_node;
		local_node = local_node->m_next;
		node = node->m_next;
	}
	return *this;
}
void ListPoly::addTerm(int coef, int power) {
	if(head == nullptr) {
		head = new Node(coef, power);
		return;
	}
	if(head->power == power) {
		head->coef += coef;
		if(!head->coef) {
			Node* head_new = head->m_next;
			delete head;
			head = head_new;
		}
		return;
	}
	Node* node = head->m_next;
	if(node == nullptr) {
		head->m_next = new Node(coef, power);
		head->m_next->m_pre = head;
		return;
	}
	while(node->m_next != nullptr) {
		if(node->power == power) {
			node->coef += coef;
			if(!node->coef) {
				if(node->m_next != nullptr) {
					node->m_next->m_pre = node->m_pre;
				}
				if(node->m_pre != nullptr) {
					node->m_pre->m_next = node->m_next;
				}
				delete node;
			}
			return;
		}

		node = node->m_next;
	}
	if(node->power == power) {
		node->coef += coef;
		if(!node->coef) {
			if(node->m_next != nullptr) {
				node->m_next->m_pre = node->m_pre;
			}
			if(node->m_pre != nullptr) {
				node->m_pre->m_next = node->m_next;
			}
			delete node;
		}
		return;
	}

	node->m_next = new Node(coef, power);
	node->m_next->m_pre = node;
}
void ListPoly::setIthCoe(int i, int coef) {
	Node* node = head;
	for(int j = 0; j < i; j++) {
		node = node->m_next;
	}
	node->coef = coef;
}
void ListPoly::setIthPow(int i, int power) {
	Node* node = head;
	for(int j = 0; j < i; j++) {
		node = node->m_next;
	}
	node->power = power;
}
int ListPoly::getIthCoe(int i) {
	Node* node = head;
	for(int j = 0; j < i; j++) {
		node = node->m_next;
	}
	return node->coef;
}
int ListPoly::getIthPow(int i) {
	Node* node = head;
	for(int j = 0; j < i; j++) {
		node = node->m_next;
	}
	return node->power;
}
int ListPoly::getSize() {
	Node* node = head;
	int size = 0;
	while(node != nullptr) {
		size++;
		node = node->m_next;
	}
	return size;
}