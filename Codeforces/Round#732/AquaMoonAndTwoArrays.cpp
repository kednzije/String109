#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <utility>
using namespace std;
const int MAXN = 105;

int nums[2][MAXN];
vector <pair <int, int>> steps;

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		memset(nums, 0, sizeof(nums));
		steps.clear();
		int sum=0, n;
		scanf("%d", &n);
		for(int i = 0; i < n; i++) {
			scanf("%d", &nums[0][i]);
			sum += nums[0][i];
		}
		for(int i = 0; i < n; i++) {
			scanf("%d", &nums[1][i]);
			sum -= nums[1][i];
		}
		if(sum) {
			printf("-1\n");
			continue;
		}
		for(int i = 0; i < n; i++) {
			int j = i + 1;
			while(nums[0][i] != nums[1][i]) {
				bool less = nums[0][i] < nums[1][i];
				if(nums[0][j] == nums[1][j]) {
					j++; 
					continue;
				}
				if((nums[0][j] < nums[1][j]) ^ less) {
					if(less) {
						nums[0][i]++, nums[0][j]--;
						steps.push_back(make_pair(j + 1, i + 1));
					}
					else {
						steps.push_back(make_pair(i + 1, j + 1));
						nums[0][i]--, nums[0][j]++;
					}
				}
				else {
					j++;
				}
			}
		}
		printf("%d\n", steps.size());
		for(auto& step: steps) {
			printf("%d %d\n", step.first, step.second);
		}
	}
}