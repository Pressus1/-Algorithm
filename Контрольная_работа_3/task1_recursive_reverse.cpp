#include <iostream>
#include <string>

void printReversed(const std::string& text, std::size_t length) {
    if (length == 0) {
        return;
    }
    std::cout << text[length - 1];
    printReversed(text, length - 1);
}

int main() {
    std::string text;
    std::getline(std::cin, text);

    printReversed(text, text.size());
    std::cout << '\n';
    return 0;
}
