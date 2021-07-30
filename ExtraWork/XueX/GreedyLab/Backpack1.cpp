#include <iostream>
#include <algorithm>
using namespace std;
constexpr int MAXN = 1e3;

int n, cap;
double tot;
struct Object {
	int ind, weight, value;
	bool operator < (const Object& other) const {
		return value * other.weight < other.value * weight;
	}
} objects[MAXN];

int main() {
	cin >> n >> cap;
	for(int i = 0; i < n; i++) {
		objects[i].ind = i + 1;
		cin >> objects[i].weight;
	}
	for(int i = 0; i < n; i++) {
		cin >> objects[i].value;
	}
	sort(objects, objects + n);
	for(int i = n - 1; i >= 0; i--) {
		if(objects[i].weight <= cap) {
			cout << "Object No." << objects[i].ind
				<< ": weight " << objects[i].weight 
				<< ", value " << objects[i].value << endl;
			tot += objects[i].value;
			cap -= objects[i].weight;
		}
	}
	cout << "Total Value: " << tot << endl;
}
/*
Input:
7 150
35 30 60 50 40 10 25
10 40 30 50 35 40 30
Output:
Object No.6: weight 10, value 40
Object No.2: weight 30, value 40
Object No.7: weight 25, value 30
Object No.4: weight 50, value 50
Object No.1: weight 35, value 10
Total Value: 170
*/