#include <iostream>
#include <string>
using namespace std;

namespace merchandise {
	class Merchandise {
	public:
		Merchandise();
		Merchandise(string, string);
		string getName() const;
		string getBrand() const;
		double getPrice() const;
		int getCount() const;
		void setName(string);
		void setBrand(string);
		void setPrice(double);
		void modifyCount(int);
		bool operator < (const Merchandise&) const;
		bool operator == (const Merchandise&) const;
		friend istream& operator >> (istream&, Merchandise&);
		friend ostream& operator << (ostream&, const Merchandise&); 
	private:
		string name, brand;
		double price;
		int count;
	};

	Merchandise::Merchandise() {
		name = brand = "";
		price = 0, count = 0;
	}
	Merchandise::Merchandise(string __name, string __brand) {
		name = __name, brand = __brand;
		price = 0, count = 0;
	}
	string Merchandise::getName() const {
		return name;
	}
	string Merchandise::getBrand() const {
		return brand;
	}
	double Merchandise::getPrice() const {
		return price;
	}
	int Merchandise::getCount() const {
		return count;
	}
	void Merchandise::setName(string __name) {
		name = __name;
	}
	void Merchandise::setBrand(string __brand) {
		brand = __brand;
	}
	void Merchandise::setPrice(double __price) {
		price = __price;
	}
	void Merchandise::modifyCount(int num) {
		count += num;
	}
	bool Merchandise::operator < (const Merchandise& other) const {
		return price < other.price;
	}
	bool Merchandise::operator == (const Merchandise& other) const {
		return (name + "," + brand) == (other.name + "," + other.brand);
	}
	istream& operator >> (istream& is, Merchandise& mer) {
		is >> mer.name >> mer.brand >> mer.price >> mer.count;
		return is;
	}
	ostream& operator << (ostream& os, const Merchandise& mer) {
		os << mer.name << ' ' << mer.brand << ' ' << mer.price << ' ' << mer.count;
		return os;
	}
} // namespace merchandise

namespace orderedlist {
	template <typename T>
	class OrderedList {
	public:
		OrderedList();
		~OrderedList();
		bool empty() const;
		void insert(T);
		void remove(T);
		void modify(T);
		T query(T t);
		void open(istream&);
		void save(ostream&);
	private:
		struct Node {
			T val;
			Node* nxt;
			Node();
			Node(T t);
		};
		Node* head;
	};
	template <typename T>
	OrderedList<T>::OrderedList() {
		head = nullptr;
	}
	template <typename T>
	OrderedList<T>::~OrderedList() {
		while(head != nullptr) {
			Node* node = head->nxt;
			delete head;
			head = node;
		}
	}
	template <typename T>
	OrderedList<T>::Node::Node() {
		nxt = nullptr;
	}
	template <typename T>
	OrderedList<T>::Node::Node(T t) {
		val = t, nxt = nullptr;
	}
	template <typename T>
	bool OrderedList<T>::empty() const {
		return nullptr == head;
	}
	template <typename T>
	void OrderedList<T>::insert(T t) {
		if(nullptr == head) {
			head = new Node(t);
			return;
		}
		Node *node = new Node(t);
		if(node->val < head->val) {
			node->nxt = head;
			head = node;
			return;
		}
		Node* pos = head;
		while(pos->nxt != nullptr && pos->nxt->val < node->val) {
			pos = pos->nxt;
		}
		node->nxt = pos->nxt;
		pos->nxt = node;
	}
	template <typename T>
	void OrderedList<T>::remove(T t) {
		if(head == nullptr) {
			return;
		}
		Node* pos = head;
		if(head->val == t) {
			pos = head->nxt;
			delete head;
			head = pos;
			return;
		}
		while(pos->nxt != nullptr) {
			if(pos->nxt->val == t) {
				Node* node = pos->nxt->nxt;
				delete pos->nxt;
				pos->nxt = node;
				return;
			}
			pos = pos->nxt;
		}
	}
	template <typename T>
	void OrderedList<T>::modify(T t) {}
	template <typename T>
	T OrderedList<T>::query(T t) {
		Node* pos = head;
		while(pos != nullptr) {
			if(pos->val == t) {
				return pos->val;
			}
			pos = pos->nxt;
		}
		return t;
	}
	template <typename T>
	void OrderedList<T>::open(istream& is) {
		T t;
		while(is >> t) {
			insert(t);
		}
	}
	template <typename T>
	void OrderedList<T>::save(ostream& os) {
		Node* pos = head;
		while(pos != nullptr) {
			os << pos->val << endl;
			pos = pos->nxt;
		}
	}
} // namespace orderedlist

template <>
void orderedlist::OrderedList<merchandise::Merchandise>::modify(merchandise::Merchandise mer) {
	Node* pos = head;
	while(pos != nullptr) {
		if(pos->val == mer) {
			if(mer.getCount() != 0) {
				pos->val.modifyCount(mer.getCount());
				if(pos->val.getCount() <= 0) {
					remove(mer);
				}
				return;
			}
			else {
				mer.modifyCount(pos->val.getCount());
				remove(mer);
				break;
			}
		}
		pos = pos->nxt;
	}
	insert(mer);
} 

enum STATE {
	EXIT = 0,
	WELCOME,
	START,
	FINISH,
	STOCK_ADD,
	STOCK_SUB,
	QUERY_NAME_BRAND,
	MODIFY_PRICE
};

string strs[] = {
	"Are you sure to exit?\n[Y/N]\n",
	"Welcome to XX Stock Management System!\nPlease tell me what you want to do:\n1.Start Business.\n\n0.Exit.\n",
	"1.Add Stock;\n2.Take out;\n3.Find;\n4.Modify;\n\n0.Finish.\n",
	"Are you sure to finish this day's work?\n[Y/N]\n",
	"Please input the information in different lines:\n1.Name;\n2.Brand;\n3.Amount;\n4.(If new, please enter it or just put zero)Price.\n",
	"Please input the information in different lines:\n1.Name;\n2.Brand;\n3.Amount;\n",
	"Please input the name and brand in different lines:\n1.name;\n2.brand.\n",
	"Please input the name and brand in different lines to adjust the price.\n1.Name;\n2.Brand;\n3.Price.\n"
};

#include <fstream>
#include <cstdlib>

int main() {
	orderedlist::OrderedList <merchandise::Merchandise> stocks;
	ifstream is;
	ofstream os;
	STATE state = WELCOME;
	while(true) {
		system("cls");
		cout << strs[(int)state];
		switch (state)
		{
		case EXIT:
		{
			char c;
			cin >> c;
			switch (c)
			{
			case 'Y': case 'y':
				return 0;
			case 'N': case 'n':
				state = WELCOME;
				break;
			
			default:
				break;
			}
		}
			break;
		case WELCOME:
		{
			int o;
			cin >> o;
			switch (o)
			{
			case 1: // start
				is.open("data.txt");
				stocks.open(is);
				is.close();
				state = START;
				break;
			case 0: // exit
				state = EXIT;
				break;
			
			default:
				break;
			}
		}
			break;
		case START:
		{
			stocks.save(cout);
			int o;
			cin >> o;
			switch (o)
			{
			case 1: // stock add
				state = STOCK_ADD;
				break;
			case 2: // stock sub
				state = STOCK_SUB;
				break;
			case 3: // query
				state = QUERY_NAME_BRAND;
				break;
			case 4: // modify
				state = MODIFY_PRICE;
				break;
			case 0: // finish
				state = FINISH;
				break;
			
			default:
				break;
			}
		}
			break;
		case FINISH:
		{
			char c;
			cin >> c;
			switch (c)
			{
			case 'Y': case 'y':
				os.open("data.txt");
				stocks.save(os);
				os.close();
				stocks.~OrderedList();
				state = WELCOME;
				break;
			case 'N': case 'n':
				state = START;
				break;
			
			default:
				break;
			}
		}
			break;
		case STOCK_ADD:
		{
			string name, brand;
			int amount;
			double price;
			cin >> name >> brand >> amount >> price;
			merchandise::Merchandise mer(name, brand);
			mer.modifyCount(amount);
			mer.setPrice(price);
			stocks.modify(mer);

			state = START;
		}
			break;
		case STOCK_SUB:
		{
			string name, brand;
			int amount;
			cin >> name >> brand >> amount;
			merchandise::Merchandise mer(name, brand);
			mer.modifyCount(-amount);
			stocks.modify(mer);

			state = START;
		}
			break;
		case QUERY_NAME_BRAND:
		{
			string name, brand;
			cin >> name >> brand;
			merchandise::Merchandise mer(name, brand);
			mer = stocks.query(mer);
			cout << mer << endl;

			getchar(); getchar();
			state = START;
		}
			break;
		case MODIFY_PRICE:
		{
			string name, brand;
			double price;
			cin >> name >> brand >> price;
			merchandise::Merchandise mer(name, brand);
			mer.setPrice(price);
			stocks.modify(mer);

			state = START;
		}
			break;
		default:
			break;
		}
	}
}