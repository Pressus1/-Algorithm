#include <fstream>
#include <string>

std::string read_first_line(const char* path, bool& ok) {
    std::ifstream input(path);
    std::string line;
    ok = static_cast<bool>(input) && static_cast<bool>(std::getline(input, line));
    return line;
}

int main() {
    bool x_ok = false;
    bool y_ok = false;
    const std::string x = read_first_line("input1.txt", x_ok);
    const std::string y = read_first_line("input2.txt", y_ok);
    std::ofstream output("output.txt");

    if (!x_ok || !y_ok || !output) {
        return 1;
    }

    output << (x.find(y) != std::string::npos ? "yes" : "no") << '\n';
    return 0;
}
