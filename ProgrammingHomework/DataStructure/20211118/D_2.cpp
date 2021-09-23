#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
using namespace std;
constexpr int MAXN = 1e4 + 10;
constexpr int INF = 1e9 + 7;

inline int get_min(int a, int b) {
	return a < b ? a : b;
}

struct Node {
	Node *ls, *rs;
};

string inputs[MAXN];

map <Node*, int> dp[3]; // 0 is for father, 1 is for self, 2 is for son

void dfs(Node* node) {
	dp[0][node] = dp[1][node] = dp[2][node] = INF;
	if(node->ls != nullptr) {
		dfs(node->ls);
	}
	if(node->rs != nullptr) {
		dfs(node->rs);
	}
	if(node->ls == nullptr && node->rs == nullptr) {
		dp[1][node] = get_min(dp[1][node], 1);
		dp[0][node] = get_min(dp[0][node], 0);
		return;
	}
	int sum = 0;
	if(node->ls != nullptr) {
		sum += get_min(dp[1][node->ls], get_min(dp[0][node->ls], dp[2][node->ls]));
	}
	if(node->rs != nullptr) {
		sum += get_min(dp[1][node->rs], get_min(dp[0][node->rs], dp[2][node->rs]));
	}
	dp[1][node] = get_min(dp[1][node], sum + 1);
	sum = 0;
	if(node->ls != nullptr) {
		sum += dp[2][node->ls];
	}
	if(node->rs != nullptr) {
		sum += dp[2][node->rs];
	}
	dp[0][node] = get_min(dp[0][node], sum);
	sum = INF;
	int cur = 0;
	if(node->ls != nullptr) {
		cur += dp[1][node->ls];
		if(node->rs != nullptr) {
			cur += get_min(dp[2][node->rs], dp[1][node->rs]);
		}
		sum = get_min(sum, cur);
	}
	cur = 0;
	if(node->rs != nullptr) {
		cur += dp[1][node->rs];
		if(node->ls != nullptr) {
			cur += get_min(dp[2][node->ls], dp[1][node->ls]);
		}
		sum = get_min(sum, cur);
	}
	dp[2][node] = get_min(dp[2][node], sum);
}

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
	dfs(root);
	cout << get_min(dp[2][root], dp[1][root]);
}