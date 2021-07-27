#include <iostream>
using namespace std;

int main() {
	for(int i = 0; ; i++) {
		int tmp = (1 + i * i) % 11;
		if(tmp == 0 || tmp == 8 || tmp == 9) {
			cout << i;
			return 0;
		}
	}
}