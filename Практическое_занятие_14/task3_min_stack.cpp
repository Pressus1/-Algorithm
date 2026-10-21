#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class MinStack {
public:
    void push(long long value) {
        const long long current_minimum = data_.empty() ? value : std::min(value, data_.back().second);
        data_.emplace_back(value, current_minimum);
    }

    bool empty() const {
        return data_.empty();
    }

    long long top() const {
        return data_.back().first;
    }

    long long minimum() const {
        return data_.back().second;
    }

    void pop() {
        data_.pop_back();
    }

private:
    std::vector<std::pair<long long, long long>> data_;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int command_count = 0;
    if (!(std::cin >> command_count) || command_count < 0) {
        std::cerr << "Expected a non-negative command count\n";
        return 1;
    }

    MinStack stack;
    for (int index = 0; index < command_count; ++index) {
        std::string command;
        if (!(std::cin >> command)) {
            std::cerr << "Not enough commands\n";
            return 1;
        }
        if (command == "push") {
            long long value = 0;
            if (!(std::cin >> value)) {
                std::cerr << "push requires a value\n";
                return 1;
            }
            stack.push(value);
        } else if (command == "pop") {
            if (stack.empty()) {
                std::cout << "error\n";
            } else {
                std::cout << stack.top() << '\n';
                stack.pop();
            }
        } else if (command == "empty") {
            std::cout << (stack.empty() ? "yes" : "no") << '\n';
        } else if (command == "min") {
            if (stack.empty()) {
                std::cout << "error\n";
            } else {
                std::cout << stack.minimum() << '\n';
            }
        } else {
            std::cerr << "Unknown command: " << command << '\n';
            return 1;
        }
    }
}
