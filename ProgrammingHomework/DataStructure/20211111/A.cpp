#include <iostream>
#include <sstream>
using namespace std;
constexpr int MAXN = 1e4 + 10;

struct Node {
	int val;
	Node *ls, *rs;
	Node() {
		val = -1;
		ls = rs = nullptr;
	}
	Node(int k) {
		val = k;
		ls = rs = nullptr;
	}
};

bool build_tree(Node *node) {
	cin >> node->val;
	if(node->val == -1) {
		delete node;
		return false;
	}
	node->ls = new Node(), node->rs = new Node();
	if(!build_tree(node->ls)) {
		node->ls = nullptr;
	}
	if(!build_tree(node->rs)) {
		node->rs = nullptr;
	}
	return true;
}

// Node* merge_tree(Node* a, Node* b) {
// 	if(a == nullptr) {
// 		return b;
// 	}
// 	if(b == nullptr) {
// 		return a;
// 	}
// 	Node* node = new Node(a->val + b->val);
// 	node->ls = merge_tree(a->ls, b->ls);
// 	node->rs = merge_tree(a->rs, b->rs);
// 	return node;
// }

void print_tree(Node *node) {
	if(node == nullptr) {
		cout << -1 << ' ';
		return;
	}
	cout << node->val << ' ';
	print_tree(node->ls), print_tree(node->rs);
}

int a, b, ans;

int dfs(Node* node) {
	int cnt = 0;
	if(node->val == a || node->val == b) {
		cnt++;
	}
	if(node->ls != nullptr) {
		cnt += dfs(node->ls);
	}
	if(node->rs != nullptr) {
		cnt += dfs(node->rs);
	}
	if(cnt == 2 && ans == 0) {
		ans = node->val;
	}
	return cnt;
}

int main() {
	Node *root = new Node();
	if(!build_tree(root)) {
		root = nullptr;
	}
	cin >> a >> b;
	dfs(root);
	cout << ans << endl;
}