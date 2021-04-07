#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
inline char ToUpper(const char c) {
    return (c >= 'A' && c <= 'Z') ? c : c + ('A' - 'a');
}
inline char ToLower(const char c) {
    return (c >= 'a' && c <= 'z') ? c : c + ('a' - 'A');
}
inline bool CompareInc(string a, string b) {
    return a < b;
}
inline bool CompareDec(string a, string b) {
    return a > b;
}

void merge_file(const char *src1, const char *src2, const char *dst);
void upper_file(const char *src, const char *dst);
void lower_file(const char *src, const char *dst);
void sort_inc_file(const char *src, const char *dst);
void sort_dec_file(const char *src, const char *dst);

#include "test.hpp"

int main()
{
    test();
    return 0;
}

void merge_file(const char *src1, const char *src2, const char *dst) {
    ifstream _src1(src1), _src2(src2);
    ofstream _dst(dst);
    string str;
    while(!_src1.eof()) {
        getline(_src1, str);
        _dst << str << endl;
    }
    while(!_src2.eof()) {
        getline(_src2, str);
        _dst << str << endl;
    }
    _src1.close(), _src2.close(), _dst.close();
}
void upper_file(const char *src, const char *dst) {
    ifstream _src(src);
    ofstream _dst(dst);
    string str;
    while(!_src.eof()) {
        getline(_src, str);
        transform(str.begin(), str.end(), str.begin(), ToUpper);
        _dst << str << endl;
    }
    _src.close(), _dst.close();
}
void lower_file(const char *src, const char *dst) {
    ifstream _src(src);
    ofstream _dst(dst);
    string str;
    while(!_src.eof()) {
        getline(_src, str);
        transform(str.begin(), str.end(), str.begin(), ToLower);
        _dst << str << endl;
    }
    _src.close(), _dst.close();
}
void sort_inc_file(const char *src, const char *dst) {
    ifstream _src(src);
    ofstream _dst(dst);
    vector <string> vec;
    while(!_src.eof()) {
        string str;
        getline(_src, str);
        vec.push_back(str);
    }
    sort(vec.begin(), vec.end(), CompareInc);
    for(int i = 0; i < vec.size(); i++) {
        _dst << vec[i] << endl;
    }
    _src.close(), _dst.close();
}
void sort_dec_file(const char *src, const char *dst) {
    ifstream _src(src);
    ofstream _dst(dst);
    vector <string> vec;
    while(!_src.eof()) {
        string str;
        getline(_src, str);
        vec.push_back(str);
    }
    sort(vec.begin(), vec.end(), CompareDec);
    for(int i = 0; i < vec.size(); i++) {
        _dst << vec[i] << endl;
    }
    _src.close(), _dst.close();
}