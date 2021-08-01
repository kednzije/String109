#include <iostream>
using namespace std;
constexpr int MAXN = 1e3;
inline int max(int a, int b) {
	return a > b ? a : b;
}

int sum[MAXN];

int main() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> sum[i];
		sum[i] += sum[i - 1];
	}
	
	int maxsum = INT_MIN;
	pair <int, int> section;

	for(int i = 1; i <= n; i++) {
		for(int j = i; j <= n; j++) {
			if(sum[j] - sum[i - 1] > maxsum) {
				maxsum = sum[j] - sum[i - 1];
				section = make_pair(i, j);
			}
		}
	}

	cout << "Max sum of sub-array is " << '[' << section.first << ',' << section.second << ']' << ": " << maxsum << endl;
}
/*
Input:
16
13 -3 -25 20 -3 -16 -23 18 20 -7 12 -5 -22 15 -4 7
Output:
Max sum of sub-array is [8,11]: 43
*/