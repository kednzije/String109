#include <iostream>
using namespace std;
struct cards {
	int a, b;
	cards(int _a, int _b) {
		if(_a > _b) {
			swap(_a, _b);
		}
		a = _a, b = _b;
	}
	bool operator >= (const cards& that) {
		if(a == 2 && b == 8) {
			return true;
		}
		if(that.a == 2 && that.b == 8) {
			return false;
		}
		if(a == b) {
			if(that.a == that.b) {
				return a >= that.b;
			}
			return true;
		}
		if(that.a == that.b) {
			return false;
		}
		if((a + b) % 10 != (that.a + that.b) % 10) {
			return (a + b) % 10 >= (that.a + that.b) % 10;
		}
		return b >= that.b;
	}
};

int main() {
	int t;
	cin >> t;
	while(t--) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		cards first(a, b), second(c, d);
		if(first >= second && second >= first) {
			cout << "tie" << endl;
		}
		else if(first >= second) {
			cout << "first" << endl;
		}
		else {
			cout << "second" << endl;
		}
	}
}