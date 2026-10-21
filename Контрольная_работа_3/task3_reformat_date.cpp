#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

bool isLeapYear(int year) {
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

bool isValidDate(int day, int month, int year) {
    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return false;
    }
    const int daysInMonth[] = {
        31, isLeapYear(year) ? 29 : 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };
    return day <= daysInMonth[month - 1];
}

bool parseDate(const std::string& text, int& day, int& month, int& year) {
    if (text.size() != 10 || text[2] != '.' || text[5] != '.') {
        return false;
    }
    for (std::size_t i = 0; i < text.size(); ++i) {
        if (i != 2 && i != 5 && !std::isdigit(static_cast<unsigned char>(text[i]))) {
            return false;
        }
    }

    char firstDot;
    char secondDot;
    std::istringstream input(text);
    if (!(input >> day >> firstDot >> month >> secondDot >> year) ||
        firstDot != '.' || secondDot != '.' || input.peek() != std::char_traits<char>::eof()) {
        return false;
    }
    return isValidDate(day, month, year);
}

int main() {
    std::string text;
    std::getline(std::cin, text);

    int day;
    int month;
    int year;
    if (!parseDate(text, day, month, year)) {
        std::cerr << "Некорректная дата\n";
        return 1;
    }

    std::cout << std::setfill('0')
              << std::setw(4) << year << '-'
              << std::setw(2) << month << '-'
              << std::setw(2) << day << '\n';
    return 0;
}
