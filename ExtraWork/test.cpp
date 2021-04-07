#include "StudentList.h"

#include <iostream>
using namespace std;

int main() {
    StudentList stulist;
    stulist.PushFront(Student("a", 90));
    stulist.PushFront(Student("b", 70));
    stulist.PushBack(Student("c", 30));
    stulist.PushFront(Student("d", 10));
    stulist.Display();
    cout << "==================" << endl;
    stulist.Count(95);
    cout << "==================" << endl;
    stulist.Delete(20);
    stulist.Display();
    cout << "==================" << endl;
    stulist.Divide(60);
    stulist.Display();
    return 0;
}