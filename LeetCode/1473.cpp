#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        // int*** dp = new int**[m + 1];
        // for(int i = 0; i <= m; i++) {
        //     dp[i] = new int*[n + 1];
        //     for(int j = 0; j <= n; j++) {
        //         dp[i][j] = new int[target + 1];
        //     }
        // }
        vector <vector <vector <int>>> dp(m + 1, vector<vector <int>>(n + 1, vector<int>(target + 1, 0)));

        for(int j = 1; j <= m; j++) {
            dp[0][j][0] = 0;
            for(int k = 1; k <= target; k++) {
                dp[0][j][k] = INT_MAX;
            }
        }
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                for(int k = 1; k <= target; k++) {
                    if(houses[i - 1] && houses[i - 1] != j) {
                        dp[i][j][k] = INT_MAX;
                    }
                    int minCost = INT_MAX;
                    for(int _j = 1; _j <= n; _j++) {
                        if(_j == j) {
                            continue;
                        }
                        minCost = min(minCost, dp[i - 1][_j][k - 1]);
                    }
                    dp[i][j][k] = min(minCost, dp[i - 1][j][k]);
                    if(!houses[i - 1] && dp[i][j][k] < INT_MAX) {
                        dp[i][j][k] += cost[i - 1][j - 1];
                    }
                }
            }
        }
        int ans = INT_MAX;
        for(int j = 1; j <= n; j++) {
            ans = min(ans, dp[n][j][target]);
        }

        // for(int i = 0; i <= m; i++) {
        //     for(int j = 0; j <= n; j++) {
        //         delete dp[i][j];
        //     }
        //     delete dp[i];
        // }
        // delete dp;

        return ans;
    }
};