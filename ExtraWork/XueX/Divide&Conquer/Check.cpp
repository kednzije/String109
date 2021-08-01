#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;
constexpr int RANGE = 50;

int sizes[] = { 100, 1000 };
#define N (sizeof(sizes) / sizeof(int))

int main() {
	srand(time(NULL));
	ofstream of;
	for(int test = 0; test < N; test++) {
		of.open("input.txt");
		int n = sizes[test];
		of << n << endl;
		for(int i = 0; i < n; i++) {
			of << (rand() % RANGE) * (rand() % 2 ? 1 : -1) << ' ';
		}
		of.close();
		cout << "Size: " << n << endl;
		cout << "Divide&Conquer: " << endl;
		double start = clock();
		system("MaxSum_F.exe");
		double end = clock();
		cout << "Time used: " << end - start << endl;
		cout << "Force: " << endl;
		start = clock();
		system("MaxSum_FX.exe");
		end = clock();
		cout << "Time used: " << end - start << endl;
	}
	getchar(), getchar();
}