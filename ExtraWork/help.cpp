#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN = 1e3 + 7;

int n, vec[MAXN];
bool edges[MAXN][MAXN];

void init_edges() {
	memset(edges, false, sizeof(edges));
}
bool search(int pos, int cnt) {
	vec[cnt] = pos;
	if(cnt == n) {
		return true;
	}
	for(int i = 1; i <= n; i++) {
		if(edges[pos][i] && search(i, cnt + 1)) {
			return true;
		}
	}
	return false;
}
void print_vec() {
	for(int i = 1; i <= n; i++) {
		cout << vec[i];
		if(i < n) {
			cout << "->";
		}
		else {
			cout << endl;
		}
	}
}

int main() {
	init_edges();
	cin >> n;
	for(int i = 1; i <= n * (n - 1) / 2; i++) {
		int u, v;
		cin >> u >> v;
		edges[u][v] = true;
	}
	for(int i = 1; i <= n; i++) {
		if(search(i, 1)) {
			break;
		}
	}

	print_vec();
}