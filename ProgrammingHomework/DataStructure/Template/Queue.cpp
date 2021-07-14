template <typename T> 
class Queue {
public:
	Queue();
	~Queue();
	T front() const;
	bool empty() const;
	void push(T);
	void pop();
private:
	struct Node {
		T val;
		Node* nxt;
		Node();
		Node(T);
	};
	Node *head, *tail;
};

template <typename T>
Queue<T>::Queue() {
	head = new Node(), tail = nullptr;
}
template <typename T>
Queue<T>::~Queue() {
	while(!empty()) {
		pop();
	}
}
template <typename T>
Queue<T>::Node::Node() {
	nxt = nullptr;
}
template <typename T>
Queue<T>::Node::Node(T t) {
	val = t, nxt = nullptr;
}
template <typename T>
T Queue<T>::front() const {
	return head->nxt->val;
}
template <typename T>
bool Queue<T>::empty() const {
	return nullptr == head->nxt;
}
template <typename T>
void Queue<T>::push(T t) {
	Node* node = new Node(t);
	(nullptr == tail) ? (head->nxt = node) : (tail->nxt = node);
	tail = node;
}
template <typename T>
void Queue<T>::pop() {
	if(head->nxt != nullptr) {
		Node* p = head->nxt;
		delete head;
		head = p;
	}
	if(head == tail) {
		tail = nullptr;
	}
}

#include <iostream>
using namespace std;

int main() {
	Queue <int> q;
	q.push(3), q.push(5), q.push(8);
	q.pop();
	q.push(1);
	while(!q.empty()) {
		cout << q.front() << ' ';
		q.pop();
	}
	q.push(4);
	cout << q.front();
}