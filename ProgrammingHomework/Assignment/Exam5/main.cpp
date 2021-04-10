#include "Mask.h"
#include "Vaccine.h"
#include "CombinedOrder.h"

#include <iostream>
using namespace std;

int main() {
    // 创建若⼲个Mask和Vaccine对象
    Mask mask1("Mask1",5,5);
    Mask mask2("Mask2",10,1);
    Mask mask3("Mask3",15,20);
    Vaccine vaccine1("Vaccine1",300,2,10);
    Vaccine vaccine2("Vaccine2",400,1,3);
    // 打印信息
    cout << mask2.GetName() << " " << vaccine1.GetBound() << endl;
    // 创建两个合并订单类
    CombinedOrder<Mask> order1;
    CombinedOrder<Vaccine> order2;
    // 加⼊订单
    order1.AddOrder(mask1);
    order1.AddOrder(mask2);
    order1.AddOrder(mask3);
    order2.AddOrder(vaccine1);
    order2.AddOrder(vaccine2);

    for(int i = 0; i < 3; i++) {
        cout << order2.AddOrder(vaccine2) << endl;
    }
    // 计算合并订单的总价
    cout << order1.GetTotalCost() << endl;
    // 根据下表获取合并订单中的特定类型
    cout << order2[1].GetName() << endl;
    // ⽐较两个订单的价格
    cout << IsLessThan(mask1, mask2) << endl;
    // 排序合并订单
    SortOrder(order2);
    for(int i = 0; i < 2; i++) {
        cout << order2[i].GetName() << ' ' << order2[i].GetCost() << endl;
    }

    getchar();
}