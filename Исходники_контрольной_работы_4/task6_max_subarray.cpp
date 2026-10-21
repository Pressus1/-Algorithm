#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int size;
    if (!(std::cin >> size) || size <= 0) {
        std::cerr << "Размер массива должен быть положительным\n";
        return 1;
    }

    std::vector<long long> numbers(size);
    for (long long& number : numbers) {
        if (!(std::cin >> number)) {
            std::cerr << "Недостаточно элементов массива\n";
            return 1;
        }
    }

    long long currentSum = numbers.front();
    long long maximumSum = numbers.front();
    for (int index = 1; index < size; ++index) {
        currentSum = std::max(numbers[index], currentSum + numbers[index]);
        maximumSum = std::max(maximumSum, currentSum);
    }

    std::cout << maximumSum << '\n';
    return 0;
}
