#include <iostream>
#include <cstdio>
#include <utility>
using namespace std;

inline int sqr(int num) {
	return num * num;
}

int main() {
	int n, k;
	cin >> n >> k; k--;
	int x=1, y=1;
	pair <int, int> dx(1, 0), dy(0, 1);
	while(n > 1) {
		switch (k / sqr(n / 2))
		{
		case 0:
			swap(dx, dy);
			break;
		case 1:
			y += dx.second * n / 2 + dy.second * n / 2;
			break;
		case 2:
			x += dx.first * n / 2 + dy.first * n / 2;
			y += dx.second * n / 2 + dy.second * n / 2;
			break;
		case 3:
			x += dx.first * (n - 1) + dy.first * (n - 1);
			y += dx.second * (n / 2 - 1) + dy.second * (n / 2 - 1);
			swap(dx, dy);
			dx.first = -dx.first, dx.second = -dx.second;
			dy.first = -dy.first, dy.second = -dy.second;
			break;
		default:
			break;
		}

		n /= 2;
		if(n == 1) {
			switch (k % 4)
			{
			case 0:
				swap(dx, dy);
				break;
			case 1:
				y += dx.second + dy.second;
				break;
			case 2:
				y += dx.second + dy.second;
				break;
			case 3:
				x += dx.first + dy.first;
				break;
			default:
				break;
			}
		}
	}
	cout << x << ' ' << y << endl;
}