#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {
    int cnt = 0;
    while(++cnt) {
        cout << "Passed: " << cnt - 1 << endl;
        cout << "Making data...\n";
        system("MakeData.exe");
        cout << "Data is ready.\n";
        system("AcceptedRes.exe");
        cout << "Answer is ready.\n";
        double start = clock();
        system("WrongRes.exe");
        double end = clock();
        if(system("fc WrongRes.out AcceptedRes.out")) {
            printf("WA time used: %.4lfms\n");
            getchar();
            return 0;
        }
        else {
            printf("AC time used: %.4lfms\n");
        }
    }
    return 0;
}