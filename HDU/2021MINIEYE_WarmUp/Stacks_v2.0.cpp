#include <iostream>
#include <cstdio>
using namespace std;
constexpr int MAXN = 1e5 + 10;

struct Node {
	int val, dir; // dir: 1: ->; -1: <-
	Node *pre, *suc;
};
Node* head[MAXN];
Node* tail[MAXN];

int get_len(Node* node) {
	if(node == nullptr) {
		return 0;
	}
	if(node->dir == 1) {
		return get_len(node->suc) + 1;
	}
	else {
		return get_len(node->pre) + 1;
	}
}
void print_list(Node* node) {
	if(node == nullptr) {
		return;
	}
	printf("%d ", node->val);
	if(node->dir == 1) {
		print_list(node->suc);
	}
	else {
		print_list(node->pre);
	}
}

int main() {
	int n, m;
	while(scanf("%d%d", &n, &m) != EOF) {
		for(int i = 1; i <= n; i++) {
			head[i] = new Node { 0, 1, nullptr, nullptr };
			head[i]->suc = new Node { i, 1, head[i], nullptr };
			tail[i] = head[i]->suc;
		}
		while(m--) {
			int a, b;
			scanf("%d%d", &a, &b);
			if(head[b]->suc == nullptr) {
				head[b]->suc = tail[a], tail[a]->dir = -tail[a]->dir;
				tail[b] = head[a]->suc;
				head[a]->suc = nullptr, tail[a] = nullptr;
			}
			else {
				tail[b]->suc = tail[a];

			}
		}
		for(int i = 1; i <= n; i++) {
			printf("%d ", get_len(head[i]->suc));
			print_list(head[i]->suc);
			printf("\n");
		}
	}
}