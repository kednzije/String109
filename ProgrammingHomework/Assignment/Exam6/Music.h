#pragma once

#include <string>
#include <iostream>

class Music {
private:
    friend std::ostream& operator << (std::ostream& out, const Music& music);

    std::string _name, _singer, _date, _nation;
    int _count;
public:
    Music(std::string name, std::string singer, int count, std::string date, std::string
nation);
    //成员函数，返回该音乐的名称
    std::string getName();
    //成员函数，返回该音乐的歌手
    std::string getSinger();
    //成员函数，返回该音乐的点评人数
    int getCount();
    //成员函数，返回该音乐的发行时间
    std::string getDate();
    //成员函数，返回该音乐的发行国家
    std::string getNation();
};