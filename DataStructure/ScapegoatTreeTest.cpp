#include "ScapegoatTree.h"

#include <iostream>
using namespace std;
using namespace String;

int main() {
    ScapegoatTree scapegoatTree;
    int ope, usedValue;
    while(true) {
        cin >> ope;
        switch (ope)
        {
        case 0:
            cin >> usedValue;
            scapegoatTree.Insert(usedValue);
            scapegoatTree.Display();
            break;
        case 1:
            cin >> usedValue;
            scapegoatTree.Delete(usedValue);
            scapegoatTree.Display();
            break;
        
        default:
            return 0;
        }
    }
}