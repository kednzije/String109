#include <iostream>
#include <queue>
#include <cmath>
#include <map>
using namespace std;
#define EPS 1e-8
inline int max(int a, int b) {
	return a > b ? a : b;
}

struct Node {
	double weight;
	char c;
	int len;
	Node *l, *r;
	Node() {
		weight = 0;
		c = 0;
		len = 1;
		l = r = nullptr;
	}
	Node(char _c, double _weight, int _len=1) {
		weight = _weight;
		c = _c;
		len = _len;
		l = r = nullptr;
	}
	bool operator < (const Node &other) const {
		if(fabs(weight - other.weight) < EPS) {
			return len > other.len;
		}
		return weight > other.weight;
	}
};
struct cmp {
	bool operator ()(const Node* a, const Node* b) {
		return (*a) < (*b);
	}
};

map <char, string> codes;
void dfs(Node* node, string huffcode) {
	if(node->l == nullptr && node->r == nullptr) {
		codes[node->c] = huffcode;
		return;
	}
	if(node->l != nullptr) {
		dfs(node->l, huffcode + "0");
	}
	if(node->r != nullptr) {
		dfs(node->r, huffcode + "1");
	}
}

int main() {
	priority_queue <Node*, vector<Node*>, cmp> que;
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		char c;
		double weight;
		cin >> c >> weight;
		que.push(new Node(c, weight));
	}
	Node* root;
	while(que.size() > 1) {
		Node *a, *b;
		a = que.top(), que.pop();
		b = que.top(), que.pop();
		Node* ab = new Node(a->c, a->weight + b->weight, max(a->len, b->len) + 1);
		ab->l = a, ab->r = b;
		que.push(ab);
	}
	root = que.top();

	codes.clear();
	dfs(root, "");
	cout << "Huffman coding result: " << endl;
	for(auto &code: codes) {
		cout << code.first << " is " << code.second << endl;
	}
}
/*
Input:
7
a 0.25
b 0.1
c 0.12
d 0.2
e 0.15
f 0.07
g 0.11
Output:
Huffman coding result: 
a is 10
b is 1111
c is 011
d is 00
e is 110
f is 1110
g is 010
*/