#include<iostream>
using namespace std;

int max(int x, int y)
{
	return x > y ? x : y;
}

int main() {
	int n, a, b;
	int min = 0;
	int Max = 0;
	bool escape = 1;
	cin >> n >> a >> b;
	int* p = new int[n];
	int* q = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> p[i];
		Max = p[i] > Max ? p[i] : Max;
		min = p[i] < min ? p[i] : min;
		if (p[i] >= a && p[i] >= b)escape = 0;
	}
	int* arr = new int[Max - min + 1];
	for (int i = 0; i < Max - min + 1; i++) {
		arr[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		arr[p[i]-min]++;
	}
	for (int i = Max; i >= min; i--) {
		if (arr[i-min] > 0) {
			bool done = 0;
			if (a < b) {
				if (a-i>=min && !done) {
					if (arr[a - i-min] > 0) {
						arr[a - i-min] = 0;
						arr[i-min] = 0;
						done = 1;
					}
				}
				if (b-i>=min && !done) {
					if (arr[b - i-min] > 0) {
						arr[b - i-min] = -1;
						arr[i-min] = -1;
						done = 1;
					}
				}
			}
			else {
				if (b-i>=min && !done) {
					if (arr[b - i-min] > 0) {
						arr[b - i-min] = -1;
						arr[i-min] = -1;
						done = 1;
					}
				}
				if (a-i>=min && !done) {
					if (arr[a - i-min] > 0) {
						arr[a - i-min] = 0;
						arr[i-min] = 0;
						done = 1;
					}
				}
			}
			if (!done) {
				escape = 0;
				break;
			}
		}
	}
	if (!escape)cout << 0;
	else {
		cout << 1 << endl;
		for (int i = 0; i < n; i++) {
			cout << -arr[p[i] - min] ;
if(i!=n-1)cout<<" ";
		}
	}
	return 0;
}