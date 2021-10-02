#include <iostream>
using namespace std;
constexpr int MAXN = 150;
using ll = long long;

#include <stdlib.h>
#include <time.h>

/**
 * @brief An algorithm collection for DS course.
 * 
 * @tparam T Type of data to be operated.
 */
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

int x[MAXN], y[MAXN];

struct Distance {
	int a, b, dis;
	bool operator < (const Distance& other) const {
		return dis < other.dis;
	}
} dis[MAXN * MAXN];

inline int i_abs(int k) {
	return k > 0 ? k : -k;
}
int calc(int i, int j) {
	return i_abs(x[i] - x[j]) + i_abs(y[i] - y[j]);
}

int f[MAXN];
int getf(int k) {
	if(f[k] != k) {
		f[k] = getf(f[k]);
	}
	return f[k];
}
bool merge(int a, int b) {
	a = getf(a), b = getf(b);
	if(a == b) {
		return false;
	}
	if(rand() % 2) {
		f[a] = b;
	}
	else {
		f[b] = a;
	}
	return true;
}

int main() {
	srand(time(NULL));
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> x[i] >> y[i];
	}
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			dis[++cnt] = { i, j, calc(i, j) };
		}
	}
	Algorithm <Distance> algo;
	algo.quick_sort(dis + 1, cnt);

	for(int i = 1; i <= n; i++) {
		f[i] = i;
	}
	ll sum = 0;
	for(int i = 1; i <= cnt && n; i++) {
		if(merge(dis[i].a, dis[i].b)) {
			sum += dis[i].dis;
			n--;
		}
	}
	cout << sum << endl;
}