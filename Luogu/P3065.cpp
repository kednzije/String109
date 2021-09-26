#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <set>
#include <queue>
using namespace std;
constexpr int MAXN = 3e4 + 50;

int n;
string strs[MAXN];
bool could_be_first[MAXN];

class Trie {
private:
	struct Node {
		int val; // a-z -> 1-26
		bool is_final;
		Node* nxt[30]; // son: a-z
		Node() {
			val = 0;
			is_final = false;
			for(int i = 1; i <= 26; i++) {
				nxt[i] = nullptr;
			}
		}
		Node(char c) {
			val = c - 'a' + 1;
			is_final = false;
			for(int i = 1; i <= 26; i++) {
				nxt[i] = nullptr;
			}
		}
		char this_char() const {
			return 'a' + val - 1;
		}
	};
	Node root;
	set <int> from[30], to[30];
	queue <int> que;
	void delete_node(Node* node) {
		if(node == nullptr) {
			return;
		}
		for(int i = 1; i <= 26; i++) {
			delete_node(node->nxt[i]);
			node->nxt[i] = nullptr;
		}
		delete node;
	}
public:
	Trie() {}
	~Trie() {
		for(int i = 1; i <= 26; i++) {
			delete_node(root.nxt[i]);
			root.nxt[i] = nullptr;
		}
	}
	void insert(const string& str) {
		int pos = 0;
		Node* node = &root;
		while(pos < str.length()) {
			int i = str[pos] - 'a' + 1;
			if(node->nxt[i] == nullptr) {
				node->nxt[i] = new Node(str[pos]);
			}
			node = node->nxt[i];
			pos++;
		}
		node->is_final = true;
	}
	bool could_find_prefix(const string& str) {
		int pos = 0;
		Node* node = &root;
		while(pos < str.length() - 1) {
			int i = str[pos] - 'a' + 1;
			if(node->nxt[i]->is_final) {
				return true;
			}
			node = node->nxt[i];
			pos++;
		}
		return false;
	}
	void add_edge_if(const string& str) {
		for(int c = 1; c <= 26; c++) {
			from[c].clear(), to[c].clear();
		}
		int pos = 0;
		Node* node = &root;
		while(pos < str.length()) {
			int i = str[pos] - 'a' + 1;
			for(int j = 1; j <= 26; j++) {
				if(j == i || node->nxt[j] == nullptr) {
					continue;
				}
				from[j].insert(i), to[i].insert(j);
			}
			node = node->nxt[i];
			pos++;
		}
	}
	bool has_cycle() {
		while(!que.empty()) {
			que.pop();
		}
		for(int i = 1; i <= 26; i++) {
			if(from[i].empty() && !to[i].empty()) {
				que.push(i);
			}
		}
		while(!que.empty()) {
			int u = que.front();
			que.pop();
			for(auto v: to[u]) {
				from[v].erase(u);
				if(from[v].empty() && !to[v].empty()) {
					que.push(v);
				}
			}
			to[u].clear();
		}
		for(int i = 1; i <= 26; i++) {
			if(!from[i].empty()) {
				return true;
			}
		}
		return false;
	}
};

int main() {
	ios::sync_with_stdio(false);
	Trie trie;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> strs[i];
		trie.insert(strs[i]);
	}
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		if(trie.could_find_prefix(strs[i])) {
			continue;
		}
		trie.add_edge_if(strs[i]);
		could_be_first[i] = !trie.has_cycle();
		cnt += could_be_first[i];
	}
	cout << cnt << endl;
	for(int i = 1; i <= n; i++) {
		if(could_be_first[i]) {
			cout << strs[i] << endl;
		}
	}
}