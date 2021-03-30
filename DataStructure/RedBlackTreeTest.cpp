#include "RedBlackTree.h"
#include <iostream>
using namespace std;
using namespace String;

int main() {
    RedBlackTree rbt;
    int ope, val;
    while (true) {
        cin >> ope;
        switch (ope) {
        case 0:
            cin >> val;
            rbt.Insert(val);
            rbt.Display();
            break;
        
        default:
            return 0;
        }
    }
}