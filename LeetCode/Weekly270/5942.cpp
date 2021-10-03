#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <set>
using namespace std;

class Solution {
public:
    vector<int> findEvenNumbers(vector<int>& digits) {
        int n = digits.size();
		vector <int> nums;
		set <int> nums_set;
		for(int i = 0; i < n; i++) {
			if(digits[i] == 0) {
				continue;
			}
			for(int j = 0; j < n; j++) {
				if(j == i) {
					continue;
				}
				for(int k = 0; k < n; k++) {
					if(k == i || k == j || digits[k] % 2 == 1) {
						continue;
					}
					nums_set.insert(digits[i] * 100 + digits[j] * 10 + digits[k]);
				}
			}
		}
		for(auto num: nums_set) {
			nums.push_back(num);
		}
		return nums;
    }
};