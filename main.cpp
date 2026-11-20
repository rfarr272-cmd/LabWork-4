// main.cc
// Точка входа: дружественный интерфейс для тестирования класса Money.
// Лабораторная работа №4, вариант 13.

#include "money.h"

#include <iostream>
#include <limits>
#include <string>

namespace {

    void ClearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int ReadIntInRange(const std::string& prompt, int min_value, int max_value) {
        while (true) {
            std::cout << prompt;
            int value = 0;
            if (std::cin >> value && value >= min_value && value <= max_value) {
                ClearInput();
                return value;
            }
            std::cout << "  Ошибка: введите целое число от " << min_value
                << " до " << max_value << "." << std::endl;
            ClearInput();
        }
    }

    unsigned int ReadUnsigned(const std::string& prompt) {
        while (true) {
            std::cout << prompt;
            unsigned int value = 0;
            if (std::cin >> value) {
                ClearInput();
                return value;
            }
            std::cout << "  Ошибка: введите неотрицательное целое число." << std::endl;
            ClearInput();
        }
    }

    short int ReadKopeks(const std::string& prompt) {
        int value = ReadIntInRange(prompt, 0, 99);
        return static_cast<short int>(value);
    }

    Money ReadMoney(const std::string& name) {
        std::cout << std::endl << "--- Ввод объекта " << name << " ---" << std::endl;
        unsigned int rub = ReadUnsigned("  Рубли (>= 0): ");
        short int kop = ReadKopeks("  Копейки (0..99): ");
        Money money(rub, kop);
        std::cout << "  Создан объект: " << money << std::endl;
        return money;
    }

    void Pause() {
        std::cout << std::endl << "Нажмите Enter, чтобы продолжить..." << std::endl;
        std::cin.get();
    }

    void ShowConstructors() {
        std::cout << std::endl << "=== Конструкторы ===" << std::endl;
        Money default_money;
        std::cout << "1) По умолчанию: " << default_money << std::endl;

        Money user_money = ReadMoney("user_money");
        std::cout << "2) С параметрами: " << user_money << std::endl;

        Money copy_money(user_money);
        std::cout << "3) Копированием: " << copy_money << std::endl;
    }

    void ShowSubtractKopeks() {
        std::cout << std::endl << "=== Задание 1: вычитание копеек ===" << std::endl;
        Money money = ReadMoney("money");
        unsigned int kopeks = ReadUnsigned("Сколько копеек вычесть (>= 0): ");
        Money result = money.SubtractKopeks(kopeks);
        std::cout << "Результат: " << money << " - " << kopeks << " коп. = "
            << result << std::endl;
    }

    void ShowUnaryOperators() {
        std::cout << std::endl << "=== Унарные операции ++ и -- ===" << std::endl;
        Money money = ReadMoney("money");
        std::cout << "Исходный: " << money << std::endl;

        ++money;
        std::cout << "После ++: " << money << std::endl;
        --money;
        std::cout << "После --: " << money << std::endl;
    }

    void ShowConversions() {
        std::cout << std::endl << "=== Приведение типов ===" << std::endl;
        Money money = ReadMoney("money");

        unsigned int rubles = static_cast<unsigned int>(money);
        std::cout << "unsigned int (явно): " << rubles << " руб." << std::endl;

        bool non_zero = money;
        std::cout << "bool (неявно): " << std::boolalpha << non_zero << std::endl;
    }

    void ShowBinaryOperators() {
        std::cout << std::endl << "=== Бинарные операции - ===" << std::endl;
        Money money = ReadMoney("money");

        std::cout << std::endl << "1) Вычитание копеек" << std::endl;
        unsigned int kopeks = ReadUnsigned("  Количество копеек: ");
        Money after_kopeks = money - kopeks;
        std::cout << "  " << money << " - " << kopeks << " коп. = "
            << after_kopeks << std::endl;

        std::cout << std::endl << "2) Вычитание суммы" << std::endl;
        Money other = ReadMoney("other");
        Money after_money = money - other;
        std::cout << "  " << money << " - " << other << " = " << after_money
            << std::endl;
    }

    void PrintMenu() {
        std::cout << std::endl << "========== МЕНЮ ==========" << std::endl
            << " ЗАДАНИЕ 1:" << std::endl
            << "  1. Конструкторы" << std::endl
            << "  2. Вычитание копеек (SubtractKopeks)" << std::endl
            << " ЗАДАНИЕ 2:" << std::endl
            << "  3. Унарные операции ++ / --" << std::endl
            << "  4. Приведение типов" << std::endl
            << "  5. Бинарные операции -" << std::endl
            << "  0. Выход" << std::endl
            << "==========================" << std::endl;
    }

}  // namespace

int main() {
    std::cout << "=== Лабораторная работа №4, вариант 13 ===" << std::endl
        << "Класс Money: рубли и копейки." << std::endl;

    while (true) {
        PrintMenu();
        int choice = ReadIntInRange("Выберите пункт: ", 0, 5);

        switch (choice) {
        case 0:
            std::cout << "До свидания!" << std::endl;
            return 0;
        case 1:
            ShowConstructors();
            break;
        case 2:
            ShowSubtractKopeks();
            break;
        case 3:
            ShowUnaryOperators();
            break;
        case 4:
            ShowConversions();
            break;
        case 5:
            ShowBinaryOperators();
            break;
        default:
            std::cout << "Неизвестный пункт." << std::endl;
            break;
        }

        Pause();
    }
}