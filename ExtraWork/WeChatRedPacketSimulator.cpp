#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
using namespace std;

int main() {
    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8);
    ofstream data("data.txt");
    cout << "请输入发红包次数：" << endl;
    int n;
    cin >> n;
    system("cls");
    cout << "发红包次数：" << n << endl;
    cout << "请输入红包个数：" << endl;
    int k;
    cin >> k;
    system("cls");
    cout << "发红包次数：" << n << endl;
    cout << "红包个数：" << k << endl;
    cout << "请输入红包金额：" << endl;
    double tot;
    cin >> tot;
    system("cls");
    cout << "发红包次数：" << n << endl;
    cout << "红包个数：" << k << endl;
    cout << "红包金额：" << showpoint << fixed << setprecision(2) << tot << endl;
    cout << "生成数据中..." << endl;
    for(int i = 1; i <= n; i++) {
        double _tot = tot;
        for(int j = 1; j <= k - 1; j++) {
            int money = rand() % ((int)((_tot / (k - j + 1)) * 200)) + 1;
            data << '#' << j << " : " << money / 100 << '.' << money % 100 << ' ';
            _tot -= money / 100.0;
        }
        data << '#' << k << " : " << showpoint << fixed << setprecision(2) << _tot << endl;
    }
    cout << "生成成功" << endl;
    getchar();getchar();
    return 0;
}