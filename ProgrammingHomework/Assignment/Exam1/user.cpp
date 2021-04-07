#include "user.h"
#include "merchandise_list.h"
#include <cstring>

User::User(const char* name) {
    strcpy(user_name, name);
}
void User::BrowseMerchandise(Merchandise* merchandise) {
    int rec = browseHis.FindRecord(merchandise);
    if(rec == -1) {
        browseHis.AddRecord(merchandise, 1);
    }
    else {
        browseHis.ModifyRecord(merchandise, rec + 1);
    }
}
MerchandiseList* User::GetBrowseHistory() {
    return &browseHis;
}
void User::BuyMerchandise(Merchandise* merchandise, int number) {
    int rec = buyHis.FindRecord(merchandise);
    if(rec == -1) {
        buyHis.AddRecord(merchandise, number);
    }
    else {
        buyHis.ModifyRecord(merchandise, rec + number);
    }
}
MerchandiseList* User::GetBuyHistory() {
    return &buyHis;
}