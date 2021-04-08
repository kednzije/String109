#include <string>
#include <sstream>
#include <algorithm>
#include <cstdlib>
using namespace std;

class Solution {
public:
    int reverse(int x) {
        int res = x % 10;
        x /= 10;
        while(x) try {
            if((x > 0 && (res > INT_MAX / 10 || (res == INT_MAX / 10 && x % 10 > INT_MAX % 10))) ||
                (x < 0 && (res < INT_MIN / 10 || (res == INT_MIN / 10 && x % 10 < INT_MIN % 10)))) {
                throw -1;
            }
            res = res * 10 + x % 10;
            x /= 10;
        }
        catch(int) {
            return 0;
        }
        return res;
    }
};