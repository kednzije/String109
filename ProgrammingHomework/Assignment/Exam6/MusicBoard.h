#pragma once

#include "Music.h"

#include <string>
#include <vector>

class MusicBoard {
private:
    std::vector <Music> musicBoard;
public:
    MusicBoard();
    MusicBoard(std::vector <std::string> music_list);
    bool addMusic(Music& music);
    void sortMusic(std::string label);
    Music getByIndex(int index);
    MusicBoard filter(std::string nation);
};