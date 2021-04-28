// 如果一个元素排序之后可以保持原方向，那么它必然满足：
// 1. 移动距离为偶数，那么排序前后位置的奇偶性不变；
// 2. 它前面不小于自己的数与后面不大于自己的数的和为偶数；
// 这两条中后一条比较容易理解，前一条比较容易判断
// 下面为证明：
// 不考虑自身移动，只主动移动其他元素，
// 可以发现移动的次数为：前面不小于自己的数与后面不大于自己的数的和，
// 设其分别为x，y。
// 再设排序前后位置为i，j，
// 那么移动距离即j - i = (i - x + y) - i = y - x
// 而x + y与y - x是模2同余的，故条件1与条件2等价
// 代码借鉴某博客，略有更改

// #include <iostream>
// #include <cstdio>
// #include <vector>
// #include <cstring>
// using namespace std;
// const int MAXN = 1e5 + 5;

// int nums[MAXN], order[MAXN], cnt[MAXN];
// void merge_sort(int l, int r) {
// 	if(l == r) {
// 		return;
// 	}
// 	int mid = (l + r) / 2;
// 	merge_sort(l, mid), merge_sort(mid + 1, r);
// 	vector <int> arr, ord;
// 	int i = l, j = mid + 1;
// 	while(i <= mid || j <= r) {
// 		if(i > mid) {
// 			ord.push_back(order[j]);
// 			cnt[order[j]] += mid - i + 1;
// 			arr.emplace_back(nums[j++]);
// 			continue;
// 		}
// 		if(j > r) {
// 			ord.push_back(order[i]);
// 			cnt[order[i]] += arr.size() - i + l;
// 			arr.emplace_back(nums[i++]);
// 			continue;
// 		}
// 		if(nums[i] <= nums[j]) {
// 			ord.push_back(order[i]);
// 			cnt[order[i]] += arr.size() - i + l;
// 			arr.emplace_back(nums[i++]);
// 		}
// 		else {
// 			ord.push_back(order[j]);
// 			cnt[order[j]] += mid - i + 1;
// 			arr.emplace_back(nums[j++]);
// 		}
// 	}
// 	for(int pos = l; pos <= r; pos++) {
// 		nums[pos] = arr[pos - l];
// 		order[pos] = ord[pos - l];
// 	}
// }

// int main() {
// 	int t;
// 	scanf("%d", &t);
// 	while(t--) {
// 		memset(nums, 0, sizeof(nums));
// 		memset(order, 0, sizeof(order));
// 		memset(cnt, 0, sizeof(cnt));

// 		int n;
// 		scanf("%d", &n);
// 		for(int i = 1; i <= n; i++) {
// 			scanf("%d", &nums[i]);
// 			order[i] = i;
// 		}
// 		merge_sort(1, n);
// 		bool isPossible = true;
// 		for(int i = 1; i <= n; i++) {
// 			if(cnt[i] % 2) {
// 				isPossible = false;
// 				break;
// 			}
// 		}
// 		if(isPossible) {
// 			printf("YES\n");
// 		}
// 		else {
// 			printf("NO\n");
// 		}
// 	}
// }

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
constexpr int N = 1e5 + 10;
int pos_before[N][2], pos_after[N][2], nums[N];
int main() {
    int t;
    // cin >> t;
	scanf("%d", &t);
    while (t--) {
		memset(pos_before, 0, sizeof(pos_before));
		memset(pos_after, 0, sizeof(pos_after));
		memset(nums, 0, sizeof(nums));
        int n;
        // cin >> n;
		scanf("%d", &n);
        // vector<int> a(n);
        for (int i = 0; i < n; i++) {
            // cin >> a[i];
			scanf("%d", &nums[i]);
        }
        // vector <vector <int>> pos_before(N, vector <int>(2));
        for (int i = 0; i < n; i++) {
            ++pos_before[nums[i]][i % 2];
        }
        // sort(a.begin(), a.end());
		sort(nums, nums + n);
        // vector <vector <int>> pos_after(N, vector <int>(2));
        for (int i = 0; i < n; i++) {
            ++pos_after[nums[i]][i % 2];
        }
        // cout << (pos_before == pos_after ? "Yes" : "No") << endl;
		auto equal = [&]() {
			for(int i = 0; i < n; i++) {
				if(pos_before[nums[i]][0] != pos_after[nums[i]][0]
					|| pos_before[nums[i]][1] != pos_after[nums[i]][1]) {
					return false;
				}
			}
			return true;
		};
		if(equal()) {
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}
    }
    return 0;
}