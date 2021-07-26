#include <iostream>
using namespace std;
constexpr int MAXN = 1e2 + 10;
using ll = long long;

bool isPrime(ll x) {
	for(ll i = 2; i < x; i++) {
		if(x % i == 0) {
			return false;
		}
	}
	return true;
}

ll f(ll x) {
	for(ll i = x + 1; ; i++) {
		if(isPrime(i)) {
			return i;
		}
	}
}

int main() {
	for(int i = 1; i <= 100; i++) {
		cout << isPrime((f(i) + f(f(i))) / 2) << endl;
	}
}