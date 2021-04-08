#include <vector>
#include <set>
#include <queue>
#include <utility>
using namespace std;

class Solution {
public:
    bool canCross(vector<int>& stones) {
        set <int> _stones;
        for(int i = 0; i < stones.size(); i++) {
            _stones.insert(stones[i]);
        }
        set <pair <int, int>> is_searched;
        queue <pair <int, int>> que;
        if(stones[1] == 1) {
            que.push(make_pair(1, 1));
            is_searched.insert(make_pair(1, 1));
        }
        while(!que.empty()) {
            pair <int, int> q = que.front();
            que.pop();
            if(q.first == stones[stones.size() - 1]) {
                return true;
            }
            for(int i = -1; i <= 1; i++) {
                if(q.second + i > 0
                    && _stones.find(q.first + q.second + i) != _stones.end()
                    && is_searched.find(make_pair(q.first + q.second + i, q.second + i)) == is_searched.end()) {
                    que.push(make_pair(q.first + q.second + i, q.second + i));
                    is_searched.insert(make_pair(q.first + q.second + i, q.second + i));
                }
            }
        }
        return false;
    }
};