#include <string>

class Student {
private:
    std::string name;
    int score;
public:
    Student();
    Student(std::string _name, int _score);
    bool operator< (const Student& stu) const;
    std::string GetName();
    int GetScore();
};