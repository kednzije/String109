#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN = 1e3 + 10;
constexpr int INF = 2e9;
using ll = long long;
inline ll toInt(const string &s) {
	if(s == "null") {
		return -INF;
	}
	ll num = 0;
	bool neg = (s[0] == '-');
	for(int i = neg; i < s.length(); i++) {
		char c = s[i];
		num = num * 10 + (c - '0');
	}
	return num * (neg ? -1 : 1);
}
struct Node {
	ll val;
	Node *l, *r;
};

ll n, sum, ans, nums[MAXN], sta[MAXN * MAXN], p_sta;

void build_tree(int pos, Node* node) {
	node->val = nums[pos], node->l = nullptr, node->r = nullptr;
	if(nums[pos * 2] != -INF) {
		node->l = new Node;
		build_tree(pos * 2, node->l);
	}
	if(nums[pos * 2 + 1] != -INF) {
		node->r = new Node;
		build_tree(pos * 2 + 1, node->r);
	}
}

void travel(Node* node) {
	sta[p_sta + 1] = node->val + sta[p_sta];
	p_sta++;
	for(int i = 1; i <= p_sta; i++) {
		ans += (sta[p_sta] - sta[i - 1] == sum);
	}
	if(node->l != nullptr) {
		travel(node->l);
	}
	if(node->r != nullptr) {
		travel(node->r);
	}
	p_sta--;
}

int main() {
	for(int i = 0; i < MAXN; i++) {
		nums[i] = -INF;
	}

	cin >> sum >> n;
	string s;
	for(int i = 1; i <= n; i++) {
		cin >> s;
		nums[i] = toInt(s);
	}
	Node* root = new Node;
	build_tree(1, root);
	travel(root);
	cout << (n == 0 ? (sum == 0) : ans) << endl;
}