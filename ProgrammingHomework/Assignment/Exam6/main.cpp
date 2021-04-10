#include "Music.h"
#include "MusicBoard.h"

#include <iostream>
using namespace std;

int main() {
    string music001 = "Crow|Vae|64970|2021-05-07|China";
    string music002 = "You Belong With Me|Taylor Swift|2809|2009-04-18|America";
    //存储音乐信息表的vector
    vector<string> musicList;
    musicList.push_back(music001);
    musicList.push_back(music002);
    //根据音乐信息表，录入多首音乐的信息
    MusicBoard board1(musicList);
    for(int i = 0; i < 2; i++) {
        cout << board1.getByIndex(i) << endl;
    }

    getchar();
}