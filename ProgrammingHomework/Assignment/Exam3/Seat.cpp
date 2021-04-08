#include "Seat.h"

Seat::Seat(int row, int col) {
    r = row, c = col;
}
int Seat::GetRow() {
    return r;
}
int Seat::GetCol() {
    return c;
}
int Seat::Price() {
    return 0;
}
bool Seat::operator> (const Seat& b) {
    return r < b.r;
}
bool Seat::operator== (const Seat& b) {
    return r == b.r;
}
int Seat::operator- (const Seat& b) {
    if(r == b.r) {
        return (c - b.c > 0 ? c - b.c : b.c - c);
    }
    return -1;
}

RegularSeat::RegularSeat(int row, int col) : Seat(row, col) {}
int RegularSeat::Price() {
    return 100;
}

VIPSeat::VIPSeat(int row, int col) : Seat(row, col) {}
int VIPSeat::Price() {
    return 500;
}