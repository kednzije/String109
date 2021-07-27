#include <iostream>
#include <cstring>
using namespace std;

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

constexpr int MAXN = 1e4 + 10;
inline int max(int a, int b) {
	return a > b ? a : b;
}

struct Node {
	int val;
	Node *l, *r;
};

int nums[MAXN], ans[MAXN];

int maxn(int l, int r) {
	for(int i = l; i <= r; i++) {
		if(nums[i] > nums[l]) {
			l = i;
		}
	}
	return l;
}

void build_tree(int l, int r, Node *node) {
	int pos = maxn(l, r), num = nums[pos];
	node->val = num;
	node->l = node->r = nullptr;
	if(l == r) {
		return;
	}
	if(pos > l) {
		node->l = new Node;
		build_tree(l, pos - 1, node->l);
	}
	if(pos < r) {
		node->r = new Node;
		build_tree(pos + 1, r, node->r);
	}
}

int main() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> nums[i];
	}
	
	Node *root = new Node;
	build_tree(1, n, root);
	Queue <Node*> que;
	que.push(root);
	while(!que.empty()) {
		Node* node = que.front();
		que.pop();
		ans[++ans[0]] = (node == nullptr ? -1 : node->val);
		if(node != nullptr/* && (node->l != nullptr || node->r != nullptr)*/) {
			que.push(node->l), que.push(node->r);
		}
	}
	for(int i = ans[0]; ans[i] == -1; i--, ans[0]--);
	for(int i = 1; i <= ans[0]; i++) {
		cout << ans[i] << ' ';
	}
}