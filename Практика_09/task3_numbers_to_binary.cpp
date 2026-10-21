#include <algorithm>
#include <cctype>
#include <fstream>
#include <string>

std::string decimal_to_binary(const std::string& digits) {
    std::string value = digits;
    const std::size_t first_non_zero = value.find_first_not_of('0');
    if (first_non_zero == std::string::npos) {
        return "0";
    }
    value.erase(0, first_non_zero);

    std::string binary;
    while (value != "0") {
        std::string quotient;
        int remainder = 0;

        for (char digit : value) {
            const int current = remainder * 10 + (digit - '0');
            const int quotient_digit = current / 2;
            remainder = current % 2;
            if (!quotient.empty() || quotient_digit != 0) {
                quotient.push_back(static_cast<char>('0' + quotient_digit));
            }
        }

        binary.push_back(static_cast<char>('0' + remainder));
        value = quotient.empty() ? "0" : quotient;
    }
    std::reverse(binary.begin(), binary.end());
    return binary;
}

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    std::string line;

    if (!input || !output || !std::getline(input, line)) {
        return 1;
    }

    for (std::size_t i = 0; i < line.size();) {
        const unsigned char symbol = static_cast<unsigned char>(line[i]);
        if (!std::isdigit(symbol)) {
            output << line[i++];
            continue;
        }

        std::size_t end = i;
        while (end < line.size() && std::isdigit(static_cast<unsigned char>(line[end]))) {
            ++end;
        }
        output << decimal_to_binary(line.substr(i, end - i));
        i = end;
    }

    output << '\n';
    return 0;
}
