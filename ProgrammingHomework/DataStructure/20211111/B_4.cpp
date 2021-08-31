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
using namespace std;
constexpr int MAXN = 1e5 + 10;

int n, a, b, ans[MAXN];
pair <int, int> nums[MAXN];
bool vis[MAXN];
int find_index(int l, int r, int key) {
	if(l == r) {
		return (nums[l].first == key) ? l : -1;
	}
	int mid = (l + r) / 2;
	if(nums[mid].first < key) {
		return find_index(mid + 1, r, key);
	}
	else {
		return find_index(l, mid, key);
	}
}

int main() {
	cin >> n >> a >> b;
	// if(a > b) { // swap
	// 	a ^= b;
	// 	b ^= a;
	// 	a ^= b;
	// }
	for(int i = 1; i <= n; i++) {
		cin >> nums[i].first;
		nums[i].second = i;
	}
	Algorithm <pair <int, int>> algo;
	algo.quick_sort(nums + 1, n);
	bool all_survive =  true;
	for(int i = n; i >= 1; i--) {
		if(vis[i]) {
			continue;
		}
		static int index[2];
		index[0] = find_index(1, n, a - nums[i].first), index[1] = find_index(1, n, b - nums[i].first);
		if(index[0] != -1 && !vis[index[0]]) {
			ans[nums[i].second] = ans[nums[index[0]].second] = 0;
			vis[i] = vis[index[0]] = true;
		}
		else if(index[1] != -1 && !vis[index[1]]) {
			ans[nums[i].second] = ans[nums[index[1]].second] = 1;
			vis[i] = vis[index[1]] = true;
		}
		else {
			all_survive = false;
			break;
		}
	}
	cout << all_survive;
	if(all_survive) {
		cout << endl;
		for(int i = 1; i <= n; i++) {
			cout << ans[i];
			if(i < n) {
				cout << ' ';
			}
		}
	}
}