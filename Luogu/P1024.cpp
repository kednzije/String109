#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
using namespace std;
const double EPS = 0.001;
inline double Pow(double base, int expo) {
    double res = 1.0;
    for(int i = 1; i <= expo; i++) {
        res *= base;
    }
    return res;
}
inline double Abs(double k) {
    return k > 0 ? k : -k;
}

double a, b, c, d;
double calc(double x) {
    return a * Pow(x, 3) + b * Pow(x, 2) + c * x + d;
}
double Solve(double l, double r) {
    double mid = (l + r) / 2;
    if(Abs(calc(mid)) < EPS) {
        return mid;
    }
    else if(calc(mid) > 0) {
        return Solve(l, mid);
    }
    else {
        return Solve(mid, r);
    }
}

int main() {
    cin >> a >> b >> c >> d;
    for(double i = -100; i <= 100; i++) {
        if(calc(i - 0.6) * calc(i + 0.6) < 0) {
            double ans;
            if(calc(i - 0.6) < 0) {
                ans = Solve(i - 0.6, i + 0.6);
            }
            else {
                ans = Solve(i + 0.6, i - 0.6);
            }
            i = ans;
            printf("%.2f ", ans);
        }
    }
    cout << endl;
    return 0;
}