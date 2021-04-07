#include <iostream>
#include "merchandise_list.h"
#include "merchandise.h"
using namespace std;

int main() {
    Merchandise mer_pen = Merchandise("pen", 2);
    Merchandise mer_app = Merchandise("apple", 3);
    cout << mer_pen.GetMerchandisePrice() << endl;
    cout << mer_app.GetMerchandisePrice() << endl;
}