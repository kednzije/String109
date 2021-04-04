#include "Singular.h"
#include <iostream>
#include <algorithm>
#include <cstring>

void get_min_asc(char* str) {
    char min_asc = str[0];
    for(int i = 1; str[i] != '\0'; i++) {
        min_asc = (min_asc < str[i] ? min_asc : str[i]);
    }
    std::cout << min_asc;
}

void reorder(char* str) {
    std::sort(str, str + strlen(str));
    for(int i = 0; str[i] != '\0'; i++) {
        std::cout << str[i];
    }
}