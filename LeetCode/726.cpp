#include <map>
#include <regex>
#include <string>
#include <iostream>
using namespace std;

class Solution {
    map <string, int> make(string formula) {
        regex reg("([A-Z][a-z]*)([0-9]*)");
        map <string, int> table;
        smatch m;
        auto pos = formula.cbegin();
        auto end = formula.cend();
        auto to_int = [](string s) {
            int k = 0;
            for(int i = 0; i < s.length(); i++) {
                k = k * 10 + (s[i] - '0');
            }
            return k;
        };
        for(; regex_search(pos, end, m, reg);) {
            if(*pos == '(') {
                int cnt = 1, l = 0;
                auto p = ++pos;
                for(; p != end; p++, l++) {
                    switch(*p) {
                    case '(':
                        cnt++;
                        break;
                    case ')':
                        cnt--;
                        break;
                    default:
                        break;
                    }
                    if(!cnt) {
                        break;
                    }
                }
                map <string, int> sub = make(formula.substr(pos - formula.cbegin(), l));
                pos = ++p;
                string num;
                while(pos != end && *pos >= '0' && *pos <= '9') {
                    num += *pos;
                    pos++;
                }
                int k = to_int(num);
				if(!k) { k = 1; }
                for(auto &elem: sub) {
                    table[elem.first] += elem.second * k;
                }
            }
            else {
                if(m.str(2) == "") {
                    table[m.str(1)] += 1;
                }
                else {
                    table[m.str(1)] += to_int(m.str(2));
                }
				pos = m.suffix().first;
            }
        }
        return table;
    }
public:
    string countOfAtoms(string formula) {
        map <string, int> table;
        table = make(formula);
        string ans;
        for(auto &elem: table) {
            ans += elem.first + (elem.second == 1 ? "" : to_string(elem.second));
        }
        return ans;
    }
};

int main() {
	Solution sol;
	cout << sol.countOfAtoms("(H)");
	return 0;
}