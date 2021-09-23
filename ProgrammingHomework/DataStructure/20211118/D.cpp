#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;
constexpr int MAXN = 1e3 + 10;
constexpr int INF = 1e9 + 7;

inline int get_min(int a, int b) {
	return a < b ? a : b;
}

struct Node {
	Node *ls, *rs;
};

string inputs[MAXN];

// int dfs(Node *node, bool need_cnt) {
// 	if(node == nullptr) {
// 		return 0;
// 	}
// 	return dfs(node->ls, !need_cnt) + dfs(node->rs, !need_cnt) + (need_cnt);
// }

int dfs(Node* node, int self_status, int father_status) {
	if(node->ls == nullptr && node->rs == nullptr) {
		return self_status;
	}

	int ans = INF;

	if((node->ls == nullptr) || (node->rs == nullptr)) {
		Node *son = (node->ls != nullptr ? node->ls : node->rs);
		if(self_status == 1 || father_status == 1) {
			if(son->ls == nullptr && son->rs == nullptr && self_status == 0) {
				ans = get_min(ans, dfs(son, 1, self_status) + self_status);
			}
			else {
				ans = get_min(ans, dfs(son, 1, self_status) + self_status);
				ans = get_min(ans, dfs(son, 0, self_status) + self_status);
			}
		}
		else {
			ans = get_min(ans, dfs(son, 1, self_status) + self_status);
		}
	}
	else {
		bool son_have_son[2] = { 
			node->ls->ls != nullptr || node->ls->rs != nullptr,
			node->rs->ls != nullptr || node->rs->rs != nullptr
		};
		int tmp_ans[2];
		if(self_status == 1 || father_status == 1) {
			if(son_have_son[0] || self_status == 1) {
				tmp_ans[0] = get_min(dfs(node->ls, 0, self_status), dfs(node->ls, 1, self_status));
			}
			else {
				tmp_ans[0] = dfs(node->ls, 1, self_status);
			}
			if(son_have_son[1] || self_status == 1) {
				tmp_ans[1] = get_min(dfs(node->rs, 0, self_status), dfs(node->rs, 1, self_status));
			}
			else {
				tmp_ans[1] = dfs(node->rs, 1, self_status);
			}
			ans = tmp_ans[0] + tmp_ans[1] + self_status;
		}
		else {
			// for(int i = 1; i < 4; i++) {
			// 	ans = get_min(ans, dfs(node->ls, i & 1, self_status) + dfs(node->rs, (i >> 1) & 1, self_status) + self_status);
			// }
			if(son_have_son[0] && son_have_son[1]) {
				for(int i = 1; i < 4; i++) {
					ans = get_min(ans, dfs(node->ls, i & 1, self_status) + dfs(node->rs, (i >> 1) & 1, self_status) + self_status);
				}
			}
			else if(son_have_son[0] && !son_have_son[1]) {
				ans = get_min(ans, dfs(node->ls, 1, self_status) + dfs(node->rs, 1, self_status));
				ans = get_min(ans, dfs(node->ls, 0, self_status) + dfs(node->rs, 1, self_status));
			}
			else if(!son_have_son[0] && son_have_son[1]) {
				ans = get_min(ans, dfs(node->ls, 1, self_status) + dfs(node->rs, 1, self_status));
				ans = get_min(ans, dfs(node->ls, 1, self_status) + dfs(node->rs, 0, self_status));
			}
			else {
				ans = dfs(node->ls, 1, self_status) + dfs(node->rs, 1, self_status);
			}
		}
	}
	return ans;
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
	// cout << get_min(dfs(root, true), dfs(root, false)) << endl;
	cout << get_min((root->ls != nullptr || root->rs != nullptr) ? (dfs(root, 0, 0)) : INF, dfs(root, 1, 0));
}