#include "pch.h"
#include "CppUnitTest.h"
#include "../lr1_8/Bill.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    // Тестування класу Bill
    TEST_CLASS(BillTests)
    {
    public:

        // Перевірка конструктора за замовчуванням
        TEST_METHOD(Bill_DefaultConstructor)
        {
            Bill b;

            Assert::AreEqual(0.0, b.GetTariff(), 0.001);
            Assert::AreEqual(0.0, b.GetDiscount(), 0.001);
            Assert::AreEqual(0.0, b.GetAmount(), 0.001);
        }

        // Перевірка обчислення вартості телефонної розмови
        TEST_METHOD(Bill_CalculateAmount)
        {
            Bill::Time start(10, 0, 0);
            Bill::Time end(10, 2, 10);

            Bill b("Іваненко", "0991234567",
                10.0, 0.0, start, end);

            // 2 хвилини 10 секунд оплачуються як 3 хвилини
            Assert::AreEqual(30.0, b.GetAmount(), 0.001);
        }

        // Перевірка обчислення суми зі знижкою
        TEST_METHOD(Bill_Discount)
        {
            Bill::Time start(10, 0, 0);
            Bill::Time end(10, 2, 10);

            Bill b("Іваненко", "0991234567",
                10.0, 20.0, start, end);

            // 3 хвилини * 10 грн - знижка 20% = 24 грн
            Assert::AreEqual(24.0, b.GetAmount(), 0.001);
        }

        // Перевірка розмови через північ
        TEST_METHOD(Bill_CallAcrossMidnight)
        {
            Bill::Time start(23, 59, 0);
            Bill::Time end(0, 1, 0);

            Bill b("Петренко", "0671234567",
                5.0, 0.0, start, end);

            // Тривалість 2 хвилини, сума 10 грн
            Assert::AreEqual(10.0, b.GetAmount(), 0.001);
        }

        // Перевірка зміни тарифу
        TEST_METHOD(Bill_SetTariff)
        {
            Bill::Time start(10, 0, 0);
            Bill::Time end(10, 1, 0);

            Bill b("Іваненко", "0991234567",
                5.0, 0.0, start, end);

            b.SetTariff(12.0);

            Assert::AreEqual(12.0, b.GetTariff(), 0.001);
            Assert::AreEqual(12.0, b.GetAmount(), 0.001);
        }

        // Перевірка зміни знижки
        TEST_METHOD(Bill_SetDiscount)
        {
            Bill::Time start(10, 0, 0);
            Bill::Time end(10, 2, 0);

            Bill b("Іваненко", "0991234567",
                10.0, 0.0, start, end);

            b.SetDiscount(50.0);

            Assert::AreEqual(50.0, b.GetDiscount(), 0.001);
            Assert::AreEqual(10.0, b.GetAmount(), 0.001);
        }

        // Перевірка конструктора копіювання
        TEST_METHOD(Bill_CopyConstructor)
        {
            Bill::Time start(10, 0, 0);
            Bill::Time end(10, 1, 0);

            Bill b1("Іваненко", "0991234567",
                8.0, 0.0, start, end);

            Bill b2(b1);

            Assert::AreEqual(b1.GetSurname(), b2.GetSurname());
            Assert::AreEqual(b1.GetPhoneNumber(), b2.GetPhoneNumber());
            Assert::AreEqual(b1.GetAmount(), b2.GetAmount(), 0.001);
        }
	};
}
