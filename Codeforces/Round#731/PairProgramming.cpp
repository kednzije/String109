#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 105;

int a[MAXN], b[MAXN];

int main() {
	int t;
	cin >> t;
	vector <int> vec;
	while(t--) {
		vec.clear();
		int n, m, k;
		cin >> k >> n >> m;
		for(int i = 0; i < n; i++) {
			cin >> a[i];
		}
		for(int j = 0; j < m; j++) {
			cin >> b[j];
		}
		int i=0, j=0;
		while(i < n || j < m) {
			if(i == n) {
				if(b[j] && k < b[j]) {
					vec.clear();
					vec.push_back(-1);
					break;
				}
				k += (!b[j]);
				vec.push_back(b[j++]);
			}
			else if(j == m) {
				if(a[i] && k < a[i]) {
					vec.clear();
					vec.push_back(-1);
					break;
				}
				k += (!a[i]);
				vec.push_back(a[i++]);
			}
			else {
				int op;
				if(a[i] < b[j]) {
					op = a[i++];
				}
				else {
					op = b[j++];
				}
				if(op && k < op) {
					vec.clear();
					vec.push_back(-1);
					break;
				}
				k += (!op);
				vec.push_back(op);
			}
		}
		for(int i = 0; i < vec.size(); i++) {
			cout << vec[i] << ' ';
		}
		cout << endl;
	}
}