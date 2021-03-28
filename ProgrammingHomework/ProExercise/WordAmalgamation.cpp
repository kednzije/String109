#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    map <string, vector<string>> dic;
    map <string, vector<string>>::iterator iter;
    string str;
    bool shouldBreak = false;
    while(true) {
        cin >> str;
        if(str == "XXXXXX") {
            if(shouldBreak) {
                break;
            }
            else {
                shouldBreak = true;
                continue;
            }
        }
        string sortedStr = str;
        sort(sortedStr.begin(), sortedStr.end());
        iter = dic.find(sortedStr);
        if(!shouldBreak) {
            if(iter == dic.end()) {
                dic[sortedStr] = vector<string>();
            }
            dic[sortedStr].push_back(str);
        }
        else {
            if(iter == dic.end()) {
                cout << "NOT A VALID WORD" << endl;
            }
            else {
                sort(dic[sortedStr].begin(), dic[sortedStr].end());
                for(int i = 0;i < dic[sortedStr].size();i++) {
                    cout << dic[sortedStr][i] << endl;
                }
            }
            cout << "******" << endl;
        }
    }
    return 0;
    
}