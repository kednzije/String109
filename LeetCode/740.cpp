#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        vector <int> n = nums;
        sort(n.begin(), n.end());
        int score = 0, rec0 = 0, rec1 = 0;
        for(int i = 0; i < n.size();) {
            int j;
            for(j = i + 1; j < n.size() && n[j] == n[i]; j++);

            if(i == 0 || n[i] > n[i - 1] + 1) {
                rec0 = max(rec0, rec1);
                rec1 = rec0 + (j - i) * n[i];
            }
            else {
                int tmp = rec0;
                rec0 = max(rec0, rec1);
                rec1 = tmp + (j - i) * n[i];
            }

            i = j;
        }
        score = max(rec0, rec1);
        return score;
    }
};