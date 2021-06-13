#include <iostream>
#include <cstring>
using namespace std;

int x, y, f, food_cnt, nxt_x, nxt_y, quad;

inline void move(int l) {
	l = (l > 0 ? l : -l);
	for(int i = 1; i <= l; i++) {
		putchar('f');
	}
}
void take_turn() {
	switch (quad)
	{
	case 0:
		switch (f)
		{
		case 0:
			move(nxt_y - y);
			putchar('c');
			f = 1;
			move(nxt_x - x);
			break;
		case 1:
			move(nxt_x - x);
			putchar('u');
			f = 0;
			move(nxt_y - y);
			break;
		case 2:
			putchar('u');
			f = 1;
			take_turn();
			break;
		case 3:
			putchar('c');
			f = 0;
			take_turn();
			break;

		default:
			break;
		}
		break;
	case 1:
		switch (f)
		{
		case 0:
			move(nxt_y - y);
			putchar('u');
			f = 3;
			move(nxt_x - x);
			break;
		case 1:
			putchar('u');
			f = 0;
			take_turn();
			break;
		case 2:
			putchar('c');
			f = 3;
			take_turn();
			break;
		case 3:
			move(nxt_x - x);
			putchar('c');
			f = 0;
			move(nxt_y - y);
			break;

		default:
			break;
		}
		break;
	case 2:
		switch (f)
		{
		case 0:
			putchar('u');
			f = 3;
			take_turn();
			break;
		case 1:
			putchar('c');
			f = 2;
			take_turn();
			break;
		case 2:
			move(nxt_y - y);
			putchar('c');
			f = 3;
			move(nxt_x - x);
			break;
		case 3:
			move(nxt_x - x);
			putchar('u');
			f = 2;
			move(nxt_y - y);
			break;
		
		default:
			break;
		}
		break;
	case 3:
		switch (f)
		{
		case 0:
			putchar('c');
			f = 1;
			take_turn();
			break;
		case 1:
			move(nxt_x - x);
			putchar('c');
			f = 2;
			move(nxt_y - y);
			break;
		case 2:
			move(nxt_y - y);
			putchar('u');
			f = 1;
			move(nxt_x - x);
			break;
		case 3:
			putchar('u');
			f = 2;
			take_turn();
			break;
		
		default:
			break;
		}
		break;

	default:
		break;
	}
	x = nxt_x, y = nxt_y;
}

int main() {
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while(t--) {
		cin >> x >> y >> f >> food_cnt;
		while(food_cnt--) {
			cin >> nxt_x >> nxt_y;
			quad = (((nxt_x < x) ^ (nxt_y < y)) + ((nxt_y < y) << 1));
			take_turn();
		}
		putchar('\n');
	}
}