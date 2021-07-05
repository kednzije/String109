#include <iostream>
using namespace std;

class Node {
private:
	int val;
	Node* lst, * nxt;
public:
	Node();
	Node(int _val);
	~Node();
	void setVal(int _val);
	void setLst(Node* _lst);
	void setNxt(Node* _nxt);
	int getVal() const;
	Node* getLst() const;
	Node* getNxt() const;
};

Node::Node() {
	val = -1;
}
Node::Node(int _val) {
	val = _val;
	lst = nxt = nullptr;
}
Node::~Node() {
	lst = nxt = nullptr;
}
void Node::setVal(int _val) {
	val = _val;
}
void Node::setLst(Node* _lst) {
	lst = _lst;
}
void Node::setNxt(Node* _nxt) {
	nxt = _nxt;
}
int Node::getVal() const {
	return val;
}
Node* Node::getLst() const {
	return lst;
}
Node* Node::getNxt() const {
	return nxt;
}

class DLinkedList {
private:
	Node* head;
public:
	DLinkedList();
	~DLinkedList();
	void insert(int val);
	void rollHead(int t, bool toNxt);
	void deleteHead(bool toNxt);
	bool isEmpty() const;
	int getHeadVal() const;
};
DLinkedList::DLinkedList() {
	head = nullptr;
}
DLinkedList::~DLinkedList() {
	while(head != nullptr) {
		Node* node = head;
		head = head->getNxt();
		delete node;
	}
}
void DLinkedList::insert(int val) {
	if(head == nullptr) {
		head = new Node(val);
		head->setLst(head), head->setNxt(head);
		return;
	}
	// if(head->getNxt() == nullptr) {
	// 	head->setNxt(new Node(val));
	// 	head->setLst(head->getNxt());
	// 	head->getNxt()->setNxt(head);
	// 	head->getLst()->setLst(head);
	// 	return;
	// }
	Node* node = new Node(val);
	node->setNxt(head);
	head->getLst()->setNxt(node);

	node->setLst(head->getLst());
	head->setLst(node);
}
void DLinkedList::rollHead(int t, bool toNxt) {
	if(head == nullptr || head->getNxt() == nullptr) {
		return;
	}
	while (0 != t) {
		if(toNxt) {
			head = head->getNxt();
		}
		else {
			head = head->getLst();
		}
		t--;
	}
}
void DLinkedList::deleteHead(bool toNxt) {
	if(head == nullptr) {
		return;
	}
	if(head->getNxt() == head) {
		delete head;
		head = nullptr;
		return;
	}

	Node* node = head;
	head->getNxt()->setLst(node->getLst());
	head->getLst()->setNxt(node->getNxt());
	if(toNxt) {
		head = head->getNxt();
	}
	else {
		head = head->getLst();
	}
	delete node;
}
bool DLinkedList::isEmpty() const {
	return head == nullptr;
}
int DLinkedList::getHeadVal() const {
	return head->getVal();
}

void makeTable(int n, DLinkedList &list) {
	for(int i = 1; i <= n; i++) {
		list.insert(i);
	}
}
void roll(DLinkedList &list, int m, int k, bool toNxt) {
	list.rollHead(k - 1, true);
	while(!list.isEmpty()) {
		list.rollHead(m - 1, toNxt);
		cout << list.getHeadVal() << ' ';
		list.deleteHead(toNxt);
	}
	cout << endl;
}

int main() {
	int n, m, k;
	cin >> n >> m >> k;
	DLinkedList list1, list2;
	makeTable(n, list1);
	makeTable(n, list2);
	roll(list1, m, k, true);
	roll(list2, m, k, false);
}