#define NULL 0
struct Node {
	int val;
	Node* ls, * rs;
};

int f(int x, Node* node) {
	if(node == NULL) {
		return -1;
	}
	if(x == node->val) {
		return 0;
	}
	if(x < node->val) {
		return 2 * f(x, node->ls);
	}
	else {
		return 2 * f(x, node->rs) + 1;
	}
}