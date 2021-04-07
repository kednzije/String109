#include "Student.h"

#include <string>
using namespace std;

Student::Student() {
    name = "";
    score = -1;
}
Student::Student(string _name, int _score) {
    name = _name, score = _score;
}
bool Student::operator< (const Student& stu) const {
    return score < stu.score;
}
string Student::GetName() {
    return name;
}
int Student::GetScore() {
    return score;
}