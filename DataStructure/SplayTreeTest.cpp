#include "SplayTree.h"
#include <iostream>
using namespace std;
using namespace String;

int main() {
    SplayTree splayTree;
    int ope, usedValue;
    while(true) {
        cin >> ope;
        switch (ope)
        {
        case 0:
            cin >> usedValue;
            splayTree.Insert(usedValue);
            break;
        case 1:
            cin >> usedValue;
            splayTree.Delete(usedValue);
            break;
        case 2:
            cin >> usedValue;
            cout << splayTree.Rank(usedValue) << endl;
            break;
        
        default:
            return 0;
        }
    }
}