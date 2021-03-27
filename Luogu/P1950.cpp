#include <iostream>
#include <deque>
using namespace std;
const int MAX_LEN = 1e3 + 5;
inline int Min(int a, int b) {
    return a < b ? a : b;
}

int n, m, max_height[MAX_LEN][MAX_LEN], l[MAX_LEN], r[MAX_LEN];
bool is_drawn[MAX_LEN][MAX_LEN];

void Push_back(deque <int> &deq, int i, int j, bool is_strictly, int arr[]) {
    if(deq.empty()) {
        deq.push_back(j);
    }
    else {
        while(!deq.empty() && (max_height[i][deq.back()] > max_height[i][j] 
            || (!is_strictly && max_height[i][deq.back()] == max_height[i][j]))) {
                arr[deq.back()] = j;
                deq.pop_back();
        }
        deq.push_back(j);
    }
}

int main() {
    cin >> n >> m;
    for(int i = 1;i <= n;i++) {
        for(int j = 1;j <= m;j++) {
            char c;
            cin >> c;
            is_drawn[i][j] = (c == '*');
        }
    }
    for(int i = 1;i <= n;i++) {
        for(int j = 1;j <= m;j++) {
            if(is_drawn[i][j]) {
                max_height[i][j] = 0;
            }
            else {
                max_height[i][j] = max_height[i - 1][j] + 1;
            }
        }
    }
    long long ans = 0;
    for(int i = 1;i <= n;i++) {
        deque <int> deq;
        max_height[i][0] = 0, max_height[i][m + 1] = -1;
        for(int j = 0;j <= m + 1;j++) {
            Push_back(deq, i, j, true, r);
        }
        deq.clear();
        for(int j = m + 1;j >= 0;j--) {
            Push_back(deq, i, j, false, l);
        }
        deq.clear();
        for(int j = 1;j <= m;j++) {
            ans += max_height[i][j] * (j - l[j]) * (r[j] - j);
        }
    }
    cout << ans << endl;
    return 0;
}