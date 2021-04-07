#pragma once
#include "CareerTalk.h"

#include <vector>

class ReservationTable {
private:
    std::vector <CareerTalk*> table;
public:
    ReservationTable();
    bool AddTalk(CareerTalk* career_talk);
    bool CancelTalk(CareerTalk* career_talk);
    CareerTalk* QueryTalk(int day, int time);
    int TalksInADay(int day);
    bool AdjustTalk(CareerTalk* career_talk);
};