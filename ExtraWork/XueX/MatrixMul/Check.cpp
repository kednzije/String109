#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;
constexpr int RANGE = 50;

int sizes[] = { 50, 100, 200, 500, 1000 };
#define N (sizeof(sizes) / sizeof(int))

int main() {
	srand(time(NULL));
	ofstream of;
	for(int test = 0; test < N; test++) {
		of.open("data.txt");
		int n = sizes[test];
		of << n << endl;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				of << (rand() % RANGE) * (rand() % 2 ? 1 : -1) << ' ';
			}
		}
		of << endl;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				of << (rand() % RANGE) * (rand() % 2 ? 1 : -1) << ' ';
			}
		}
		of.close();
		cout << "Size: " << n << endl;
		cout << "Strassen: " << endl;
		double start = clock();
		system("Strassen.exe");
		double end = clock();
		cout << "Time used: " << end - start << endl;
		cout << "Force: " << endl;
		start = clock();
		system("MatrixMul.exe");
		end = clock();
		cout << "Time used: " << end - start << endl;
		if(system("fc res0.txt res1.txt")) {
			cout << "Wrong Answer!" << endl;
		}
	}
	getchar(), getchar();
}