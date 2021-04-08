#include <vector>
#include <utility>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int num_wanted, int use_limit) {
        vector <pair <int, int>> elements;
        for(int i = 0; i < values.size(); i++) {
            elements.push_back(make_pair(values[i], labels[i]));
        }
        auto cmp = [&] (pair <int, int> a, pair <int, int> b)->bool {
            return a.first > b.first;
        };
        sort(elements.begin(), elements.end(), cmp);
        map <int, int> cnt;
        for(int i = 0; i < labels.size(); i++) {
            cnt[labels[i]] = 0;
        }
        int selected_cnt = 0, ind = 0, res = 0;
        while(selected_cnt < num_wanted && ind < elements.size()) {
            if(cnt[elements[ind].second] < use_limit) {
                res += elements[ind].first;
                cnt[elements[ind].second]++;
                selected_cnt++;
            }
            ind++;
        }
        return res;
    }
};