// 二分答案
#include <iostream>
using namespace std;
const int MAX_ARRAY_LEN = 1e5;
const int INF = 1e9 + 10;
inline int Max(int a, int b) {
    return a > b ? a : b;
}
inline int Min(int a, int b) {
    return a < b ? a : b;
}

int n, m, num[MAX_ARRAY_LEN + 1];

int Check(int tot) {
    int cnt = 1, tmp = 0;
    for(int i = 1; i <= n; i++) {
        tmp += num[i];
        if(tmp > tot) {
            cnt++;
            tmp = num[i];
        }
    }
    return cnt;
}

int main() {
    cin >> n >> m;
    int maxNum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> num[i];
        maxNum = Max(maxNum, num[i]);
    }
    int l = maxNum, r = INF;
    while(l < r) {
        int mid = (l + r) / 2;
        if(Check(mid) > m) {
            l = mid + 1;
        }
        else {
            r = mid;
        }
    }
    cout << l << endl;
    return 0;
}