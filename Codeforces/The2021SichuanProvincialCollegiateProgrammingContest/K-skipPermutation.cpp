#include <iostream>
#include <unordered_set>
using namespace std;

int arr[(int)1e6 + 1];

int main() {
	int n, k;
	cin >> n >> k;
	unordered_set <int> cnt;
	int num = 1;
	for(int i = 1; i <= n;) {
		while(cnt.count(num)) {
			num++;
		}
		for(int j = 0; i <= n && num + k * j <= n; i++, j++) {
			arr[i] = num + k * j;
			cnt.insert(num + k * j);
		}
	}
	for(int i = 1; i < n; i++) {
		cout << arr[i] << ' ';
	}
	cout << arr[n];
	return 0;
}