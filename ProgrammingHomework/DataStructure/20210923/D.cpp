#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN = 1005;
constexpr int MAXK = 15;
#define QUESIZE 10

template <typename T>
class Queue {
private:
	T* que;
	int size, length, l, r;
public:
	Queue();
	~Queue();
	void push(T);
	void pop();
	bool empty() const;
	T head() const;
};

template <typename T>
Queue <T>::Queue() {
	que = new T[QUESIZE];
	size = 0, length = QUESIZE, l = r = 0;
}
template <typename T>
Queue <T>::~Queue() {
	delete que;
	size = 0, length = 0, l = r = 0;
}
template <typename T>
void Queue<T>::push(T elem) {
	if(r == length) {
		length += QUESIZE;
		T* __que = new T[length];
		for(int i = l; i < r; i++) {
			__que[i - l] = que[i];
		}
		delete que;
		que = __que;
		l = 0, r = size;
	}
	que[r++] = elem;
	size++;
}
template <typename T>
void Queue <T>::pop() {
	l++, size--;
}
template <typename T>
bool Queue<T>::empty() const {
	return size == 0;
}
template <typename T>
T Queue<T>::head() const {
	return que[l];
}

struct Position {
	int x, y, stepcnt;
	bool operator == (const Position& other) const {
		return x == other.x && y == other.y;
	}
};
char maze[MAXN][MAXN];
bool seen[MAXN][MAXN];
int k;
Position portal[MAXK];

const int to[4][2] = {
	1, 0,
	-1, 0,
	0, 1,
	0, -1,
};

int main() {
	memset(maze, 0, sizeof(maze));
	memset(seen, false, sizeof(seen));
	k = 0;

	Position a, b;
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> maze[i] + 1;
		for(int j = 1; j <= m; j++) {
			switch (maze[i][j])
			{
			case 'S':
				a = Position{i, j, 0};
				break;
			case 'E':
				b = Position{i, j, 0};
				break;
			case '*':
				portal[++k] = Position{i, j, 0};
				break;
			
			default:
				break;
			}
		}
	}

	Queue <Position> que;
	que.push(a);
	seen[a.x][a.y] = true;
	while(!que.empty()) {
		Position pos = que.head();
		que.pop();
		if(pos == b) {
			cout << pos.stepcnt << endl;
			return 0;
		}
		for(int i = 0; i < 4; i++) {
			int x = pos.x + to[i][0], y = pos.y + to[i][1];
			if(maze[x][y] != 0 && maze[x][y] != '1' && !seen[x][y]) {
				que.push(Position{x, y, pos.stepcnt + 1});
				seen[x][y] = true;
			}
		}
		if(maze[pos.x][pos.y] == '*' && k != 0) {
			for(int i = 1; i <= k; i++) {
				if(!seen[portal[i].x][portal[i].y]) {
					que.push(Position{portal[i].x, portal[i].y, pos.stepcnt + 1});
				}
			}
		}
	}
	cout << -1 << endl;
	return 0;
}