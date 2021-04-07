#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <iomanip>
using namespace std;

struct Student {
    int id;
    char name[11];
    int age;
    char birthplace[11];
    double score;
};
inline bool cmp(Student a, Student b) {
    if(a.score == b.score) {
        return a.id < b.id;
    }
    return a.score > b.score;
}

void convert_file(const char *src, const char *dst);
void modify_file(const char *src, const char *dst);
void print_file(const char *src);

#include "test.hpp"

int main()
{
    test();
    return 0;
}

void convert_file(const char *src, const char *dst) {
    ifstream _src(src);
    ofstream _dst(dst, ios::out | ios::binary);
    Student stu;
    _src >> stu.id >> stu.name >> stu.age >> stu.birthplace >> stu.score;
    while(!_src.eof()) {
        _dst.write((char *)&stu, sizeof(stu));
        _src >> stu.id >> stu.name >> stu.age >> stu.birthplace >> stu.score;
    }
    _src.close(), _src.close();
}
void modify_file(const char *src, const char *dst) {
    ifstream _src(src, ios::in | ios::binary);
    ofstream _dst(dst, ios::out | ios::binary);
    vector <Student> vec;
    Student stu;
    while(_src.read((char *)&stu, sizeof(stu))) {
        vec.push_back(stu);
    }
    for(int i = 0; i < vec.size(); i++) {
        if(!strcmp(vec[i].birthplace, "Nanjing")) {
            vec[i].id += 10000000;
        }
    }
    sort(vec.begin(), vec.end(), cmp);
    for(int i = 0; i < vec.size(); i++) {
        _dst.write((char *)&vec[i], sizeof(vec[i]));
    }
    _src.close(), _dst.close();

}
void print_file(const char *src) {
    ifstream _src(src);
    Student stu;
    while(_src.read((char *)&stu, sizeof(stu))) {
        cout << stu.id << ' ' << stu.name << ' ' << stu.age << ' ' << stu.birthplace << ' ' 
            << fixed << showpoint << setprecision(1) << stu.score << '\n';
    }
    _src.close();
}