// money.cc
// Реализация класса Money.
// Лабораторная работа №4, вариант 13.
// Стиль: Google C++ Style Guide.

#include "money.h"

#include <ostream>

Money::Money() : rubles_(0), kopeks_(0) {}

Money::Money(unsigned int rubles, short int kopeks)
    : rubles_(rubles), kopeks_(kopeks) {
    Normalize();
}

unsigned int Money::rubles() const { return rubles_; }

short int Money::kopeks() const { return kopeks_; }

Money Money::SubtractKopeks(unsigned int kopeks) const {
    long long total = static_cast<long long>(rubles_) * 100 + kopeks_;
    total -= kopeks;
    if (total < 0) total = 0;
    return MoneyFromTotalKopeks(total);
}

Money& Money::operator++() {
    long long total = static_cast<long long>(rubles_) * 100 + kopeks_;
    total += 1;
    *this = MoneyFromTotalKopeks(total);
    return *this;
}

Money& Money::operator--() {
    long long total = static_cast<long long>(rubles_) * 100 + kopeks_;
    total = (total > 0) ? total - 1 : 0;
    *this = MoneyFromTotalKopeks(total);
    return *this;
}

Money::operator unsigned int() const { return rubles_; }

Money::operator bool() const { return rubles_ != 0 || kopeks_ != 0; }

Money Money::operator-(unsigned int kopeks) const {
    return SubtractKopeks(kopeks);
}

Money Money::operator-(const Money& other) const {
    long long total = static_cast<long long>(rubles_) * 100 + kopeks_;
    long long other_total =
        static_cast<long long>(other.rubles_) * 100 + other.kopeks_;
    total -= other_total;
    if (total < 0) total = 0;
    return MoneyFromTotalKopeks(total);
}

std::ostream& operator<<(std::ostream& os, const Money& money) {
    os << money.rubles_ << " руб. " << money.kopeks_ << " коп.";
    return os;
}

void Money::Normalize() {
    if (kopeks_ >= 100) {
        rubles_ += static_cast<unsigned int>(kopeks_ / 100);
        kopeks_ = static_cast<short int>(kopeks_ % 100);
    }
    else if (kopeks_ < 0) {
        int borrow = (-kopeks_ + 99) / 100;
        if (rubles_ >= static_cast<unsigned int>(borrow)) {
            rubles_ -= static_cast<unsigned int>(borrow);
            kopeks_ += static_cast<short int>(borrow * 100);
        }
        else {
            rubles_ = 0;
            kopeks_ = 0;
        }
    }
}

Money Money::MoneyFromTotalKopeks(long long total_kopeks) {
    if (total_kopeks < 0) total_kopeks = 0;
    unsigned int rub = static_cast<unsigned int>(total_kopeks / 100);
    short int kop = static_cast<short int>(total_kopeks % 100);
    return Money(rub, kop);
}