#include <iostream>
using namespace std;

struct A {
      int a, b;
};

int main() {
      A *x = new A{ 9, 8 };
      cout << x->a << endl;
      delete x;

      int x = 8 / 0;
}