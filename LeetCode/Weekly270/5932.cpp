#include <vector>
#include <utility>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
		map <int, vector <int>> edges;
		map <int, int> in_degree, out_degree;
		for(auto &vec: pairs) {
			edges[vec[0]].push_back(vec[1]);
			in_degree[vec[1]]++;
			out_degree[vec[0]]++;
		}
		int head = pairs[0][0];
		for(auto &vec: pairs) {
			if(in_degree[vec[0]] + 1 == out_degree[vec[0]]) {
				head = vec[0];
				break;
			}
		}
		vector <vector <int>> perm;
		for(int edge_cnt = 1; edge_cnt <= pairs.size(); edge_cnt++) {
			perm.push_back({ head, edges[head][out_degree[head] - 1] });
			head = edges[head][--out_degree[head]];
		}
		return perm;
    }
};

int main() {
	Solution sol;
	vector <vector <int>> vec = {
		{ 1, 2 },
		{ 1, 3 },
		{ 2, 1 }
	};
	vec = sol.validArrangement(vec);
}