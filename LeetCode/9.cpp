#include <limits.h>
using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0) {
            return false;
        }
        int rev = x % 10, num = x;
        x /= 10;
        while(x) try {
            if((x > 0 && (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && x % 10 > INT_MAX % 10))) ||
                (x < 0 && (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && x % 10 < INT_MIN % 10)))) {
                throw -1;
            }
            rev = rev * 10 + x % 10;
            x /= 10;
        }
        catch(int) {
            return false;
        }
        return rev == num;
    }
};