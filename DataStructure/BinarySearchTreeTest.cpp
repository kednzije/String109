#include "BinarySearchTree.h"

#include <iostream>
using namespace std;

int main() {
    BinarySearchTree BST;
    int ope, usedValue, shouldBreak=false;
    while(true && !shouldBreak) {
        cin >> ope;
        switch (ope) {
        case 0:
            cin >> usedValue;
            BST.Insert(usedValue);
            BST.Display();
            cout << endl;
            break;
        case 1:
            cin >> usedValue;
            BST.Delete(usedValue);
            BST.Display();
            cout << endl;
            break;

        default:
            shouldBreak = true;
            break;
        }
    }
    return 0;
}