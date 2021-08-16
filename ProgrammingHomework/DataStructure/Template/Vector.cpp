#include <assert.h>
#include <stdlib.h>

template <typename T>
class Vector {
public:
	Vector();
	Vector(size_t);
	Vector(size_t, const T&);
	Vector(const Vector&);
	~Vector();
	bool empty() const;
	size_t size() const;
	T& operator [](unsigned int i);
	const T& operator [](unsigned int i) const;
	void push_back(const T& elem);
	void pop_back();
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	void clear();
private:
	T *vec;
	size_t vec_size, max_size;
};

template <typename T>
Vector <T>::Vector() {
	vec = new T[1];
	vec_size = 0, max_size = 1;
}
template <typename T>
Vector <T>::Vector(size_t size_tmp) {
	vec = new T[size_tmp];
	vec_size = size_tmp, max_size = size_tmp;
}
template <typename T>
Vector <T>::Vector(size_t size_tmp, const T& elem_tmp) {
	vec = new T[size_tmp];
	vec_size = size_tmp, max_size = size_tmp;
	for(int i = 0; i < vec_size; i++) {
		vec[i] = elem_tmp;
	}
}
