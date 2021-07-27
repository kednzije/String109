#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;
constexpr int MAXN = 100;

int hashTable[MAXN], asl[2];
int n, m, MOD;
int hashFunc(int key) {
	return key % MOD;
}

int hashTable_insert(int key) {
	int step = 1, pos = hashFunc(key);
	while(hashTable[pos]) {
		pos = (pos + 1) % n;
		step++;
	}
	hashTable[pos] = key;
	return step;
}
int hashTable_step2next(int i) {
	int step = 1;
	while(hashTable[i]) {
		i = (i + 1) % n;
		step++;
	}
	return step;
}
int hashTable_insert_2(int key) {
	int step = 0, pos = hashFunc(key);
	for(int i = 0; ; i++) {
		step++;
		if(!hashTable[(pos + i * i) % n]) {
			hashTable[(pos + i * i) % n] = key;
			break;
		}
		step++;
		if(!hashTable[(((pos - i * i) % n) + n) % n]) {
			hashTable[(((pos - i * i) % n) + n) % n] = key;
			break;
		}
	}
	return step;
}
int hashTable_step2next_2(int i) {
	int step = 0;
	for(int jmp_dis = 0; ; jmp_dis++) {
		step++;
		if(!hashTable[(i + jmp_dis * jmp_dis) % n]) {
			return step;
		}
		step++;
		if(!hashTable[(((i + jmp_dis * jmp_dis) % n) + n) % n]) {
			return step;
		}
	}
}

int main() {
	freopen("hashTest.txt", "r", stdin);
	freopen("hashTable.txt", "w", stdout);
	bool insert_2;
	while(true) {
		memset(hashTable, 0, sizeof(hashTable));
		memset(asl, 0, sizeof(asl));

		cin >> n >> m >> MOD >> insert_2;
		if(n == -1) {
			break;
		}

		for(int i = 0; i < m; i++) {
			int key;
			cin >> key;
			asl[0] += (insert_2 ? hashTable_insert_2(key) : hashTable_insert(key));
		}
		cout << "Hash Table: " << (insert_2 ? "insert_2" : "insert_normal") << endl;
		for(int i = 0; i < n; i++) {
			cout << i << '\t';
		}
		cout << endl;
		for(int i = 0; i < n; i++) {
			cout << hashTable[i] << '\t';
		}
		cout << endl;
		printf("ASL SUCCESS: %.6lf\n", 1.0 * asl[0] / m);
		for(int i = 0; i < n; i++) {
			asl[1] += (insert_2 ? hashTable_step2next_2(i) : hashTable_step2next(i));
		}
		printf("ASL FAILURE: %.6lf\n", 1.0 * asl[1] / n);
	}
}