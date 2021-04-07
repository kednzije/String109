#include "ReservationTable.h"

#include <vector>
#include <algorithm>
using namespace std;

bool cmp(CareerTalk* a, CareerTalk* b) {
    return (*a) <= (*b);
}

ReservationTable::ReservationTable() {
    table.clear();
}
bool ReservationTable::AddTalk(CareerTalk* career_talk) {
    if(!career_talk->IsOpen()) {
        return false;
    }
    if(table.empty()) {
        table.push_back(career_talk);
        return true;
    }
    else {
        bool is_added = false;
        for(int i = 0; i < table.size(); i++) {
            if(table[i] == career_talk) {
                return false;
            }
            if(i == table.size() - 1) {
                if((*table[i]) < (*career_talk)) {
                    is_added = true;
                    table.insert(table.begin() + i + 1, career_talk);
                }
                break;
            }
            if((*table[i]) < (*career_talk) && (*career_talk) < (*table[i + 1])) {
                is_added = true;
                table.insert(table.begin() + i + 1, career_talk);
                break;
            }
        }
        if(!is_added) {
            return false;
        }
        // sort(table.begin(), table.end(), cmp);
        return true;
    }
}
bool ReservationTable::CancelTalk(CareerTalk* career_talk) {
    for(int i = 0; i < table.size(); i++) {
        if(table[i] == career_talk) {
            table.erase(table.begin() + i);
            return true;
        }
    }
    return false;
}
CareerTalk* ReservationTable::QueryTalk(int day, int time) {
    for(int i = 0; i < table.size(); i++) {
        if(table[i]->GetDay() == day
        && table[i]->GetStartTime() <= time
        && table[i]->GetEndTime() > time) {
            return table[i];
        }
    }
    return NULL;
}
int ReservationTable::TalksInADay(int day) {
    int cnt = 0;
    for(int i = 0; i < table.size(); i++) {
        if(table[i]->GetDay() == day) {
            cnt++;
        }
    }
    return cnt;
}
bool ReservationTable::AdjustTalk(CareerTalk* career_talk) {
    return CancelTalk(career_talk) && AddTalk(career_talk);
}