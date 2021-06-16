#include <iostream>
#include <queue>
#include <cstdio>
#include <vector>
#include <map>
using namespace std;

#define		DIR_N 		0
#define 	DIR_E 		1
#define 	DIR_S 		2
#define		DIR_W 		3
#define		N_to_N	 	0
#define 	N_to_E	 	1
#define 	N_to_S	 	2
#define		N_to_W	 	3
#define		E_to_N	 	4
#define 	E_to_E	 	5
#define 	E_to_S	 	6
#define		E_to_W	 	7
#define		S_to_N	 	8
#define 	S_to_E	 	9
#define 	S_to_S	 	10
#define		S_to_W	 	11
#define		W_to_N	 	12
#define 	W_to_E	 	13
#define 	W_to_S	 	14
#define		W_to_W	 	15

#define		to(x, y)	((x * 4) + y)

vector <int> cars;
map <vector <int>, int> seen;
queue <vector <int>> que;

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		cars.clear(), seen.clear();
		for(int i = 0; i < 16; i++) {
			int car_num;
			scanf("%d", &car_num);
			cars.emplace_back(car_num);
		}

		while(!que.empty()) {
			que.pop();
		}

		seen[cars] = 0;
		que.push(cars);

		auto check_zero = [](vector <int> now) {
			for(int i = 0; i < 16; i++) {
				if(now[i] > 0) {
					return false;
				}
			}
			return true;
		};

		while(!que.empty()) {
			vector <int> now = que.front(), nxt;
			if(check_zero(now)) {
				printf("%d\n", seen[now]);
				break;
			}
			que.pop();

			int time_cost_nxt = seen[now] + 1;
			for(int dir_fwd = 0; dir_fwd < 4; dir_fwd++) {
				int dir_lft = (dir_fwd + 3) % 4, dir_rgt = (dir_fwd + 1) % 4, dir_bck = (dir_fwd + 2) % 4;
				{
					nxt = now;
					
					if(nxt[S_to_E] > 0) {
						nxt[S_to_E]--;
					}
					if(nxt[E_to_N] > 0) {
						nxt[E_to_N]--;
					}
					if(nxt[N_to_W] > 0) {
						nxt[N_to_W]--;
					}
					if(nxt[W_to_S] > 0) {
						nxt[W_to_S]--;	
					}
					
					if(nxt[to(dir_bck, dir_fwd)] > 0) {
						nxt[to(dir_bck, dir_fwd)]--;
					}
					if(nxt[to(dir_fwd, dir_bck)] > 0) {
						nxt[to(dir_fwd, dir_bck)]--;
					}

					if(seen.count(nxt) != 1) {
						seen[nxt] = time_cost_nxt;
						que.push(nxt);
					}
				}
				{
					nxt = now;
					
					if(nxt[S_to_E] > 0) {
						nxt[S_to_E]--;
					}
					if(nxt[E_to_N] > 0) {
						nxt[E_to_N]--;
					}
					if(nxt[N_to_W] > 0) {
						nxt[N_to_W]--;
					}
					if(nxt[W_to_S] > 0) {
						nxt[W_to_S]--;	
					}
					
					if(nxt[to(dir_bck, dir_fwd)] > 0) {
						nxt[to(dir_bck, dir_fwd)]--;
					}
					if(nxt[to(dir_bck, dir_lft)] > 0) {
						nxt[to(dir_bck, dir_lft)]--;
					}

					if(seen.count(nxt) != 1) {
						seen[nxt] = time_cost_nxt;
						que.push(nxt);
					}
				}
				{
					nxt = now;
					
					if(nxt[S_to_E] > 0) {
						nxt[S_to_E]--;
					}
					if(nxt[E_to_N] > 0) {
						nxt[E_to_N]--;
					}
					if(nxt[N_to_W] > 0) {
						nxt[N_to_W]--;
					}
					if(nxt[W_to_S] > 0) {
						nxt[W_to_S]--;	
					}
					
					if(nxt[to(dir_bck, dir_fwd)] > 0) {
						nxt[to(dir_bck, dir_fwd)]--;
					}
					if(nxt[to(dir_lft, dir_fwd)] > 0) {
						nxt[to(dir_lft, dir_fwd)]--;
					}

					if(seen.count(nxt) != 1) {
						seen[nxt] = time_cost_nxt;
						que.push(nxt);
					}
				}
				{
					nxt = now;
					
					if(nxt[S_to_E] > 0) {
						nxt[S_to_E]--;
					}
					if(nxt[E_to_N] > 0) {
						nxt[E_to_N]--;
					}
					if(nxt[N_to_W] > 0) {
						nxt[N_to_W]--;
					}
					if(nxt[W_to_S] > 0) {
						nxt[W_to_S]--;	
					}
					
					if(nxt[to(dir_bck, dir_lft)] > 0) {
						nxt[to(dir_bck, dir_lft)]--;
					}
					if(nxt[to(dir_fwd, dir_rgt)] > 0) {
						nxt[to(dir_fwd, dir_rgt)]--;
					}

					if(seen.count(nxt) != 1) {
						seen[nxt] = time_cost_nxt;
						que.push(nxt);
					}
				}
			}
		}
	}
}