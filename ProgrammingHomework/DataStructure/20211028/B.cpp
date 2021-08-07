#include <iostream>
#include <cmath>
using namespace std;
constexpr int MAXN = 1e4 + 10;
constexpr int MAXM = 1e4 + 10;

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

int tree[MAXN][MAXM];
void dfs(Node* node, int step) {
	tree[step][++tree[step][0]] = node->val;
	if(node->ls != nullptr) {
		dfs(node->ls, step + 1);
	}
	if(node->rs != nullptr) {
		dfs(node->rs, step + 1);
	}
}

int main() {
	int n;
	cin >> n;
	Node *root = new Node();
	if(!build_tree(root)) {
		root = nullptr;
	}
	dfs(root, 1);
	for(int i = 1; tree[i][0]; i++) {
		if(i % 2) {
			for(int j = 1; j <= tree[i][0]; j++) {
				cout << tree[i][j] << ' ';
			}
			cout << endl;
		}
		else {
			for(int j = tree[i][0]; j >= 1; j--) {
				cout << tree[i][j] << ' ';
			}
			cout << endl;
		}
	}
}