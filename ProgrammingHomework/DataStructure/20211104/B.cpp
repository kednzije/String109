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
using ll = long long;

struct Card {
	ll nums[2], sum;
	void calc() {
		sum = nums[0] + nums[1];
	}
	bool operator < (const Card& other) const {
		return sum > other.sum;
	}
} cards[MAXN];

int main() {
	Algorithm <Card> algo;
	int n;
	cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> cards[i].nums[0];
	}
	for(int i = 0; i < n; i++) {
		cin >> cards[i].nums[1];
		cards[i].calc();
	}
	algo.quick_sort(cards, n);
	ll res[2] = { 0, 0 };
	for(int i = 0; i < n; i++) {
		res[i % 2] += cards[i].nums[i % 2];
	}
	int whowin = (res[0] > res[1] ? 1 : (res[0] < res[1] ? -1 : 0));
	cout << whowin << endl;
}