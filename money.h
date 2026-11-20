// money.h
// Класс Money: рубли и копейки.
// Лабораторная работа №4, вариант 13.
// Стиль: Google C++ Style Guide.

#ifndef LABA4_MONEY_H_
#define LABA4_MONEY_H_

#include <ostream>

class Money {
public:
	// Конструктор по умолчанию: 0 руб. 0 коп.
	Money();

	// Конструктор с параметрами. Нормализует копейки (>= 100 переводит в рубли,
	// < 0 заимствует из рублей; сумма не может быть отрицательной).
	Money(unsigned int rubles, short int kopeks);

	// Конструктор копирования и присваивание (правило пяти).
	Money(const Money& other) = default;
	Money& operator=(const Money& other) = default;

	// --- Свойства ---
	unsigned int rubles() const;
	short int kopeks() const;

	// --- Задание 1: вычитание копеек (насыщение до 0) ---
	Money SubtractKopeks(unsigned int kopeks) const;

	// --- Задание 2: унарные операторы ---
	Money& operator++();    // добавление копейки
	Money& operator--();    // вычитание копейки (насыщение до 0)

	// --- Задание 2: операции приведения типа ---
	explicit operator unsigned int() const;  // явная: количество рублей
	operator bool() const;                   // неявная: сумма != 0

	// --- Задание 2: бинарные операторы ---
	Money operator-(unsigned int kopeks) const;  // вычесть копейки
	Money operator-(const Money& other) const;   // вычесть сумму

	// Дружественная функция вывода.
	friend std::ostream& operator<<(std::ostream& os, const Money& money);

private:
	// Приводит копейки к диапазону [0, 99], перенося излишек в рубли.
	void Normalize();

	// Фабричный метод: из общего числа копеек.
	static Money MoneyFromTotalKopeks(long long total_kopeks);

	unsigned int rubles_;
	short int kopeks_;
};

class money
{
};

#endif  // LABA4_MONEY_H_