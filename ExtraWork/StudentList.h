#include "Student.h"

const int MAXSIZE = 100;

class StudentList {
private:
    Student stu[MAXSIZE];
    int length;
public:
    StudentList();
    void PushFront(Student _stu);
    void PushBack(Student _stu);
    bool Insert(int i, Student _stu);
    bool Erase(int i);
    int GetLength();
    Student GetStudent(int i);
    void Divide(int key);
    void Display();
    void Count(int key);
    void Delete(int key);
};