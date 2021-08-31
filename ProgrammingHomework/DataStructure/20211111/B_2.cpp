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

#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN = 1e5 + 10;

int n, a, b, ans[MAXN];
pair <int, int> nums[MAXN];

int main() {
	cin >> n >> a >> b;
	for(int i = 1; i <= n; i++) {
		cin >> nums[i].first;
		nums[i].second = i;
	}
	Algorithm <pair <int, int> > algo;
	algo.quick_sort(nums + 1, n);
	int l, r;
	memset(ans, -1, sizeof(ans));
	for(int i = 0; i < 4; i++) {
		l = 1, r = n;
		while(l <= r) {
			if(ans[l] != -1) {
				l++;
				continue;
			}
			if(ans[r] != -1) {
				r--;
				continue;
			}
			if(nums[l].first + nums[r].first == ((i & 1) ? b : a)) {
				ans[nums[l].second] = ans[nums[r].second] = (i & 1);
				l++, r--;
			}
			else if(nums[l].first + nums[r].first > ((i & 1) ? b : a)) {
				((i & 2) ? (l++) : (r--));
			}
			else {
				((i & 2) ? (r--) : (l++));
			}
		}
	}
	bool all_survive = true;
	for(int i = 1; i <= n; i++) {
		if(ans[i] == -1) {
			all_survive = false;
			break;
		}
	}
	cout << all_survive << endl;
	if(all_survive) {
		for(int i = 1; i <= n; i++) {
			cout << ans[i];
			if(i < n) {
				cout << ' ';
			}
		}
	}
}