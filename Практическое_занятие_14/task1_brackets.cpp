#include <iostream>
#include <string>
#include <vector>

static bool matches(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '[' && closing == ']') ||
           (opening == '{' && closing == '}');
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string message;
    std::getline(std::cin, message);
    std::vector<char> stack;
    bool correct = true;
    for (char symbol : message) {
        if (symbol == '(' || symbol == '[' || symbol == '{') {
            stack.push_back(symbol);
        } else if (symbol == ')' || symbol == ']' || symbol == '}') {
            if (stack.empty() || !matches(stack.back(), symbol)) {
                correct = false;
                break;
            }
            stack.pop_back();
        }
    }
    if (!stack.empty()) {
        correct = false;
    }

    std::cout << (correct ? "yes" : "no") << '\n';
}
