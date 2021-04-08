#include <vector>
#include <string>
#include <queue>
#include <set>
using namespace std;

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        auto check = [] (string _s)->bool {
            int cnt = 0;
            for(int i = 0; i < _s.length(); i++) {
                if(_s[i] == '(') {
                    cnt++;
                }
                if(_s[i] == ')') {
                    cnt--;
                }
                if(cnt < 0) {
                    return false;
                }
            }
            return !cnt;
        };
        queue <string> que;
        vector <string> ans;
        set <string> pushed;
        que.push(s);
        while(!que.empty()) {
            string _s = que.front();
            que.pop();
            if(!ans.empty() && _s.length() < ans[0].length()) {
                break;
            }
            if(check(_s) && (ans.empty() || _s.length() == ans[0].length())) {
                ans.push_back(_s);
            }
            for(int i = 0; i < _s.length(); i++) {
                string __s = _s;
                __s.erase(__s.begin() + i);
                if(pushed.find(__s) == pushed.end()) {
                    que.push(__s);
                    pushed.insert(__s);
                }
            }
        }
        return ans;
    }
};