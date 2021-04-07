#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    srand(time(NULL));
    freopen("Data.in", "w", stdout);
    int n = rand() % 100;
    cout << n << endl;
    vector <int> vec;
    while(n--) {
        int ope = rand() % 6 + 1, val, i;
        switch (ope)
        {
        case 1:
            val = rand() % 996 + 1;
            cout << ope << ' ' << val << endl;
            vec.push_back(val);
            break;
        case 2:
            if(vec.size() == 0) {
                n++;
                break;
            }
            i = rand() % vec.size();
            cout << ope << ' ' << vec[i] << endl;
            vec.erase(remove(vec.begin(), vec.end(), vec[i]), vec.end());
            break;
        case 3:
            if(vec.size() == 0) {
                n++;
                break;
            }
            i = rand() % vec.size();
            cout << ope << ' ' << vec[i] << endl;
            break;
        case 4:
            if(vec.size() == 0) {
                n++;
                break;
            }
            i = rand() % vec.size() + 1;
            cout << ope << ' ' << i << endl;
            break;
        case 5:
            if(vec.size() == 0) {
                n++;
                break;
            }
            i = rand() % vec.size();
            cout << ope << ' ' << vec[i] + rand() % vec[i] + 1 << endl;
            break;
        case 6:
            if(vec.size() == 0) {
                n++;
                break;
            }
            i = rand() % vec.size();
            cout << ope << ' ' << rand() % vec[i] - 1 << endl;
            break;
        
        default:
            break;
        }
    }
}