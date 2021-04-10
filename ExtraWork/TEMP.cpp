// scoreboard.h
#include <string>
#include <vector>
#include <iostream>

struct ScoreLog
{
    int id;
    std::string name;
    bool isMale;
    double score;
    ScoreLog(int _id, std::string _name, bool _isMale, double _score) {
        id = _id, name = _name, isMale = _isMale, score = _score;
    }
};

enum class OutputFormat {
    normal,
    veryGood,
    underAverage,
};

class ScoreBoard {
private:
    friend std::istream& operator >> (std::istream& input, ScoreBoard& s);
    friend std::ostream& operator << (std::ostream& output, ScoreBoard& s);

    std::vector <ScoreLog> logs;
    OutputFormat formatFlag;
public:
    ScoreBoard();
    void addLog(int id, std::string name, bool isMale, double score);
    void addExtraLog(int id, std::string name, bool isMale, double score);
    void setFormatFlag(OutputFormat f);
    void sortByScore();
    ScoreBoard underAverageStudents();
};

// scoarboard.cpp
// #include "scoreboard.h"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

ScoreBoard::ScoreBoard() {
    logs.clear();
    formatFlag = OutputFormat::normal;
}
void ScoreBoard::addLog(int id, std::string name, bool isMale, double score) {
    logs.push_back(ScoreLog(id, name, isMale, score));
}
void ScoreBoard::addExtraLog(int id, std::string name, bool isMale, double score) {
    logs.push_back(ScoreLog(id, name, isMale, score * 0.9));
}
void ScoreBoard::setFormatFlag(OutputFormat f) {
    formatFlag = f;
}
void ScoreBoard::sortByScore() {
    sort(logs.begin(), logs.end(), [](ScoreLog a, ScoreLog b) { return a.score > b.score; });
}
ScoreBoard ScoreBoard::underAverageStudents() {
    ScoreBoard stu;
    double avgMale = 0, avgFemale = 0;
    int cntMale = 0, cntFemale =  0;
    for(int i = 0; i < logs.size(); i++) {
        if(logs[i].isMale) {
            avgMale += logs[i].score;
            cntMale++;
        }
        else {
            avgFemale += logs[i].score;
            cntFemale++;
        }
    }
    avgMale /= cntMale, avgFemale /= cntFemale;
    for(int i = 0; i < logs.size(); i++) {
        if(logs[i].isMale && logs[i].score < avgMale) {
            stu.logs.push_back(logs[i]);
        }
        if(!logs[i].isMale && logs[i].score < avgFemale) {
            stu.logs.push_back(logs[i]);
        }
    }
    return stu;
}
istream& operator >> (istream& input, ScoreBoard& s) {
    int n;
    input >> n;
    s = ScoreBoard();
    for(int i = 0; i < n; i++) {
        int id;
        string name;
        bool isMale;
        double score;
        input >> id >> name >> isMale >> score;
        s.addLog(id, name, isMale, score);
    }
    return input;
}
ostream& operator << (ostream& output, ScoreBoard& s) {
    switch (s.formatFlag)
    {
    case OutputFormat::normal:
        output << s.logs.size() << endl;
        for(int i = 0; i < s.logs.size(); i++) {
            output << s.logs[i].id << ' ' << s.logs[i].name 
                << ' ' << s.logs[i].isMale << ' ' << s.logs[i].score << endl;
        }
        break;
    case OutputFormat::veryGood: {
        ScoreBoard tmp = s;
        tmp.sortByScore();
        output << 3 << endl;
        for(int i = 0; i < 3; i++) {
            output << tmp.logs[i].id << ' ' << tmp.logs[i].name 
                << ' ' << tmp.logs[i].isMale << ' ' << tmp.logs[i].score << endl;
        }
        break;
    }
    case OutputFormat::underAverage: {
        ScoreBoard tmp = s.underAverageStudents();
        output << tmp;
        break;
    }

    default:
        break;
    }
}

// #include "scoreboard.h"

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ScoreBoard s;
    cin >> s;
    ofstream output_a("a.txt");
    ofstream output_b("b.txt");
    ofstream output_c("c.txt");
    output_a << s;
    s.setFormatFlag(OutputFormat::veryGood);
    output_b << s;
    s.setFormatFlag(OutputFormat::underAverage);
    output_c << s;

    output_a.close();
    output_b.close();
    output_c.close();

    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int id; 
        string name;
        bool isMale;
        double score;
        cin >> id >> name >> isMale >> score;
        s.addExtraLog(id, name, isMale, score);
    }
    s.setFormatFlag(OutputFormat::normal);
    output_a.open("a.txt");
    output_a << s;
    output_a.close();
    return 0;
}