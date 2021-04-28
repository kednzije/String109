#include <iostream>
using namespace std;

int prices[] = {0, 7, 27, 41, 49, 63, 78, 108};

int main() {
	int t;
	cin >> t;
	while(t--) {
		int n;
		cin >> n;
		int tot = 0;
		while(n--) {
			int i;
			cin >> i;
			tot += prices[i];
		}
		if(tot >= 120) {
			tot -= 50;
		}
		else if(tot >= 89) {
			tot -= 30;
		}
		else if(tot >= 69) {
			tot -= 15;
		}
		cout << tot << endl;
	}
}