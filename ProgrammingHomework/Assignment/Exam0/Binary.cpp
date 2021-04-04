#include "Binary.h"
#include <iostream>
#include <algorithm>
#include <cstring>

void sum_len(char* str1, char* str2) {
    int cnt = 0;
    for(int i = 0; str1[i] != '\0'; i++, cnt++) {}
    for(int j = 0; str2[j] != '\0'; j++, cnt++) {}
    std::cout << cnt;
}

void merge(char* str1, char* str2) {
    std::sort(str1, str1 + strlen(str1));
    std::sort(str2, str2 + strlen(str2));
    int i = 0, j = 0;
    while(true) {
        if(i == strlen(str1)) {
            for(;j < strlen(str2); j++) {
                std::cout << str2[j];
            }
            break;
        }
        if(j == strlen(str2)) {
            for(;i < strlen(str1); i++) {
                std::cout << str1[i];
            }
            break;
        }

        if(str1[i] < str2[j]) {
            std::cout << str1[i];
            i++;
        }
        else {
            std::cout << str2[j];
            j++;
        }
    }
}