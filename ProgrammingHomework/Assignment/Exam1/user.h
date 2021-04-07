#pragma once
#include "merchandise_list.h"

class User {
    private:
        char user_name[100];
        MerchandiseList buyHis, browseHis;
    public:
        User(const char* user_name);
        void BrowseMerchandise(Merchandise* merchandise);
        MerchandiseList* GetBrowseHistory();
        void BuyMerchandise(Merchandise* merchandise, int number);
        MerchandiseList* GetBuyHistory();
};