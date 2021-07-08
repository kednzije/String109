#include <iostream>
using namespace std;

class Node {
public:
	Node();
	Node(int __val);
	void setVal(int __val);
	void setNxt(Node* __nxt);
	int getVal() const;
	Node* getNxt() const;

private:
	int val;
	Node* nxt;
};

Node::Node() {
	val = 0, nxt = nullptr;
}
Node::Node(int __val) {
	val = __val, nxt = nullptr;
}
void Node::setVal(int __val) {
	val = __val;
}
void Node::setNxt(Node* __nxt) {
	nxt = __nxt;
}
int Node::getVal() const {
	return val;
}
Node* Node::getNxt() const {
	return nxt;
}

class LinkedList {
public:
	LinkedList();
	~LinkedList();
	LinkedList(const LinkedList&);
	void insertHead(int val);
	void insertTail(int val);
	void append(const LinkedList&);
	LinkedList reverse() const;
	LinkedList reverseM(const int m) const;
	void print() const;
private:
	Node* head;
};
LinkedList::LinkedList() {
	head = nullptr;
}
LinkedList::~LinkedList() {
	while(head != nullptr) {
		Node* node = head->getNxt();
		delete head;
		head = node;
	}
}
LinkedList::LinkedList(const LinkedList &other) {
	Node* node = other.head;
	head = nullptr;
	while(node != nullptr) {
		insertTail(node->getVal());
		node = node->getNxt();
	}
}
void LinkedList::insertHead(int val) {
	Node* node = new Node(val);
	node->setNxt(head);
	head = node;
}
void LinkedList::insertTail(int val) {
	Node* node = new Node(val);
	if(head == nullptr) {
		head = node;
		return;
	}
	Node* pos = head;
	while(pos->getNxt() != nullptr) {
		pos = pos->getNxt();
	}
	pos->setNxt(node);
}
void LinkedList::append(const LinkedList &other) {
	Node* node = other.head;
	while(node != nullptr) {
		insertTail(node->getVal());
		node = node->getNxt();
	}
}
LinkedList LinkedList::reverse() const {
	LinkedList list;
	Node* node = head;
	while(node != nullptr) {
		list.insertHead(node->getVal());
		node = node->getNxt();
	}
	return list;
}
LinkedList LinkedList::reverseM(const int m) const {
	Node* node = head;
	int cnt = 0;
	LinkedList helper, res;
	while(node != nullptr) {
		helper.insertTail(node->getVal());
		cnt++;
		node = node->getNxt();
		if(m == cnt) {
			res.append(helper.reverse());
			helper.~LinkedList();
			cnt = 0;
		}
	}
	res.append(helper);
	return res;
}
void LinkedList::print() const {
	Node* node = head;
	while(node != nullptr) {
		cout << node->getVal() << ' ';
		node = node->getNxt();
	}
	cout << endl;
}

int main() {
	int n, m;
	cin >> n >> m;
	LinkedList list;
	for(int i = 1; i <= n; i++) {
		int val;
		cin >> val;
		list.insertTail(val);
	}
	LinkedList reversedList = list.reverseM(m);
	reversedList.print();
}