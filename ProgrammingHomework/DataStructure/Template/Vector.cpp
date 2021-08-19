#include <assert.h>
#include <string.h>

template <typename T>
class Vector {
public:
	Vector();
	Vector(size_t);
	Vector(size_t, const T&);
	Vector(const Vector<T>&);
	~Vector();
	bool empty() const;
	size_t size() const;
	Vector<T>& operator =(const Vector<T>& other);
	T& operator [](size_t);
	const T& operator [](size_t) const;
	void push_back(const T&);
	void pop_back();
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	T* data();
	const T* data() const;
	void reverse(size_t, size_t);
	void clear();
private:
	T *vec;
	size_t vec_size, max_size;
	void swap(T&, T&);
};

template <typename T>
Vector <T>::Vector() {
	vec = new T[1];
	assert(vec != nullptr);
	vec_size = 0, max_size = 1;
}
template <typename T>
Vector <T>::Vector(size_t size_tmp) {
	vec = new T[size_tmp];
	assert(vec != nullptr);
	vec_size = size_tmp, max_size = size_tmp;
}
template <typename T>
Vector <T>::Vector(size_t size_tmp, const T& elem_tmp) {
	vec = new T[size_tmp];
	assert(vec != nullptr);
	vec_size = size_tmp, max_size = size_tmp;
	for(int i = 0; i < vec_size; i++) {
		vec[i] = elem_tmp;
	}
}
template <typename T>
Vector <T>::Vector(const Vector<T>& other) {
	vec = new T[other.max_size];
	assert(vec != nullptr);
	vec_size = other.vec_size, max_size = other.max_size;
	for(int i = 0; i < vec_size; i++) {
		vec[i] = other[i];
	}
}
template <typename T>
Vector <T>::~Vector() {
	delete[] vec;
	vec_size = 0, max_size = 0;
}
template <typename T>
bool Vector <T>::empty() const {
	return (vec_size == 0);
}
template <typename T>
size_t Vector <T>::size() const {
	return vec_size;
}
template <typename T>
Vector <T>& Vector <T>::operator =(const Vector<T>& other) {
	delete[] vec;
	vec = new T[other.max_size];
	vec_size = other.vec_size, max_size = other.max_size;
	for(int i = 0; i < vec_size; i++) {
		vec[i] = other[i];
	}
	return (*this);
}
template <typename T>
T& Vector<T>::operator [](size_t i) {
	assert(i < vec_size);
	return vec[i];
}
template <typename T>
const T& Vector<T>::operator [](size_t i) const {
	assert(i < vec_size);
	return vec[i];
}
template <typename T>
void Vector <T>::push_back(const T& elem) {
	if(vec_size == max_size) {
		T* vec_tmp = new T[max_size * 2];
		assert(vec_tmp != nullptr);
		memcpy(vec_tmp, vec, sizeof(T) * vec_size);
		max_size *= 2;
		delete[] vec;
		vec = vec_tmp;
	}
	vec[vec_size++] = elem;
}
template <typename T>
void Vector <T>::pop_back() {
	assert(vec_size > 0);
	vec_size--;
}
template <typename T>
T& Vector <T>::front() {
	assert(vec_size > 0);
	return vec[0];
}
template <typename T>
const T& Vector <T>::front() const {
	assert(vec_size > 0);
	return vec[0];
}
template <typename T>
T& Vector <T>::back() {
	assert(vec_size > 0);
	return vec[vec_size - 1];
}
template <typename T>
const T& Vector <T>::back() const {
	assert(vec_size > 0);
	return vec[vec_size - 1];
}
template <typename T>
T* Vector <T>::data() {
	return vec;
}
template <typename T>
const T* Vector <T>::data() const {
	return vec;
}
template <typename T>
void Vector <T>::reverse(size_t l, size_t r) {
	assert(l <= r), assert(l >= 0), assert(r < vec_size);
	while(l <= r) {
		swap(vec[l], vec[r]);
		l++, r--;
	}
}
template <typename T>
void Vector <T>::clear() {
	memset(vec, 0, sizeof(T) * vec_size);
	vec_size = 0;
}
template <typename T>
void Vector <T>::swap(T& a, T& b) {
	static T swap_tmp;
	swap_tmp = a;
	a = b;
	b = swap_tmp;
}

#include <iostream>
using namespace std;

int main() {
	Vector <int> a;
	Vector <int> b(10, 5);
	Vector <int> c(b);
	cout << "a is empty?" << endl << (a.empty() ? "yes" : "no") << endl;
	a.push_back(90);
	for(int i = 1; i <= 4; i++) {
		a.push_back(i);
	}
	cout << "elements of a: " << endl;
	auto print = [=](const Vector<int>& vec) {
		for(int i = 0; i < vec.size(); i++) {
			cout << vec[i] << ' ';
		}
		cout << endl;
	};
	print(a);
	// cout << "elements of b:" << endl;
	// print(b);
	// cout << "elements of c:" << endl;
	// print(c);
	// b.pop_back();
	// cout << "elements of b:" << endl;
	// print(b);
	// cout << "elements of c:" << endl;
	// print(c);
	c = a;
	a.pop_back();
	cout << "elements of c:" << endl;
	print(c);
	cout << "front of c:" << endl;
	cout << c.front() << endl;
	cout << "back of c:" << endl;
	cout << c.back() << endl;

	// c.reverse(0, c.size() - 1);
	c.clear();

	int* arr = c.data();
	for(int i = 0; i < c.size(); i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;
}