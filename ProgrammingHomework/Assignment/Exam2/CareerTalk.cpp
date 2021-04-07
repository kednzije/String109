#include "CareerTalk.h"

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
        return _end_time <= career_talk.GetStartTime();
    }
    else {
        return _day < career_talk.GetDay();
    }
}
bool CareerTalk::operator<= (CareerTalk &career_talk) {
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