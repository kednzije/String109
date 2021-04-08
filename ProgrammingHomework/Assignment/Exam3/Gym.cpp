#include "Seat.h"
#include "Gym.h"

#include <vector>
#include <utility>
using namespace std;

#define NULL 0

Gym::Gym(int RegularSeatNum, int VIPSeatNum) {
    rs.clear(), vs.clear();
    rs_num = RegularSeatNum, vs_num = VIPSeatNum;
}
bool Gym::AddSeat(Seat* seat, int type) {
    for(int i = 0; i < vs.size(); i++) {
        if(vs[i].first->GetRow() == seat->GetRow() && vs[i].first->GetCol() == seat->GetCol()) {
            return false;
        }
    }
    for(int i = 0; i < rs.size(); i++) {
        if(rs[i].first->GetRow() == seat->GetRow() && rs[i].first->GetCol() == seat->GetCol()) {
            return false;
        }
    }
    if(type) {
        // VIPSeat
        if(vs.size() == vs_num) {
            return false;
        }
        vs.push_back(make_pair(new VIPSeat(seat->GetRow(), seat->GetCol()), false));
    }
    else {
        // ReSeat
        if(rs.size() == rs_num) {
            return false;
        }
        rs.push_back(make_pair(new RegularSeat(seat->GetRow(), seat->GetCol()), false));
    }
    return true;
}
bool Gym::DeleteSeat(Seat* seat, int type) {
    if(type) {
        // VIPSeat
        for(int i = 0; i < vs.size(); i++) {
            if(vs[i].first->GetRow() == seat->GetRow() && vs[i].first->GetCol() == seat->GetCol()) {
                vs.erase(vs.begin() + i);
                return true;
            }
        }
    }
    else {
        for(int i = 0; i < rs.size(); i++) {
            if(rs[i].first->GetRow() == seat->GetRow() && rs[i].first->GetCol() == seat->GetCol()) {
                rs.erase(rs.begin() + i);
                return true;
            }
        }
    }
    return false;
}
Seat* Gym::Buy(int row, int col) {
    for(int i = 0; i < vs.size(); i++) {
        if(!vs[i].second && vs[i].first->GetRow() == row && vs[i].first->GetCol() == col) {
            vs[i].second = true;
            return vs[i].first;
        }
    }
    for(int i = 0; i < rs.size(); i++) {
        if(!rs[i].second && rs[i].first->GetRow() == row && rs[i].first->GetCol() == col) {
            rs[i].second = true;
            return rs[i].first;
        }
    }
    return NULL;
}
Seat* Gym::Refund(int row, int col) {
    for(int i = 0; i < vs.size(); i++) {
        if(vs[i].second && vs[i].first->GetRow() == row && vs[i].first->GetCol() == col) {
            vs[i].second = false;
            return vs[i].first;
        }
    }
    for(int i = 0; i < rs.size(); i++) {
        if(rs[i].second && rs[i].first->GetRow() == row && rs[i].first->GetCol() == col) {
            rs[i].second = false;
            return rs[i].first;
        }
    }
    return NULL;
}
int Gym::Income() {
    int income = 0;
    for(int i = 0; i < vs.size(); i++) {
        if(vs[i].second) {
            income += vs[i].first->Price();
        }
    }
    for(int i = 0; i < rs.size(); i++) {
        if(rs[i].second) {
            income += rs[i].first->Price();
        }
    }
    return income;
}