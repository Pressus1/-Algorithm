#include <array>
#include <cctype>
#include <fstream>

int main() {
    std::ifstream input("input.txt", std::ios::binary);
    std::ofstream output("output.txt", std::ios::binary);

    if (!input || !output) {
        return 1;
    }

    std::array<bool, 256> forbidden{};
    const char phrase[] = "user agreement";
    for (unsigned char symbol : phrase) {
        if (std::isalpha(symbol)) {
            forbidden[static_cast<unsigned char>(std::tolower(symbol))] = true;
        }
    }

    char symbol;
    while (input.get(symbol)) {
        const unsigned char byte = static_cast<unsigned char>(symbol);
        const unsigned char lower = static_cast<unsigned char>(std::tolower(byte));
        if (!forbidden[lower]) {
            output.put(symbol);
        }
    }

    return 0;
}
