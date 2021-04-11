#include <regex>
#include <iostream>
using namespace std;

int main() {
    regex reg("^Var ([a-z]+[0-9]*)=(.+)");
    
    while(true) {
        string str;
        getline(cin, str);

        regex reg("[+-/*]");
        sregex_token_iterator pos0(str.begin(), str.end(), reg, -1);
        sregex_token_iterator pos1(str.begin(), str.end(), reg, 0);

        decltype(pos0) end0;
	    decltype(pos1) end1;

        for(; pos0 != end0; ++pos0) {
            cout << "!!!" << pos0->str() << endl;
        }
    }
    return 0;
}