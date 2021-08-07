#include <iostream>
#include <stack>
using namespace std;

enum Object {
	NONE = 0,
	WOLF = 1,
	SHEEP = 3,
	PLANT = 6
};

Object a[] = {
	WOLF, SHEEP, PLANT
}, b[] = {
	NONE, NONE, NONE
};

stack <Object> sta;
int vis[2][20][10];

bool dfs(int k, bool a2b) {
	Object* from = (a2b ? a : b);
	if(vis[a2b][from[0] + from[1] + from[2]][k == -1 ? 0 : from[k]]) {
		return false;
	}
	vis[a2b][from[0] + from[1] + from[2]][k == -1 ? 0 : from[k]] = true;
	int to_ind;
	if(k == -1) {
		for(int i = 0; i < 3; i++) {
			for(int j = i + 1; j < 3; j++) {
				Object x = from[i], y = from[j];
				if(x > y) {
					swap(x, y);
				}
				if((x == WOLF && y == SHEEP) || (x == SHEEP && y == PLANT)) {
					return false;
				}
			}
		}
		sta.push(NONE);
	}
	else {
		int x = (k + 1) % 3, y = 3 - k - x;
		if(from[x] > from[y]) {
			swap(x, y);
		}
		if((from[x] == WOLF && from[y] == SHEEP) || (from[x] == SHEEP && from[y] == PLANT)) {
			return false;
		}
		sta.push(from[k]);
		Object* to = (a2b ? b : a);
		for(int i = 0; i < 3; i++) {
			if(to[i] == NONE) {
				swap(to[i], from[k]);
				to_ind = i;
				break;
			}
		}
	}
	bool succ = true;
	for(int i = 0; i < 3; i++) {
		if(b[i] == NONE) {
			succ = false;
			break;
		}
	}
	if(succ) {
		return true;
	}
	from = (a2b ? b : a);
	for(int i = 0; i < 3; i++) {
		if(i != to_ind && from[i] != NONE && dfs(i, !a2b)) {
			return true;
		}
	}
	if(dfs(-1, !a2b)) {
		return true;
	}

	from = (a2b ? a : b);
	sta.pop();
	if(k != -1) {
		swap(from[k], (a2b ? b : a)[to_ind]);
	}
	return false;
}

void print_ans() {
	stack <Object> sta_rev;
	while(!sta.empty()) {
		sta_rev.push(sta.top());
		sta.pop();
	}
	bool a2b = true;
	while(!sta_rev.empty()) {
		cout << (a2b ? "a -> b: " : "b -> a: ");
		switch (sta_rev.top())
		{
		case WOLF:
			cout << "WOLF" << endl;
			break;
		case SHEEP:
			cout << "SHEEP" << endl;
			break;
		case PLANT:
			cout << "PLANT" << endl;
			break;
		default:
			cout << "NONE" << endl;
			break;
		}
		sta_rev.pop();
		a2b = !a2b;
	}
}

int main() {
	for(int i = 0; i < 3; i++) {
		if(a[i] != NONE && dfs(i, true)) {
			print_ans();
			break;
		}
	}
}