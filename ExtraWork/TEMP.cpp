#include <iostream>
#include <unordered_map>
using namespace std;

struct A {
      int a, b;
      A() {
            throw 1;
      }
};

int main() {
      unordered_map <int, int> m;
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