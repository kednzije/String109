#pragma once
#include "merchandise.h"
#include <map>
const int MAXLSTNUM = 20;

class MerchandiseList {
    private:
        std::map <Merchandise*, int> list;
        std::map<Merchandise*, int>::iterator iter;
    public:
        MerchandiseList();
        void AddRecord(Merchandise* merchandise, int value);
        void ModifyRecord(Merchandise* merchandise, int new_value);
        int FindRecord(Merchandise* merchandise);
        bool DeleteRecord(Merchandise* merchandise);
};