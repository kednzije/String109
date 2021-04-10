#include "Music.h"
#include "MusicBoard.h"

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

MusicBoard::MusicBoard() {
    musicBoard.clear();
}
MusicBoard::MusicBoard(vector <string> music_list) {
    musicBoard.clear();
    for(int i = 0; i < music_list.size(); i++) {
        string info = music_list[i];
        int ind = info.find('|');
        string name = info.substr(0, ind);
        info = info.substr(ind + 1, info.length());
        ind = info.find('|');
        string singer = info.substr(0, ind);
        info = info.substr(ind + 1, info.length());
        ind = info.find('|');
        string count = info.substr(0, ind);
        info = info.substr(ind + 1, info.length());
        ind = info.find('|');
        string date = info.substr(0, ind);
        info = info.substr(ind + 1, info.length());
        ind = info.find('|');
        string nation = info.substr(0, ind);
        int _count = 0;
        for(int j = 0; j < count.length(); j++) {
            _count = _count * 10 + (count[j] - '0');
        }

        musicBoard.push_back(Music(name, singer, _count, date, nation));
    }
}
bool MusicBoard::addMusic(Music& music) {
    for(int i = 0; i < musicBoard.size(); i++) {
        if(music.getName() == musicBoard[i].getName()
            && music.getSinger() == musicBoard[i].getSinger()) {
                return false;
            }
    }

    musicBoard.push_back(music);
    return true;
}
void MusicBoard::sortMusic(string label) {
    if(label == "commentCount") {
        sort(musicBoard.begin(), musicBoard.end(), 
            [](Music a, Music b) {
                return a.getCount() > b.getCount();
            });
    }
    if(label == "releaseDate") {
        sort(musicBoard.begin(), musicBoard.end(), 
            [](Music a, Music b) {
                return a.getDate() < b.getDate();
            });
    }
}
Music MusicBoard::getByIndex(int index) {
    return musicBoard[index];
}
MusicBoard MusicBoard::filter(string nation) {
    MusicBoard newBoard;
    for(int i = 0; i < musicBoard.size(); i++) {
        if(musicBoard[i].getNation() == nation) {
            newBoard.addMusic(musicBoard[i]);
        }
    }
    return newBoard;
}