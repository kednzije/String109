#include <string>
#include <sstream>
#include <cmath>
using namespace std;

class Solution {
public:
    string smallestGoodBase(string n) {
        long long num = stoll(n);
        auto check = [=] (int k)->bool {
            long long _num = num;
            while(_num) {
                if(_num % k != 1) {
                    return false;
                }
                _num /= k;
            }
            return true;
        };
        for(int i = 59; i >= 2; i--) {
            long long k = pow(num, 1.0 / i);
            if(check(k)) {
                return to_string(k);
            }
        }
        return to_string(num - 1);
    }
};