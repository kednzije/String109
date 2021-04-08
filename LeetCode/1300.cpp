#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Solution {
public:
    int findBestValue(vector<int>& arr, int target) {
        arr.push_back(0);
        sort(arr.begin(), arr.end());
        int sum = 0, res = target * arr.size(), ans = 0, n = arr.size();;
        for(int i = 0; i < n - 1; i++) {
            sum += arr[i];
            for(int k = arr[i]; k < arr[i + 1]; k++) {
                int tmp = abs(sum + (n - i - 1) * k - target);
                if(res > tmp) {
                    res = tmp, ans = k;
                }
            }
        }
        if(res > abs(sum - target)) {
            res = abs(sum - target);
            ans = arr[n - 1];
        }
        return ans;
    }
};