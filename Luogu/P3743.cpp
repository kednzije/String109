#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

const int MAX_NUM = 1e5;
const double EPS = 1e-5;
const double INF = 1e12;
inline double Abs(double k) {
    return k < 0 ? -k : k;
}
inline double Max(double a, double b) {
    return a > b ? a : b;
}
inline double Min(double a, double b) {
    return a < b ? a : b;
}

pair <int, int> data[MAX_NUM];

bool Check(double t, int n, double p) {
    for(int i = 0; i < n; i++) {
        if(p < 0) {
            break;
        }
        if(data[i].first * t > data[i].second) {
            p -= data[i].first * t - data[i].second;
        }
    }
    return p >= 0;
}

int main() {
    int n, p;
    cin >> n >> p;
    double tot = 0, l = INF, r = INF;
    for(int i = 0; i < n; i++) {
        cin >> data[i].first >> data[i].second;
        tot += data[i].first;
        l = Min(l, (double) data[i].second / data[i].first);
    }
    if(p >= tot) {
        cout << -1;
        return 0;
    }
    while(Abs(r - l) > EPS) {
        double mid = (l + r) / 2;
        if(Check(mid, n, mid * p)) {
            l = mid;
        }
        else {
            r = mid;
        }
    }
    cout << l << endl;
    return 0;
}