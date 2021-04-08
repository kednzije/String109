#pragma once
class Seat {
private:
    int r, c;
public:
    Seat(int row, int col);
    int GetRow();
    int GetCol();
    virtual int Price();
    bool operator > (const Seat& b);
    bool operator == (const Seat& b);
    int operator - (const Seat& b);
};

class RegularSeat : public Seat {
public:
    RegularSeat(int row, int col);
    int Price();
};

class VIPSeat : public Seat {
public:
    VIPSeat(int row, int col);
    int Price();
};