#include <cmath>

class Solution {
public:
    bool judgeSquareSum(int c) {
        for(int i = 0; i <= ceil(sqrt(c)); i++) {
            int k = c - i * i;
            if((int)sqrt(k) * (int)sqrt(k) == k) {
                return true;
            }
        }
        return false;
    }
};