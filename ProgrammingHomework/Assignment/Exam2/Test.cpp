#include "CareerTalk.h"
#include "ReservationTable.h"

#include <iostream>
using namespace std;

#include <vector>
#include <algorithm>
#include <cstring>

CareerTalk::CareerTalk() {
    _company_name = nullptr;
    _day = _start_time = _end_time = -1;
    is_open = false;
    cnt = tot = 0;
}
CareerTalk::CareerTalk(const char* company_name, int day, int start_time, int end_time) {
    _company_name = new char[strlen(company_name) + 1];
    strcpy(_company_name, company_name);
    _day = day, _start_time = start_time, _end_time = end_time;
    is_open = false;
    cnt = tot = 0;
}
CareerTalk::~CareerTalk() {
    delete _company_name;
    _company_name = nullptr;
}
const char* CareerTalk::GetName() {
    return _company_name;
}
int CareerTalk::GetDay() {
    return _day;
}
int CareerTalk::GetStartTime() {
    return _start_time;
}
int CareerTalk::GetEndTime() {
    return _end_time;
}
void CareerTalk::AdjustInfo(int day, int start_time, int end_time) {
    _day = day, _start_time = start_time, _end_time = end_time;
}
void CareerTalk::OpenAccess() {
    is_open = true;
}
void CareerTalk::CloseAccess() {
    is_open = false;
}
bool CareerTalk::IsOpen() {
    return is_open;
}
void CareerTalk::Comment(int score) {
    cnt++, tot += score;
}
float CareerTalk::GetScore() {
    return (float)(1.0 * tot / cnt);
}

bool CareerTalk::operator< (CareerTalk &career_talk) {
    if(_day == career_talk.GetDay()) {
        if(_start_time == career_talk.GetStartTime()) {
            return _end_time < career_talk.GetEndTime();
        }
        else {
            return _start_time < career_talk.GetStartTime();
        }
    }
    else {
        return _day < career_talk.GetDay();
    }
}
bool cmp(CareerTalk* a, CareerTalk* b) {
    return (*a) < (*b);
}

ReservationTable::ReservationTable() {
    table.clear();
}
bool ReservationTable::AddTalk(CareerTalk* career_talk) {
    if(table.empty()) {
        table.push_back(career_talk);
        return true;
    }
    else {
        bool is_added = false;
        for(int i = 0; i < table.size(); i++) {
            if(i == table.size() - 1) {
                if(table[i]->GetDay() < career_talk->GetDay()) {
                    table.push_back(career_talk);
                    is_added = true;
                }
                else if(table[i]->GetDay() == career_talk->GetDay() 
                    && table[i]->GetEndTime() <= career_talk->GetStartTime()) {
                    table.push_back(career_talk);
                    is_added = true;
                }
                break;
            }
            if(table[i]->GetDay() <= career_talk->GetDay()
                && career_talk->GetDay() <= table[i + 1]->GetDay()) {
                if(table[i]->GetDay() < career_talk->GetDay()
                && career_talk->GetDay() < table[i + 1]->GetDay()) {
                    table.insert(table.begin() + i, career_talk);
                    is_added = true;
                }
                else if(table[i]->GetDay() == career_talk->GetDay()
                    && table[i]->GetEndTime() <= career_talk->GetEndTime()) {
                    table.insert(table.begin() + i, career_talk);
                    is_added = true;
                }
                else if(career_talk->GetDay() == table[i + 1]->GetDay()
                    && career_talk->GetEndTime() >= table[i + 1]->GetStartTime()) {
                    table.insert(table.begin() + i, career_talk);
                    is_added = true;
                }
            }
        }
        if(!is_added) {
            return false;
        }
        sort(table.begin(), table.end(), cmp);
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
    if(table.size() == 1) {
        return true;
    }
    sort(table.begin(), table.end(), cmp);
    for(int i = 0; i < table.size(); i++) {
        if(table[i] == career_talk) {
            if(i == 0) {
                return !(table[i]->GetDay() == table[i + 1]->GetDay()
                    && table[i]->GetEndTime() > table[i + 1]->GetStartTime());
            }
            if(i == table.size() - 1) {
                return !(table[i]->GetDay() == table[i - 1]->GetDay()
                    && table[i]->GetStartTime() > table[i - 1]->GetEndTime());
            }
            if((table[i]->GetDay() == table[i + 1]->GetDay()
                && table[i]->GetEndTime() > table[i + 1]->GetStartTime())
                || (table[i]->GetDay() == table[i - 1]->GetDay()
                && table[i]->GetStartTime() > table[i - 1]->GetEndTime())) {
                table.erase(table.begin() + i);
                return false;
            }
            return true;
        }
    }
}

int main() {
    CareerTalk talk1 = CareerTalk("Tencent QQ", 1, 8, 10);
    CareerTalk talk2 = CareerTalk("Alibaba", 2, 14, 16);
    CareerTalk talk3 = CareerTalk("Baidu", 3, 12, 15);
    talk1.OpenAccess();
    talk2.OpenAccess();
    // 初始化对象
    ReservationTable table;
    // 预约宣讲会，根据开放预约与否会有不同的结果
    bool addState1 = table.AddTalk(&talk1);
    bool addState2 = table.AddTalk(&talk2);
    bool addState3 = table.AddTalk(&talk3);
    cout << addState1 << endl;
    // 查询周一9:00-10:00的宣讲会信息
    CareerTalk *queryTalk = table.QueryTalk(1, 9);
    // 查询周一预约了几场宣讲会
    int talkNum = table.TalksInADay(1);
    // 调整宣讲会时间，如果冲突则自动取消预约被改动的宣讲会，不冲突则将table中的宣讲会信息更新
    talk1.AdjustInfo(4, 15, 17);
    bool adjustState = table.AdjustTalk(&talk1);
    talk1.AdjustInfo(2, 15, 17);
    adjustState = table.AdjustTalk(&talk1);
    // 取消预约
    bool cancelState = table.CancelTalk(&talk2);

    vector <int> a;
    a.push_back(0);
    a.push_back(1);
    a.push_back(2);
    a.push_back(4);
    a.insert(a.begin() + 3, 3);
    for(int i = 0; i < 5; i++) {
        cout << a[i] << endl;
    }

    cout << endl;
    a.erase(a.begin() + 1);
    for(int i= 0; i < 4;i++) {
        cout << a[i] << endl;
    }
}