#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
#include <cerrno>
#include <iterator>
#include <bitset>
using namespace std;
using ll = long long;
inline ll get_max(ll a, ll b) {
	return a > b ? a : b;
}
inline ll get_min(ll a, ll b) {
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
constexpr ll MAXN = 1e3 + 50;
constexpr ll INF = 923372036854775000ll;

struct Edge {
	int to, val, nxt;
} edges[MAXN * MAXN * 4];
int head[MAXN * MAXN], edge_index[MAXN * MAXN];
void add_edge(int u, int v, int w, int ind) {
	edges[++edges[0].val] = { v, w, head[u] };
	head[u] = edges[0].val;
	edge_index[edges[0].val] = ind;
}

int path[MAXN], switch_cost[MAXN], path_len[MAXN];

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

ll Dijkstra(int src, int dst, int num_of_pos, int num_of_layer) {
	static ll dis[MAXN * MAXN], n = num_of_pos / num_of_layer;
	static int pre_edge[MAXN * MAXN], pre_layer[MAXN * MAXN];
	static bool vis[MAXN * MAXN];
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, false, sizeof(vis));
	memset(pre_edge, -1, sizeof(pre_edge));
	memset(pre_layer, -1, sizeof(pre_layer));
	dis[src] = 0;

	static Heap <pair <ll, int>> que(MAXN * MAXN);
	for(int i = 1; i <= num_of_pos; i++) {
		que.insert({ dis[i], i });
	}
	while(!que.empty()) {
		pair <ll, int> pos = que.top();
		que.pop();
		if(vis[pos.second]) {
			continue;
		}
		vis[pos.second] = true;
		for(int i = head[pos.second]; i; i = edges[i].nxt) {
			int to = edges[i].to;
			if(vis[to]) {
				continue;
			}
			if((pos.second - 1) / n == (to - 1) / n && (pos.second - 1) / n == pre_layer[pos.second]
				&& pre_edge[pos.second] + 1 != edge_index[i]) {
				continue;
			}
			if(dis[to] > dis[pos.second] + edges[i].val) {
				dis[to] = dis[pos.second] + edges[i].val;
				que.insert({ dis[to], to });

				pre_edge[to] = edge_index[i];
				pre_layer[to] = (pos.second - 1) / n;
			}			
		}
	}
	return dis[dst];
}

int main() {
	int n, m, src, dst;
	n = input(), m = input(), src = input(), dst = input();

	for(int i = 1; i <= m; i++) {
		path_len[i] = input();
	}
	for(int i = 1; i <= m; i++) {
		switch_cost[i] = input();
	}

	for(int i = 1; i <= n; i++) {
		for(int k = 1; k <= m; k++) {
			add_edge(i, k * n + i, switch_cost[k], 0);
			add_edge(k * n + i, i, 0, 0);
		}
	}
	for(int k = 1; k <= m; k++) {
		int len = path_len[k], cost;
		for(int j = 1; j <= len; j++) {
			path[j] = input();
		}
		for(int j = 1; j < len; j++) {
			cost = input();
			add_edge(k * n + path[j], k * n + path[j + 1], cost, j);
		}
	}
	printf("%lld\n", Dijkstra(src, dst, n * (m + 1), m + 1));
	return 0;
}