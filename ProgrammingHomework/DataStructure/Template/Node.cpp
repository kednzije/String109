template <typename T>
class Node {
public:
	Node();
	~Node();
	Node(T t);
	void setVal(T);
	void setNxt(Node<T>*);
	T getVal() const;
	Node<T>* getNxt() const;
private:
	T val;
	Node* nxt;
};

template <typename T>
Node<T>::Node() {
	nxt = nullptr;
}
template <typename T>
Node<T>::~Node() {}
template <typename T>
Node<T>::Node(T t) {
	val = t;
}
template <typename T>
void Node<T>::setVal(T t) {
	val = t;
}
template <typename T>
void Node<T>::setNxt(Node<T>* node) {
	nxt = node;
}
template <typename T>
T Node<T>::getVal() const {
	return val;
}
template <typename T>
Node<T>* Node<T>::getNxt() const {
	return nxt;
}