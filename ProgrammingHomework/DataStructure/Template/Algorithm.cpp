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