#include <cstdio>
#include <cstdlib>
using namespace std;

int main() {
	freopen("data.txt", "w", stdout);

	int n = 1e6;
	printf("%d\n", n);
	int k = 114514;
	for(int i = 1; i <= n; i++) {
		printf("%d ", k);
	}
	printf("\n");
}