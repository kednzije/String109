#include <bits/stdc++.h>
using namespace std;

class Solution { // Discretization & BFS
	const int max_pos = 1e6 - 1;
	set <int> row, col;
	set <pair <int, int>> blocked_set;
	map <int, int> row_ind, col_ind;
	bool bfs(const vector<int>& source, const vector<int>& target) {
		const int to[4][2] = {
			1, 0,
			0, -1,
			-1, 0,
			0, 1
		};
		queue <pair <int, int>> que;
		set <pair <int, int>> vis;
		auto in_board = [=](int pos_x, int pos_y)->bool {
			return pos_x >= 1 && pos_y >= 1 && pos_x <= row_ind[max_pos] && pos_y <= col_ind[max_pos];
		};
		
		que.push({ row_ind[source[0]], col_ind[source[1]] });
		vis.insert(que.back());
		while(!que.empty()) {
			pair <int, int> pos = que.front();
			que.pop();
			if(pos.first == row_ind[target[0]] && pos.second == col_ind[target[1]]) {
				return true;
			}
			for(int i = 0; i < 4; i++) {
				int x = pos.first + to[i][0], y = pos.second + to[i][1];
				if(!in_board(x, y) || blocked_set.count({ x, y }) != 0 || vis.count({ x, y }) != 0) {
					continue;
				}
				que.push({ x, y });
				vis.insert(que.back());
			}
		}
		return false;
	}
public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
		row.insert(0), col.insert(0), row.insert(max_pos), col.insert(max_pos);
		row.insert(source[0]), row.insert(target[0]);
		col.insert(source[1]), col.insert(target[1]);
		for(auto &vec: blocked) {
			row.insert(vec[0]), col.insert(vec[1]);
		}
		int ind, last;
		ind = 0, last = -1;
		for(auto r: row) {
			row_ind[r] = ++ind;
			if(r > last + 1) {
				row_ind[r] = ++ind;
			}

			last = r;
		}
		ind = 0, last = -1;
		for(auto c: col) {
			col_ind[c] = ++ind;
			if(c > last + 1) {
				col_ind[c] = ++ind;
			}

			last = c;
		}
		for(auto &vec: blocked) {
			blocked_set.insert({ row_ind[vec[0]], col_ind[vec[1]] });
		}
		return bfs(source, target);
    }
};