#pragma once
class Merchandise {
    private:
        char name[100];
        int price;
    public:
        Merchandise(const char* n, int p);
        const char* GetMerchandiseName();
        int GetMerchandisePrice();
};