#include <iostream>
#include <algorithm>
using namespace std;
constexpr int MAXN = 1e3;

int n;
struct Object {
	int weight, value;
	double ratio;
	void calc() {
		ratio = 1.0 * value / weight;
	}
	bool operator < (const Object& other) const {
		return ratio < other.ratio;
	}
} objects[MAXN];

int main() {
	cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> objects[i].weight;
	}
	for(int i = 0; i < n; i++) {
		cin >> objects[i].value;
	}
	
	
}