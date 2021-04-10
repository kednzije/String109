#include "Music.h"

#include <string>
#include <iostream>
using namespace std;

Music::Music(string name, string singer, int count, string date, string
nation) {
    _name = name, _singer = singer, _count = count, _date = date, _nation = nation;
}
string Music::getName() {
    return _name;
}
string Music::getSinger() {
    return _singer;
}
int Music::getCount() {
    return _count;
}
string Music::getDate() {
    return _date;
}
string Music::getNation() {
    return _nation;
}

ostream& operator << (ostream& out, const Music& music) {
    out << music._name << ',' 
        << music._singer << ',' 
        << music._count << ',' 
        << music._date << ',' 
        << music._nation;
    return out;
}