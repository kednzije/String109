#include "StudentList.h"

#include <iostream>
#include <string>
using namespace std;

StudentList::StudentList() {
    length = 0;
}
void StudentList::PushFront(Student _stu) {
    for(int i = length; i > 0; i--) {
        stu[i] = stu[i - 1];
    }
    stu[0] = _stu;
    length++;
}
void StudentList::PushBack(Student _stu) {
    stu[length++] = _stu;
}
bool StudentList::Insert(int i, Student _stu) {
    if(i < 1 || i > length) {
        return false;
    }
    for(int _i = length; _i >= i; _i--) {
        stu[_i] = stu[_i - 1];
    }
    stu[i - 1] = _stu;
    length++;
    return true;
}
bool StudentList::Erase(int i) {
    if(i < 1 || i > length) {
        return false;
    }
    for(int _i = i - 1; _i < length - 1; _i++) {
        stu[_i] = stu[_i + 1];
    }
    length--;
    return true;
}
int StudentList::GetLength() {
    return length;
}
Student StudentList::GetStudent(int i) {
    if(i < 1 || i > length) {
        Student null = Student();
        return null;
    }
    return stu[i - 1];
}
void StudentList::Divide(int key) {
    Student _key = Student("", key);
    StudentList tmp;
    for(int i = 0; i < length; i++) {
        if(stu[i] < _key) {
            tmp.PushFront(stu[i]);
        }
        else {
            tmp.PushBack(stu[i]);
        }
    }
    for(int i = 0; i < length; i++) {
        stu[i] = tmp.GetStudent(i);
    }
}
void StudentList::Display() {
    for(int i = 0; i < length; i++) {
        cout << stu[i].GetName() << ' ' << stu[i].GetScore() << endl;
    }
}
void StudentList::Count(int key) {
    int cnt = 0;
    for(int i = 0; i < length; i++) {
        if(stu[i].GetScore() >= key) {
            cnt++;
            cout << stu[i].GetName() << ' ' << stu[i].GetScore() << endl;
        }
    }
    cout << cnt << endl;
}
void StudentList::Delete(int key) {
    while(true) {
        bool flag = false;
        int ind;
        for(int i = 0; i < length; i++) {
            if(stu[i].GetScore() < key) {
                ind = i;
                flag = true;
            }
        }
        if(flag) {
            Erase(ind + 1);
        }
        else {
            break;
        }
    }
}