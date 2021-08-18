#include <iostream>
using namespace std;

struct A {
      int a, b;
      A() {
            throw 1;
      }
};

int main() {
      try {
            A *x = new A;
            x->a = 9;
            cout << x->a << endl;
            delete x;
      }
      catch(int e) {
            cout << e << endl;
      }
}