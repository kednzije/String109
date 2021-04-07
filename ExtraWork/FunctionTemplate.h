#ifndef FUNCTIONTEMPLATE
#define FUNCTIONTEMPLATE

template <typename Type> void Sort(Type a[], int n) {
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(a[i] >= a[j]) {
                Type tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

#endif