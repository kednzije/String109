#include <iostream>
#include <cstdio>
using namespace std;
constexpr int MAXN = 1e4 + 10;

string inputs[MAXN];

int main() {
	int n, depth = 1;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> inputs[i];
	}
	if(inputs[1] == "null") {
		cout << 0 << endl;
		return 0;
	}
	vector <Node*> nodes[2];
	Node* root = new Node;
	root->ls = root->rs = nullptr;
	nodes[1].push_back(root);
	depth++;
	for(int i = 2; i <= n; i++) {
		Node* node;
		if(inputs[i] == "null") {
			node = nullptr;
		}
		else {
			node = new Node;
			node->ls = node->rs = nullptr;
		}
		nodes[depth % 2].push_back(node);
		if(nodes[depth % 2].size() == nodes[(depth + 1) % 2].size() * 2) {
			for(int j = 0; j < nodes[(depth + 1) % 2].size(); j++) {
				nodes[(depth + 1) % 2][j]->ls = nodes[depth % 2][j * 2];
				nodes[(depth + 1) % 2][j]->rs = nodes[depth % 2][j * 2 + 1];
			}
			for(int j = nodes[depth % 2].size() - 1; j >= 0; j--) {
				if(nodes[depth % 2][j] == nullptr) {
					nodes[depth % 2].erase(nodes[depth % 2].begin() + j);
				}
			}
			depth++;
			nodes[depth % 2].clear();
		}
	}
}