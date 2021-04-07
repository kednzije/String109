#include "merchandise_list.h"
#include <map>
#include <cstring>

MerchandiseList::MerchandiseList() {}
void MerchandiseList::AddRecord(Merchandise* merchandise, int value) {
    for(iter = list.begin(); iter != list.end(); iter++) {
        if(!strcmp(iter->first->GetMerchandiseName(), merchandise->GetMerchandiseName())) {
            iter->second = value;
            return;
        }
    }
    list[merchandise] = value;
}
void MerchandiseList::ModifyRecord(Merchandise* merchandise, int new_value) {
    for(iter = list.begin(); iter != list.end(); iter++) {
        if(!strcmp(iter->first->GetMerchandiseName(), merchandise->GetMerchandiseName())) {
            iter->second = new_value;
            return;
        }
    }
}
int MerchandiseList::FindRecord(Merchandise* merchandise) {
    for(iter = list.begin(); iter != list.end(); iter++) {
        if(!strcmp(iter->first->GetMerchandiseName(), merchandise->GetMerchandiseName())) {
            return iter->second;
        }
    }
    return -1;
}
bool MerchandiseList::DeleteRecord(Merchandise* merchandise) {
    for(iter = list.begin(); iter != list.end(); iter++) {
        if(!strcmp(iter->first->GetMerchandiseName(), merchandise->GetMerchandiseName())) {
            list.erase(iter);
            return true;
        }
    }
    return false;
}