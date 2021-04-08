#include "Gym.h"

#include <iostream>
using namespace std;

int main() {
    // 创建对象
    Gym gym1(3,2);
    RegularSeat seat3(3,5);
    RegularSeat seat4(3,6);
    RegularSeat seat5(3,7);
    VIPSeat seat6(1,2);
    VIPSeat seat7(1,3);
    int ans1 = seat3 - seat5; // ans1 == 2
    cout << ans1 << endl;
    int ans2 = seat6 - seat4; // ans2 == -1
    cout << ans2 << endl;
    bool ans3 = (seat4 == seat5); // ans3 == true
    cout << ans3 << endl;
    bool ans4 = (seat5 > seat7); // ans4 == false
    cout << ans4 << endl;
    // 添加座位
    cout << gym1.AddSeat(&seat3,0) << endl;
    cout << gym1.AddSeat(&seat4,0) << endl;
    cout << gym1.AddSeat(&seat5,0) << endl;
    cout << gym1.AddSeat(&seat6,1) << endl;
    cout << gym1.AddSeat(&seat7,1) << endl;
    cout << gym1.AddSeat(&seat7,1) << endl; // false
    // 删除座位
    cout << gym1.DeleteSeat(&seat5,0) << endl;
    cout << gym1.DeleteSeat(&seat6,1) << endl;
    cout << gym1.DeleteSeat(&seat6,1) << endl; // false
    // 购票
    gym1.Buy(3,6);
    gym1.Buy(1,3);
    gym1.Buy(1,3); // NULL
    // 退票
    gym1.Refund(1,3);
    gym1.Refund(1,3); // NULL
    // 计算该场馆的收⼊
    cout << gym1.Income() << endl;
    getchar(); getchar();
}