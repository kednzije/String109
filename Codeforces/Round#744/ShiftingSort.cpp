#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
constexpr int MAXN = 100;

int n, num[MAXN];
vector <vector <int>> ans;

void shift(int arr[], int l, int r, int offset) {
	static int helper[MAXN];
	for(int i = l; i <= r; i++) {
		helper[i] = arr[l + (i - l + offset) % (r - l + 1)];
	}
	for(int i = l; i <= r; i++) {
		arr[i] = helper[i];
	}
}
void print(int arr[], int l, int r) {
	for(int i = l; i <= r; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;
}
bool check(int arr[], int l, int r) {
	for(int i = l; i < r; i++) {
		if(arr[i] > arr[i + 1]) {
			return false;
		}
	}
	return true;
}
int findmin(int arr[], int l, int r) {
	int pos = l;
	for(int i = l; i <= r; i++) {
		if(arr[i] < arr[pos]) {
			pos = i;
		}
	}
	return pos;
}

int main() {
	int t;
	cin >> t;
	while(t--) {
		memset(num, 0, sizeof(num));
		ans.clear();
		cin >> n;
		for(int i = 1; i <= n; i++) {
			cin >> num[i];
		}
		int l = 1;
		while(!check(num, 1, n)) {
			int pos = findmin(num, l, n);
			if(pos == l) {
				l++;
				continue;
			}
			shift(num, l, n, pos - l);
			ans.push_back({l, n, pos - l});
			l++;
		}
		cout << ans.size() << endl;
		for(auto &vec: ans) {
			for(auto x: vec) {
				cout << x << ' ';
			}
			cout << endl;
		}
	}
}