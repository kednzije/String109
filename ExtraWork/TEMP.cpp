typedef unsigned char Byte;

int double_compare(const void *p1, const void *p2) {
    return (*(double*)p1) < (*(double*)p2);
}
void merge_sort(void *base, unsigned int count, unsigned int element_size, 
	int (*cmp)(const void *, const void *)) {
    if(count <= 1) {
        return;
    }
    Byte* byte_base = (Byte*)base;
    merge_sort((void*)base, count / 2, element_size, cmp);
    merge_sort((void*)(byte_base + count / 2 * element_size), count - count / 2, element_size, cmp);
    Byte* byte_copy = new Byte[count * element_size];
    for(int k = 0; k < count * element_size; k++) {
        byte_copy[k] = byte_base[k];
    }
    int i = 0, j = count / 2, ind = 0;
    while(i < count / 2 || j < count) {
        Byte* from;
        if(i == count / 2) {
            from = byte_copy + j * element_size;
            j++;
        }
        else if(j == count) {
            from = byte_copy + i * element_size;
            i++;
        }
        else if(cmp(byte_copy + i * element_size, byte_copy + j * element_size)) {
            from = byte_copy + i * element_size;
            i++;
        }
        else {
            from = byte_copy + j * element_size;
            j++;
        }
        Byte* to = byte_base + (ind++) * element_size;
        for(int k = 0; k < element_size; k++) {
            to[k] = from[k];
        }
    }
}

#include <iostream>
using namespace std;

int main() {
    double a[] = {1.2, 0.1, 3.3, 8};
    merge_sort(a, 4, sizeof(double), double_compare);
    for(int i = 0; i < 4; i++) {
        cout << a[i] << endl;
    }
}