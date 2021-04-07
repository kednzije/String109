#include "merchandise.h"
#include <cstring>

Merchandise::Merchandise(const char* n, int p) {
    strcpy(name, n);
    price = p;
}

const char* Merchandise::GetMerchandiseName() {
    return name;
}
int Merchandise::GetMerchandisePrice() {
    return price;
}