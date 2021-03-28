#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
const int MAXLEN = 105;

bool isVowel(char c) {
    return (c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u');
}

int main() {
    int n;
    cin >> n;
    while(n--) {
        string str;
        int k;
        cin >> str >> k;
        vector <int> vec;
        for(int i = 0;i < str.length();i++) {
            if(isVowel(str[i])) {
                vec.push_back(i);
            }
        }
        int ind = 0;
        for(int i = 0;i < str.length();i++) {
            if(isVowel(str[i])) {
                cout << str[vec[(ind + k) % vec.size()]];
                ind++;
            }
            else {
                cout << str[i];
            }
        }
        cout << endl;
    }
    return 0;
}