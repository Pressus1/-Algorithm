#include <fstream>
#include <iostream>

int main() {
    std::ifstream input("input.txt", std::ios::binary);
    if (!input) {
        std::cerr << "Не удалось открыть input.txt\n";
        return 1;
    }

    char symbol;
    while (input.get(symbol)) {
        std::cout << (symbol == ' ' ? '_' : symbol);
    }

    if (!input.eof()) {
        std::cerr << "Ошибка чтения input.txt\n";
        return 1;
    }
    return 0;
}
