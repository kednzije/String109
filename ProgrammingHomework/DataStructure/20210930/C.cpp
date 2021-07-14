#include <iostream>
#include <queue>
using namespace std;
constexpr int MAXN = 1e6 + 10;

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

int main() {
	Queue <int> q2, q3;
	int x, n;
	cin >> x >> n;
	for(int i = 2; i <= n; i++) {
		q2.push(2 * x + 1), q3.push(3 * x + 1);
		if(q2.front() <= q3.front()) {
			x = q2.front();
			q2.pop();
		}
		else {
			x = q3.front();
			q3.pop();
		}
	}
	cout << x << endl;
}