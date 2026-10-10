#include <iostream>
#include <Windows.h>
#include "Bill.h"

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Створення об'єктів Time різними конструкторами
    Bill::Time t1;
    Bill::Time t2(12, 30, 45);
    Bill::Time t3("23:59:59");
    Bill::Time t4(3661);
    Bill::Time t5(t2);

    cout << "===== КЛАС TIME =====\n";

    cout << "t1: " << t1.toString() << '\n';
    cout << "t2: " << t2.toString() << '\n';
    cout << "t3: " << t3.toString() << '\n';
    cout << "t4: " << t4.toString() << '\n';
    cout << "t5 (копія t2): " << t5.toString() << '\n';

    // Ініціалізація та методи доступу
    t1.Init(10, 20, 30);
    t1.SetHour(11);
    t1.SetMinute(25);
    t1.SetSecond(40);

    cout << "\nГодина: " << t1.GetHour() << '\n';
    cout << "Хвилина: " << t1.GetMinute() << '\n';
    cout << "Секунда: " << t1.GetSecond() << '\n';

    cout << "Час у секундах: " << t1.ToSeconds() << '\n';
    cout << "Час у хвилинах: " << t1.ToMinutes() << '\n';

    cout << "Різниця t1 і t2: "
        << t1.Difference(t2) << " секунд\n";

    cout << "Додавання 90 секунд: "
        << t1.AddSeconds(90).toString() << '\n';

    cout << "Віднімання 90 секунд: "
        << t1.SubtractSeconds(90).toString() << '\n';

    cout << "t1 == t2: " << (t1 == t2) << '\n';
    cout << "t1 != t2: " << (t1 != t2) << '\n';
    cout << "t1 < t2: " << (t1 < t2) << '\n';
    cout << "t1 > t2: " << (t1 > t2) << '\n';
    cout << "t1 <= t2: " << (t1 <= t2) << '\n';
    cout << "t1 >= t2: " << (t1 >= t2) << '\n';

    // Введення часу з клавіатури
    Bill::Time enteredTime;
    cout << "\nВведення часу з клавіатури:\n";
    enteredTime.Read();

    cout << "Введений час: ";
    enteredTime.Display();
    cout << '\n';

    // Створення об'єктів Bill
    Bill::Time start(10, 0, 0);
    Bill::Time end(10, 2, 1);

    Bill bill1(
        "Іваненко",
        "+380991234567",
        5.0,
        10.0,
        start,
        end
    );

    Bill bill2;
    bill2.Init(
        "Петренко",
        "+380671112233",
        4.0,
        0.0,
        Bill::Time(14, 0, 0),
        Bill::Time(14, 3, 0)
    );

    Bill bill3(bill1);

    cout << "\n===== КЛАС BILL =====\n";

    bill1.Display();

    cout << "\nДругий платіж:\n";
    bill2.Display();

    cout << "\nКопія першого платежу:\n";
    bill3.Display();

    // Методи доступу
    cout << "\nПрізвище: " << bill1.GetSurname() << '\n';
    cout << "Телефон: " << bill1.GetPhoneNumber() << '\n';
    cout << "Тариф: " << bill1.GetTariff() << '\n';
    cout << "Знижка: " << bill1.GetDiscount() << '\n';
    cout << "Сума: " << bill1.GetAmount() << '\n';

    cout << "Початок: "
        << bill1.GetStartTime().toString() << '\n';
    cout << "Кінець: "
        << bill1.GetEndTime().toString() << '\n';

    // Зміна значень через сеттери
    bill1.SetSurname("Шевченко");
    bill1.SetPhoneNumber("+380501234567");
    bill1.SetTariff(7.0);
    bill1.SetDiscount(20.0);
    bill1.SetStartTime(Bill::Time(9, 0, 0));
    bill1.SetEndTime(Bill::Time(9, 2, 0));

    cout << "\nПлатіж після зміни значень:\n";
    bill1.Display();

    cout << "\nСума у форматі рядка: "
        << bill1.toString() << '\n';

    // Масив об'єктів
    Bill bills[3] = { bill1, bill2, bill3 };

    cout << "\n===== МАСИВ ПЛАТЕЖІВ =====\n";

    for (int i = 0; i < 3; i++)
    {
        cout << "\nПлатіж №" << i + 1 << ":\n";
        bills[i].Display();
    }

    // Введення цілого платежу з клавіатури
    Bill enteredBill;

    cout << "\n===== ВВЕДЕННЯ ПЛАТЕЖУ =====\n";
    enteredBill.Read();

    cout << "\nВведений платіж:\n";
    enteredBill.Display();

    return 0;
}
