#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN = 1e3 + 50;
using ll = long long;
constexpr ll INF = 1e9 + 7;
ll get_min(ll a, ll b) {
	return a < b ? a : b;
}
inline ll input() {
	ll num = 0, sign = 1;
	char c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-') {
			sign = -1;
		}
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		num = num * 10 + (c - '0');
		c = getchar();
	}
	return sign * num;
}
void swap(ll &a, ll &b) {
	static ll swap_helper;
	swap_helper = a;
	a = b;
	b = swap_helper;
}

ll n, m, edge[MAXN][MAXN], dis[MAXN], vis[MAXN];

template <typename T>
class Heap {
public:
	Heap();
	Heap(int);
	~Heap();
	int size() const;
	bool empty() const;
	bool insert(const T&);
	bool pop();
	const T& top() const;
private:
	T* arr;
	int elem_count, capacity;
	void swap(T&, T&);
	void percolate_up(int);
	void percolate_down(int);
};

template <typename T>
Heap<T>::Heap() {
	arr = new T[100];
	elem_count = 0, capacity = 100;
}
template <typename T>
Heap<T>::Heap(int size) {
	arr = new T[size + 1];
	elem_count = 0, capacity = size;
}
template <typename T>
Heap<T>::~Heap() {
	delete[] arr;
	elem_count = capacity = 0; 
}
template <typename T>
int Heap<T>::size() const {
	return elem_count;
}
template <typename T>
bool Heap<T>::empty() const {
	return 0 == elem_count;
}
template <typename T>
void Heap<T>::swap(T &a, T &b) {
	static T temp;
	temp = a;
	a = b;
	b = temp;
}
template <typename T>
void Heap<T>::percolate_up(int pos) {
	while(pos > 1 && arr[pos / 2] > arr[pos]) {
		swap(arr[pos / 2], arr[pos]);
		pos /= 2;
	}
}
template <typename T>
bool Heap<T>::insert(const T& elem) {
	if(elem_count == capacity) {
		return false;
	}

	arr[++elem_count] = elem;
	percolate_up(elem_count);

	return true;
}
template <typename T>
void Heap<T>::percolate_down(int pos) {
	while(pos * 2 <= elem_count) {
		int less = ((2 * pos + 1 <= elem_count && arr[2 * pos + 1] < arr[2 * pos]) ? (2 * pos + 1) : (2 * pos));
		if(arr[pos] < arr[less]) {
			break;
		}
		swap(arr[pos], arr[less]);
		pos = less;
	}
}
template <typename T>
bool Heap<T>::pop() {
	if(empty()) {
		return false;
	}

	swap(arr[1], arr[elem_count]);
	elem_count--;
	percolate_down(1);

	return true;
}
template <typename T>
const T& Heap<T>::top() const {
	return arr[1];
}
void Dijkstra(int src) {
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, false, sizeof(vis));
	dis[src] = 0;

	Heap <pair <ll, int>> que(MAXN * MAXN);
	for(int i = 1; i <= n; i++) {
		que.insert({ dis[i], i });
	}
	while(!que.empty()) {
		int pos = que.top().second;
		que.pop();
		vis[pos] = true;
		for(int i = 1; i <= n; i++) {
			if(vis[i]) {
				continue;
			}
			if(dis[i] > dis[pos] + edge[pos][i]) {
				dis[i] = dis[pos] + edge[pos][i];
				que.insert({ dis[i], i });
			}
		}
	}
}

int main() {
	// cin >> n >> m;
	n = input(), m = input();
	memset(edge, 0x3f, sizeof(edge));
	for(int i = 1; i <= n; i++) {
		edge[i][i] = 0;
	}
	for(int i = 1; i <= m; i++) {
		int u, v, w;
		// cin >> u >> v >> w;
		u = input(), v = input(), w = input();
		edge[u][v] = get_min(edge[u][v], w);
	}
	Dijkstra(1);
	ll sum = 0;
	for(int i = 1; i <= n; i++) {
		sum += dis[i];
	}
	for(int i = 1; i <= n; i++) {
		for(int j = i; j <= n; j++) {
			swap(edge[i][j], edge[j][i]);
		}
	}
	Dijkstra(1);
	for(int i = 1; i <= n; i++) {
		sum += dis[i];
	}
	cout << sum;
}