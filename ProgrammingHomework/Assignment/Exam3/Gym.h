#pragma once
#include "Seat.h"

#include <vector>
#include <utility>

class Gym {
private:
    int rs_num, vs_num;
    std::vector <std::pair <Seat*, bool> > rs;
    std::vector <std::pair <Seat*, bool> > vs;
public:
    Gym(int RugularSeatNum, int VIPSeatNum);
    bool AddSeat(Seat* seat, int type);
    bool DeleteSeat(Seat* seat, int type);
    Seat* Buy(int row, int col);
    Seat* Refund(int row, int col);
    int Income();
};