#pragma once
#include <string>
using namespace std;

class Bill
{
public:
    class Time
    {
    private:
        unsigned int hour;
        unsigned int minute;
        unsigned int second;

        bool IsValid(unsigned int h, unsigned int m,
            unsigned int s) const;

    public:
        Time();
        Time(unsigned int h, unsigned int m, unsigned int s);
        Time(const string& str);
        Time(unsigned int totalSeconds);
        Time(const Time& other);

        void Init(unsigned int h, unsigned int m, unsigned int s);
        void Read();
        void Display() const;
        string toString() const;

        unsigned int GetHour() const;
        unsigned int GetMinute() const;
        unsigned int GetSecond() const;

        void SetHour(unsigned int h);
        void SetMinute(unsigned int m);
        void SetSecond(unsigned int s);

        unsigned int ToSeconds() const;
        unsigned int ToMinutes() const;

        int Difference(const Time& other) const;
        Time AddSeconds(int seconds) const;
        Time SubtractSeconds(int seconds) const;

        bool operator==(const Time& other) const;
        bool operator!=(const Time& other) const;
        bool operator<(const Time& other) const;
        bool operator>(const Time& other) const;
        bool operator<=(const Time& other) const;
        bool operator>=(const Time& other) const;
    };

private:
    string surname;
    string phoneNumber;
    double tariff;
    double discount;
    Time startTime;
    Time endTime;
    double amount;

    bool IsValidSurname(const string& value) const;
    bool IsValidPhone(const string& value) const;
    bool IsValidTariff(double value) const;
    bool IsValidDiscount(double value) const;

    void CalculateAmount();

public:
    Bill();
    Bill(const string& surname, const string& phoneNumber,
        double tariff, double discount,
        const Time& startTime, const Time& endTime);
    Bill(const Bill& other);

    void Init(const string& surname, const string& phoneNumber,
        double tariff, double discount,
        const Time& startTime, const Time& endTime);

    void Read();
    void Display() const;
    string toString() const;

    string GetSurname() const;
    string GetPhoneNumber() const;
    double GetTariff() const;
    double GetDiscount() const;
    Time GetStartTime() const;
    Time GetEndTime() const;
    double GetAmount() const;

    void SetSurname(const string& value);
    void SetPhoneNumber(const string& value);
    void SetTariff(double value);
    void SetDiscount(double value);
    void SetStartTime(const Time& value);
    void SetEndTime(const Time& value);
};
