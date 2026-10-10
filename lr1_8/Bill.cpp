#include "Bill.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>
#include <cmath>

using namespace std;

// ==================== Вкладений клас Time ====================

// Перевірка правильності введеного часу
bool Bill::Time::IsValid(unsigned int h, unsigned int m, unsigned int s) const
{
    return h < 24 && m < 60 && s < 60;
}

// Конструктор за замовчуванням
Bill::Time::Time()
{
    hour = 0;
    minute = 0;
    second = 0;
}

// Конструктор часу за годинами, хвилинами та секундами
Bill::Time::Time(unsigned int h, unsigned int m, unsigned int s)
{
    Init(h, m, s);
}

// Конструктор часу з рядка формату "23:59:59"
Bill::Time::Time(const string& str)
{
    unsigned int h, m, s;
    char separator1, separator2;
    istringstream input(str);

    // Перевірка формату рядка та допустимості часу
    if ((input >> h >> separator1 >> m >> separator2 >> s) &&
        separator1 == ':' &&
        separator2 == ':' &&
        (input >> ws).eof() &&
        IsValid(h, m, s))
    {
        hour = h;
        minute = m;
        second = s;
    }
    else
    {
        // Якщо рядок неправильний, встановлюємо час 00:00:00
        hour = 0;
        minute = 0;
        second = 0;
    }
}

// Конструктор часу за кількістю секунд від початку доби
Bill::Time::Time(unsigned int totalSeconds)
{
    totalSeconds %= 86400;

    hour = totalSeconds / 3600;
    minute = (totalSeconds % 3600) / 60;
    second = totalSeconds % 60;
}

// Конструктор копіювання
Bill::Time::Time(const Time& other)
{
    hour = other.hour;
    minute = other.minute;
    second = other.second;
}

// Ініціалізація часу
void Bill::Time::Init(unsigned int h, unsigned int m, unsigned int s)
{
    if (IsValid(h, m, s))
    {
        hour = h;
        minute = m;
        second = s;
    }
    else
    {
        // Якщо час некоректний, встановлюємо значення за замовчуванням
        hour = 0;
        minute = 0;
        second = 0;
    }
}

// Введення часу з клавіатури
void Bill::Time::Read()
{
    unsigned int h, m, s;

    while (true)
    {
        cout << "Введіть години (0-23): ";

        if (!(cin >> h))
        {
            cout << "Помилка! Потрібно ввести ціле число.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cout << "Введіть хвилини (0-59): ";

        if (!(cin >> m))
        {
            cout << "Помилка! Потрібно ввести ціле число.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cout << "Введіть секунди (0-59): ";

        if (!(cin >> s))
        {
            cout << "Помилка! Потрібно ввести ціле число.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Перевірка допустимості введеного часу
        if (IsValid(h, m, s))
        {
            hour = h;
            minute = m;
            second = s;
            break;
        }

        cout << "Помилка! Некоректний час. Спробуйте ще раз.\n";
    }
}

// Виведення часу на екран
void Bill::Time::Display() const
{
    cout << toString();
}

// Перетворення часу в рядок формату "HH:MM:SS"
string Bill::Time::toString() const
{
    ostringstream output;

    output << setfill('0')
        << setw(2) << hour << ":"
        << setw(2) << minute << ":"
        << setw(2) << second;

    return output.str();
}

// Отримання годин
unsigned int Bill::Time::GetHour() const
{
    return hour;
}

// Отримання хвилин
unsigned int Bill::Time::GetMinute() const
{
    return minute;
}

// Отримання секунд
unsigned int Bill::Time::GetSecond() const
{
    return second;
}

// Зміна годин із перевіркою правильності
void Bill::Time::SetHour(unsigned int h)
{
    if (IsValid(h, minute, second))
        hour = h;
}

// Зміна хвилин із перевіркою правильності
void Bill::Time::SetMinute(unsigned int m)
{
    if (IsValid(hour, m, second))
        minute = m;
}

// Зміна секунд із перевіркою правильності
void Bill::Time::SetSecond(unsigned int s)
{
    if (IsValid(hour, minute, s))
        second = s;
}

// Перетворення часу в кількість секунд від початку доби
unsigned int Bill::Time::ToSeconds() const
{
    return hour * 3600 + minute * 60 + second;
}

// Перетворення часу в хвилини з округленням до найближчої хвилини
unsigned int Bill::Time::ToMinutes() const
{
    return (ToSeconds() + 30) / 60;
}

// Обчислення різниці між двома моментами часу в секундах

int Bill::Time::Difference(const Time& other) const
{
    return static_cast<int>(other.ToSeconds()) -
           static_cast<int>(ToSeconds());
}


// Додавання заданої кількості секунд до часу
Bill::Time Bill::Time::AddSeconds(int seconds) const
{
    long long total = static_cast<long long>(ToSeconds()) + seconds;
    total %= 86400;

    // Якщо результат від'ємний, переносимо його в межі доби
    if (total < 0)
        total += 86400;

    return Time(static_cast<unsigned int>(total));
}

// Віднімання заданої кількості секунд від часу
Bill::Time Bill::Time::SubtractSeconds(int seconds) const
{
    long long total = static_cast<long long>(ToSeconds()) - seconds;
    total %= 86400;

    // Якщо результат від'ємний, переносимо його в межі доби
    if (total < 0)
        total += 86400;

    return Time(static_cast<unsigned int>(total));
}

// Перевірка рівності двох моментів часу
bool Bill::Time::operator==(const Time& other) const
{
    return ToSeconds() == other.ToSeconds();
}

// Перевірка нерівності двох моментів часу
bool Bill::Time::operator!=(const Time& other) const
{
    return !(*this == other);
}

// Перевірка, чи є поточний час меншим за інший
bool Bill::Time::operator<(const Time& other) const
{
    return ToSeconds() < other.ToSeconds();
}

// Перевірка, чи є поточний час більшим за інший
bool Bill::Time::operator>(const Time& other) const
{
    return other < *this;
}

// Перевірка, чи є поточний час меншим або рівним іншому
bool Bill::Time::operator<=(const Time& other) const
{
    return !(*this > other);
}

// Перевірка, чи є поточний час більшим або рівним іншому
bool Bill::Time::operator>=(const Time& other) const
{
    return !(*this < other);
}


// ==================== Клас Bill ====================

// Перевірка правильності прізвища платника
bool Bill::IsValidSurname(const string& value) const
{
    return !value.empty();
}

// Перевірка правильності номера телефону
bool Bill::IsValidPhone(const string& value) const
{
    if (value.empty())
        return false;

    // Номер може містити цифри, знак "+" та розділювачі
    for (char c : value)
    {
        if (!isdigit(static_cast<unsigned char>(c)) &&
            c != '+' && c != '-' && c != '(' &&
            c != ')' && c != ' ')
        {
            return false;
        }
    }

    return true;
}

// Перевірка правильності тарифу за хвилину
bool Bill::IsValidTariff(double value) const
{
    return isfinite(value) && value >= 0;
}

// Перевірка правильності відсотка знижки
bool Bill::IsValidDiscount(double value) const
{
    return isfinite(value) && value >= 0 && value <= 100;
}

// Обчислення суми до оплати за телефонну розмову


void Bill::CalculateAmount()
{
    int duration = startTime.Difference(endTime);

    // Якщо розмова завершилася наступного дня
    if (duration < 0)
    {
        duration += 24 * 60 * 60;
    }

    // Кожна неповна хвилина оплачується як повна
    int minutes = (duration + 59) / 60;

    amount = minutes * tariff * (1.0 - discount / 100.0);
}



// Конструктор за замовчуванням
Bill::Bill()
{
    surname = "";
    phoneNumber = "";
    tariff = 0;
    discount = 0;
    startTime = Time();
    endTime = Time();
    amount = 0;
}

// Конструктор із параметрами
Bill::Bill(const string& surname, const string& phoneNumber,
    double tariff, double discount,
    const Time& startTime, const Time& endTime)
{
    // Спочатку задаємо безпечні початкові значення
    this->surname = "";
    this->phoneNumber = "";
    this->tariff = 0;
    this->discount = 0;
    this->startTime = Time();
    this->endTime = Time();
    this->amount = 0;

    // Ініціалізація об'єкта переданими параметрами
    Init(surname, phoneNumber, tariff, discount, startTime, endTime);
}

// Конструктор копіювання
Bill::Bill(const Bill& other)
{
    surname = other.surname;
    phoneNumber = other.phoneNumber;
    tariff = other.tariff;
    discount = other.discount;
    startTime = other.startTime;
    endTime = other.endTime;
    amount = other.amount;
}

// Ініціалізація даних рахунку
void Bill::Init(const string& surname, const string& phoneNumber,
    double tariff, double discount,
    const Time& startTime, const Time& endTime)
{
    SetSurname(surname);
    SetPhoneNumber(phoneNumber);
    SetTariff(tariff);
    SetDiscount(discount);
    SetStartTime(startTime);
    SetEndTime(endTime);

    // Остаточний перерахунок суми до оплати
    CalculateAmount();
}

// Введення даних рахунку з клавіатури
void Bill::Read()
{
    string surnameInput;
    string phoneInput;
    double tariffInput;
    double discountInput;

    // Введення прізвища платника
    do
    {
        cout << "Введіть прізвище платника: ";
        cin >> surnameInput;

        if (!IsValidSurname(surnameInput))
            cout << "Помилка! Прізвище не може бути порожнім.\n";

    } while (!IsValidSurname(surnameInput));

    // Введення номера телефону
    do
    {
        cout << "Введіть номер телефону: ";
        cin >> phoneInput;

        if (!IsValidPhone(phoneInput))
            cout << "Помилка! Некоректний номер телефону.\n";

    } while (!IsValidPhone(phoneInput));

    // Введення тарифу за одну хвилину
    do
    {
        cout << "Введіть тариф за хвилину (грн): ";

        if (!(cin >> tariffInput))
        {
            cout << "Помилка! Введіть число.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            tariffInput = -1;
            continue;
        }

        if (!IsValidTariff(tariffInput))
            cout << "Помилка! Тариф не може бути від'ємним.\n";

    } while (!IsValidTariff(tariffInput));

    // Введення знижки у відсотках
    do
    {
        cout << "Введіть знижку (%): ";

        if (!(cin >> discountInput))
        {
            cout << "Помилка! Введіть число.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            discountInput = -1;
            continue;
        }

        if (!IsValidDiscount(discountInput))
            cout << "Помилка! Знижка має бути від 0 до 100.\n";

    } while (!IsValidDiscount(discountInput));

    cout << "\nВведення часу початку розмови:\n";
    startTime.Read();

    cout << "\nВведення часу завершення розмови:\n";
    endTime.Read();

    // Збереження введених даних
    this->surname = surnameInput;
    this->phoneNumber = phoneInput;
    this->tariff = tariffInput;
    this->discount = discountInput;

    // Обчислення суми до оплати
    CalculateAmount();
}

// Виведення інформації про рахунок
void Bill::Display() const
{
    cout << toString();
}

// Формування рядка з інформацією про рахунок
string Bill::toString() const
{
    ostringstream output;

    output << fixed << setprecision(2);
    output << "Прізвище платника: " << surname << '\n';
    output << "Номер телефону: " << phoneNumber << '\n';
    output << "Тариф за хвилину: " << tariff << " грн\n";
    output << "Знижка: " << discount << "%\n";
    output << "Час початку розмови: " << startTime.toString() << '\n';
    output << "Час завершення розмови: " << endTime.toString() << '\n';

    int duration = startTime.Difference(endTime);

    // Врахування переходу через північ
    if (duration < 0)
        duration += 86400;

    output << "Тривалість розмови: "
        << duration / 60 << " хв "
        << duration % 60 << " с\n";

    output << "Сума до оплати: " << amount << " грн\n";

    return output.str();
}

// Отримання прізвища платника
string Bill::GetSurname() const
{
    return surname;
}

// Отримання номера телефону
string Bill::GetPhoneNumber() const
{
    return phoneNumber;
}

// Отримання тарифу за хвилину
double Bill::GetTariff() const
{
    return tariff;
}

// Отримання відсотка знижки
double Bill::GetDiscount() const
{
    return discount;
}

// Отримання часу початку розмови
Bill::Time Bill::GetStartTime() const
{
    return startTime;
}

// Отримання часу завершення розмови
Bill::Time Bill::GetEndTime() const
{
    return endTime;
}

// Отримання суми до оплати
double Bill::GetAmount() const
{
    return amount;
}

// Зміна прізвища платника
void Bill::SetSurname(const string& value)
{
    if (IsValidSurname(value))
        surname = value;
}

// Зміна номера телефону
void Bill::SetPhoneNumber(const string& value)
{
    if (IsValidPhone(value))
        phoneNumber = value;
}

// Зміна тарифу за хвилину
void Bill::SetTariff(double value)
{
    if (IsValidTariff(value))
    {
        tariff = value;
        CalculateAmount();
    }
}

// Зміна відсотка знижки
void Bill::SetDiscount(double value)
{
    if (IsValidDiscount(value))
    {
        discount = value;
        CalculateAmount();
    }
}

// Зміна часу початку розмови
void Bill::SetStartTime(const Time& value)
{
    startTime = value;
    CalculateAmount();
}

// Зміна часу завершення розмови
void Bill::SetEndTime(const Time& value)
{
    endTime = value;
    CalculateAmount();
}
