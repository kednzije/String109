#include <vector>
using namespace std;

class Solution {
public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
        int n = jobs.size();
        vector<int> sum(1 << n);

        // 计算完成子集x的工作量x所需时间sum[x]
        for (int i = 1; i < (1 << n); i++) {
            // __builtin_ctz(i)返回i的二进制下末尾的0的个数
            int x = __builtin_ctz(i), y = i - (1 << x);
            sum[i] = sum[y] + jobs[x];
        }

        vector<vector<int>> dp(k, vector<int>(1 << n));

        // 第0个工人完成子集i的最小工作时间即子集i的工作量之和
        for (int i = 0; i < (1 << n); i++) {
            dp[0][i] = sum[i];
        }

        for (int i = 1; i < k; i++) {
            for (int j = 0; j < (1 << n); j++) {
                // 前i个工人完成子集j的最小工作时间
                // 即“前i-1个工人完成子集x的最小工作时间”与“第i个工人完成子集j-x的工作量”中较大者的最小值
                // 其中子集x包含于子集j

                int minn = INT_MAX;
                for (int x = j; x; x = (x - 1) & j) {
                    minn = min(minn, max(dp[i - 1][j - x], sum[x]));
                }
                dp[i][j] = minn;
            }
        }
        return dp[k - 1][(1 << n) - 1];
    }
};