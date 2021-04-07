#pragma once
class CareerTalk {
private:
    char* _company_name;
    int _day, _start_time, _end_time;
    bool is_open;
    int cnt, tot;
public:
    CareerTalk();
    ~CareerTalk();
    CareerTalk(const char* company_name, int day, int start_time, int end_time);
    const char* GetName();
    int GetDay();
    int GetStartTime();
    int GetEndTime();
    void AdjustInfo(int day, int start_time, int end_time);
    void OpenAccess();
    void CloseAccess();
    bool IsOpen();
    void Comment(int score);
    float GetScore();

    bool operator <(CareerTalk &career_talk);
    bool operator <=(CareerTalk &career_talk);
};