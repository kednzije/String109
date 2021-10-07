template <typename T>
class Heap {
public:
	Heap();
	Heap(int);
	~Heap();
	int size() const;
	bool empty() const;
	bool insert(const T&);
	bool pop();
	const T& top() const;
private:
	T* arr;
	int elem_count, capacity;
	void swap(T&, T&);
	void percolate_up(int);
	void percolate_down(int);
};

template <typename T>
Heap<T>::Heap() {
	arr = new T[100];
	elem_count = 0, capacity = 100;
}
template <typename T>
Heap<T>::Heap(int size) {
	arr = new T[size + 1];
	elem_count = 0, capacity = size;
}
template <typename T>
Heap<T>::~Heap() {
	delete[] arr;
	elem_count = capacity = 0; 
}
template <typename T>
int Heap<T>::size() const {
	return elem_count;
}
template <typename T>
bool Heap<T>::empty() const {
	return 0 == elem_count;
}
template <typename T>
void Heap<T>::swap(T &a, T &b) {
	static T temp;
	temp = a;
	a = b;
	b = temp;
}
template <typename T>
void Heap<T>::percolate_up(int pos) {
	while(pos > 1 && arr[pos / 2] > arr[pos]) {
		swap(arr[pos / 2], arr[pos]);
		pos /= 2;
	}
}
template <typename T>
bool Heap<T>::insert(const T& elem) {
	if(elem_count == capacity) {
		return false;
	}

	arr[++elem_count] = elem;
	percolate_up(elem_count);

	return true;
}
template <typename T>
void Heap<T>::percolate_down(int pos) {
	while(pos * 2 <= elem_count) {
		int less = ((2 * pos + 1 <= elem_count && arr[2 * pos + 1] < arr[2 * pos]) ? (2 * pos + 1) : (2 * pos));
		if(arr[pos] < arr[less]) {
			break;
		}
		swap(arr[pos], arr[less]);
		pos = less;
	}
}
template <typename T>
bool Heap<T>::pop() {
	if(empty()) {
		return false;
	}

	swap(arr[1], arr[elem_count]);
	elem_count--;
	percolate_down(1);

	return true;
}
template <typename T>
const T& Heap<T>::top() const {
	return arr[1];
}