template <typename T>
class List {
public:
	List();
	~List();
	bool empty() const;
private:
	struct Node {
		T val;
		Node* nxt;
	};
	Node* head;
};