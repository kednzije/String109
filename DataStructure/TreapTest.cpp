#include "Treap.h"

#include <iostream>
using namespace std;
using namespace String;

int main() {
    TreapSet<int> treapSet;
    int ope, usedValue;
    bool shouldBreak = false;
    while(true && !shouldBreak) {
        cin >> ope;
        switch (ope)
        {
        case 0:
            cin >> usedValue;
            treapSet.Insert(usedValue);
            break;
        case 1:
            cin >> usedValue;
            treapSet.Erase(usedValue);
            break;
        case 2:
            cin >> usedValue;
            cout << treapSet.Count(usedValue) << endl;
            break;
        
        default:
            shouldBreak = true;
            break;
        }
    }
}