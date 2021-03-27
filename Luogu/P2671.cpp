#include <iostream>
using namespace std;
const int P = 10007;
const int MAX_LEN = 1e5;
#define COLOR 1
#define NUMBER 0

inline int Add(int a, int b) {
    return ((a % P) + (b % P)) % P;
}
inline int Mul(int a, int b) {
    return ((a % P) * (b % P)) % P;
}

int n, m;
int paperData[MAX_LEN][2], sum[MAX_LEN][2], cnt[MAX_LEN][2];

int main() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> paperData[i][NUMBER];
    }
    for(int i = 1; i <= n; i++) {
        cin >> paperData[i][COLOR];
    }
    for(int i = 1; i <= n; i++) {
        sum[paperData[i][COLOR]][i % 2] = Add(sum[paperData[i][COLOR]][i % 2], paperData[i][NUMBER]);
        cnt[paperData[i][COLOR]][i % 2]++;
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        ans = Add(ans, Mul(i, Add(sum[paperData[i][COLOR]][i % 2], 
            Mul(cnt[paperData[i][COLOR]][i % 2] - 2, paperData[i][NUMBER]))));
    }
    cout << ans << endl;
    return 0;
}