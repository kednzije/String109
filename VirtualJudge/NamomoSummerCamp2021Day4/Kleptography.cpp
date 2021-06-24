#include <iostream>
#include <string>
using namespace std;

inline int to_code(char c) {
	return c - 'a';
}
inline char to_char(int k) {
	return 'a' + k;
}

int main() {
	int n, m;
	cin >> n >> m;
	string plaintext, ciphertext;
	// cin >> plaintext >> ciphertext;

	// string s;
	// for(int i = 0; i < m; i++) {
	// 	s = to_char((to_code(ciphertext[m - 1 - i]) - to_code(ciphertext[m - 1 - i % n]) + to_code(plaintext[n - 1 - i % n])) % 26) + s;
	// }
	// cout << s << endl;

	cin >> plaintext;
	for(int i = 0; i < m; i++) {
		cout << to_char(to_code(plaintext[i]) + to_code(plaintext[(i - n + m) % m]) % 26);
	}
}