/**
 * @file SA.cpp
 * @author String
 * @brief SA, used to find the max calc(k)
 * @version 0.1
 * @date 2021-11-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;
#define DELTA (0.999)
#define ZERO (1e-3)
#define EPS (1e-7)
 
double calc(double k) {
	return k; // A Function
}
 
int main() {
	srand(time(NULL));
	int n;
	scanf("%d", &n);
	while(n--) {
		//scanf()
		double T = 1000.0;
		double ans = 0.0, x = 0.0;
		while(T > ZERO) {
			double __x = x + ((rand() * 2) - RAND_MAX) * T;
			double k = calc(__x) - ans;
			if(k > 0) {
				ans = k, x = __x;
			} else {
				if(exp(-k / T) * RAND_MAX > rand()) {
					x = __x;
				}
			}
			T *= DELTA;
		}
		printf("%.5lf\n", ans);
	}
	return 0;
}