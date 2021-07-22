#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;
constexpr int MAXN = 1e4 + 10;
inline int max(int a, int b) {
	return a > b ? a : b;
}

#include <stdlib.h>
#include <time.h>

template <typename T>
class Algorithm {
public:
	Algorithm();
	void swap(T&, T&);
	void quick_sort(T*, const unsigned int);
};

template <typename T>
Algorithm<T>::Algorithm() {
	srand(time(NULL));
}
template <typename T>
void Algorithm<T>::swap(T& a, T& b) {
	T c = a;
	a = b;
	b = c;
}
template <typename T>
void Algorithm<T>::quick_sort(T* arr, const unsigned int len) {
	if(len <= 1) {
		return;
	}
	const T pivot = arr[rand() % len];
	// i: element now operated
	// j: the first element equaling to pivot
	// k: the first element bigger than pivot
	int i = 0, j = 0, k = len;
	while(i < k) {
		if(arr[i] < pivot) {
			swap(arr[i++], arr[j++]);
		}
		else if(pivot < arr[i]) {
			swap(arr[i], arr[--k]);
		}
		else {
			i++;
		}
	}
	quick_sort(arr, j), quick_sort(arr + k, len - k);
}

pair <int, int> lines[MAXN];

int main() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> lines[i].first >> lines[i].second;
	}
	// sort(lines + 1, lines + 1 + n);
	Algorithm <pair <int, int>> alg;
	alg.quick_sort(lines + 1, n);
	int l = lines[1].first, r = lines[1].second;
	for(int i = 1; i <= n; i++) {
		if(lines[i].first <= r) {
			r = max(r, lines[i].second);
		}
		else {
			cout << l << ' ' << r << endl;
			l = lines[i].first, r = lines[i].second;
		}
	}
	cout << l << ' ' << r << endl;
}